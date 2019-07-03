#!/usr/bin/python3
# This file is part of volk library; see volk.h for version/license details

from collections import OrderedDict
import sys
import urllib
import xml.etree.ElementTree as etree
import urllib.request

def parse_xml(path):
    file = urllib.request.urlopen(path) if path.startswith("http") else open(path, 'r')
    with file:
        tree = etree.parse(file)
        return tree

def patch_file(path, blocks):
    result = []
    block = None

    with open(path, 'r') as file:
        for line in file.readlines():
            if block:
                if line == block:
                    result.append(line)
                    block = None
            else:
                result.append(line)
                if line.strip().startswith('/* VOLK_GENERATE_'):
                    block = line
                    result.append(blocks[line.strip()[17:-3]])

    with open(path, 'w') as file:
        for line in result:
            file.write(line)

def is_descendant_type(types, name, base):
    if name == base:
        return True
    type = types.get(name)
    if not type:
        return False
    parents = type.get('parent')
    if not parents:
        return False
    return any([is_descendant_type(types, parent, base) for parent in parents.split(',')])

def defined(key):
    return 'defined(' + key + ')'


def enumsBinding(enums, extensions):
    code = '//' + '-' * 20 + ' enums binding ' + '-' * 180 + '\n'
    cppTemp = 'py::enum_<{}>(m, "{}", py::arithmetic())'
    for enum in enums:
        name = enum.get('name')

        if name == "API Constants":
            codeTemp = 'm.attr("{}") = {}({});\n'
            constants = {}
            for member in enum.iter('enum'):
                mname = member.get('name')
                value = member.get('value')
                alias = member.get('alias')
                constants[mname] = value
                if not value:
                    value = constants[alias]
                pydata = ''
                if '.' in value:
                    pydata = 'py::float_'
                else:
                    pydata = 'py::int_'
                code += codeTemp.format(mname, pydata, mname)

            code += '\n'
        else:
            addedEnumNames = {}
            code += cppTemp.format(name, name[2:])
            for member in enum.iter('enum'):
                mname = member.get('name')
                code += '\n\t.value("{}", {}::{})'.format(mname, name, mname)

            for ext in extensionEnums:
                extends = ext.get('extends')
                if extends:
                    mname = ext.get('name')
                    if mname in addedEnumNames: continue
                    if extends == name:
                        code += '\n\t.value("{}", {}::{})'.format(mname, name, mname)
                    addedEnumNames[mname] = None

            code += '\n\t.export_values();\n'

    return code


def extensionsBinding(extensions):
    code = '//' + '-' * 20 + ' extensions constants binding ' + '-' * 180 + '\n'
    ccodeTemp = 'm.attr("{}") = {}({});\n'
    for ext in extensionEnums:
        name = ext.get('name')
        if name.endswith('VERSION'):
            pydata = 'py::int_'
        elif name.endswith('NAME'):
            pydata = 'py::str'
        else:
            continue
        code += ccodeTemp.format(name, pydata, name)

        #code += '\n'

    return code


def structsBinding(structs, vktypes):
    code = ''
    cppTemp = 'py::class_<{}>(m, "{}")'
    ctypes = [
        'int32_t', 'uint32_t', 'float', 'uint8_t', 'void*', 
        'size_t', 'uint64_t', 'int', 
    ]
    arraytypes = ['char', 'float*', 'uint32_t*', 'uint64_t*', 'int32_t*']
    alltypes = ctypes + arraytypes + list(vktypes.keys())

    for name in structs:
        struct = structs[name]
        mtypes = []
        memberNames = {}
        for member in struct.iter('member'):
            mtype = member.find('type')
            mname = member.find('name')

            ctype = mtype.text
            if mtype.tail:
                ctype += mtype.tail.strip()

            mtypes.append(ctype)
            #if ctype == 'VkStructureType':
            if mname.text == 'sType':
                memberNames[mname.text] = member.get('values')
            else:
                memberNames[mname.text] = None

        okToBind = False
        allGoodType = all([i in alltypes for i in mtypes])
        okToBind = allGoodType and mtypes
        if okToBind:
            code += cppTemp.format(name, name[2:])
            code += '\n\t.def(py::init<>())'
            for i, mname in enumerate(memberNames):
                if mtypes[i] in arraytypes:
                    code += '\n\t.def_readonly("{}", &{}::{})'.format(mname, name, mname)
                else:
                    code += '\n\t.def_readwrite("{}", &{}::{})'.format(mname, name, mname)
            code += ';\n\n'
        else:
            #if name == 'VkPhysicalDeviceProperties2':
            code += cppTemp.format(name, name[2:])
            if 'sType' in memberNames:
                code += '\n\t.def(py::init([]() { ' + '{} out '.format(name)
                code += '= {}; ' + 'out.sType = {}; '.format(memberNames['sType']) + 'return out; }))'
            else:
                code += '\n\t.def(py::init<>())'

            for i, mname in enumerate(memberNames):
                if mname == 'pNext':
                    code += '\n\t.def_property("{}", []({} &self) '.format(mname, name)
                    code += '{ return self.pNext; }, ' + '[]({} &self, void* pNext) '.format(name) + '{ self.pNext = pNext; })'
                elif mtypes[i] in arraytypes:
                    code += '\n\t.def_readonly("{}", &{}::{})'.format(mname, name, mname)
                else:
                    code += '\n\t.def_readwrite("{}", &{}::{})'.format(mname, name, mname)
            code += ';\n\n'
    return code

if __name__ == "__main__":
    #specpath = "https://raw.githubusercontent.com/KhronosGroup/Vulkan-Docs/master/xml/vk.xml"
    specpath = 'vk.xml'

    if len(sys.argv) > 1:
        specpath = sys.argv[1]

    spec = parse_xml(specpath)

    types = {}
    vktypes = {}
    structs = {}
    unions = {}
    for type in spec.findall('types/type'):
        category = type.get('category')
        name = type.get('name')
        tname = type.findtext('name')
        if tname:
            types[tname] = type

        if category == "basetype" or category == "bitmask":
            vktypes[tname] = type

        if category == "struct":
            structs[name] = type

        if category == "union":
            unions[name] = type

    #enums = spec.findall('enums')
    extensionEnums = spec.findall('extensions/extension/require/enum')
    #print(unions.keys())
    with open('py_binding.txt', 'w') as enumscpp:
        code = structsBinding(structs, vktypes)
        code += enumsBinding(spec.findall('enums'), extensionEnums)
        code += extensionsBinding(extensionEnums)
        enumscpp.write(code)
    #for enum in spec.findall('enums'):
    #    name = enum.get('name')
    #    for member in enum.iter('enum'):
    #        pass


    #block_keys = ('DEVICE_TABLE', 'PROTOTYPES_H', 'PROTOTYPES_C', 'LOAD_LOADER', 'LOAD_INSTANCE', 'LOAD_DEVICE', 'LOAD_DEVICE_TABLE')

    #blocks = {}

    #version = spec.find('types/type[name="VK_HEADER_VERSION"]')
    #blocks['VERSION'] = '#define VOLK_HEADER_VERSION ' + version.find('name').tail.strip() + '\n'

    #command_groups = OrderedDict()

    #for feature in spec.findall('feature'):
    #    key = defined(feature.get('name'))
    #    cmdrefs = feature.findall('require/command')
    #    command_groups[key] = [cmdref.get('name') for cmdref in cmdrefs]

    #for ext in sorted(spec.findall('extensions/extension'), key=lambda ext: ext.get('name')):
    #    supported = ext.get('supported')
    #    if supported == 'disabled':
    #        continue
    #    name = ext.get('name')
    #    for req in ext.findall('require'):
    #        key = defined(name)
    #        if req.get('feature'):
    #            key += ' && ' + defined(req.get('feature'))
    #        if req.get('extension'):
    #            key += ' && ' + defined(req.get('extension'))
    #        cmdrefs = req.findall('command')
    #        command_groups.setdefault(key, []).extend([cmdref.get('name') for cmdref in cmdrefs])

    #commands_to_groups = OrderedDict()

    #for (group, cmdnames) in command_groups.items():
    #    for name in cmdnames:
    #        commands_to_groups.setdefault(name, []).append(group)

    #for (group, cmdnames) in command_groups.items():
    #    command_groups[group] = [name for name in cmdnames if len(commands_to_groups[name]) == 1]

    #for (name, groups) in commands_to_groups.items():
    #    if len(groups) == 1:
    #        continue
    #    key = ' || '.join(['(' + g + ')' for g in groups])
    #    command_groups.setdefault(key, []).append(name)

    #commands = {}

    #for cmd in spec.findall('commands/command'):
    #    if not cmd.get('alias'):
    #        name = cmd.findtext('proto/name')
    #        commands[name] = cmd

    #for cmd in spec.findall('commands/command'):
    #    if cmd.get('alias'):
    #        name = cmd.get('name')
    #        commands[name] = commands[cmd.get('alias')]

    #types = {}

    #for type in spec.findall('types/type'):
    #    name = type.findtext('name')
    #    if name:
    #        types[name] = type

    #for key in block_keys:
    #    blocks[key] = ''

    #for (group, cmdnames) in command_groups.items():
    #    ifdef = '#if ' + group + '\n'

    #    for key in block_keys:
    #        blocks[key] += ifdef

    #    for name in sorted(cmdnames):
    #        cmd = commands[name]
    #        type = cmd.findtext('param[1]/type')

    #        if name == 'vkGetInstanceProcAddr':
    #            type = ''
    #        if name == 'vkGetDeviceProcAddr':
    #            type = 'VkInstance'

    #        if is_descendant_type(types, type, 'VkDevice'):
    #            blocks['LOAD_DEVICE'] += '\t' + name + ' = (PFN_' + name + ')load(context, "' + name + '");\n'
    #            blocks['DEVICE_TABLE'] += '\tPFN_' + name + ' ' + name + ';\n'
    #            blocks['LOAD_DEVICE_TABLE'] += '\ttable->' + name + ' = (PFN_' + name + ')load(context, "' + name + '");\n'
    #        elif is_descendant_type(types, type, 'VkInstance'):
    #            blocks['LOAD_INSTANCE'] += '\t' + name + ' = (PFN_' + name + ')load(context, "' + name + '");\n'
    #        elif type != '':
    #            blocks['LOAD_LOADER'] += '\t' + name + ' = (PFN_' + name + ')load(context, "' + name + '");\n'

    #        blocks['PROTOTYPES_H'] += 'extern PFN_' + name + ' ' + name + ';\n'
    #        blocks['PROTOTYPES_C'] += 'PFN_' + name + ' ' + name + ';\n'

    #    for key in block_keys:
    #        if blocks[key].endswith(ifdef):
    #            blocks[key] = blocks[key][:-len(ifdef)]
    #        else:
    #            blocks[key] += '#endif /* ' + group + ' */\n'

    #patch_file('volk.h', blocks)
    #patch_file('volk.c', blocks)

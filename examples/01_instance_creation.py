# -*- coding: UTF-8 -*-

import _vk
from PySide2 import (QtGui, QtCore)



class HelloTriangleApplication(QtGui.QWindow):

    def __init__(self):
        super(HelloTriangleApplication, self).__init__()

        self.setWidth(1280)
        self.setHeight(720)

        self.setTitle("Vulkan Python - PySide2")

        #self.setSurfaceType(self.OpenGLSurface)

        self.__instance = None

        self.initVulkan()

    def __del__(self):
        del self.__instance
        print('instance destroyed')

    def initVulkan(self):
        self.__cretaeInstance()

    def __cretaeInstance(self):
        #appInfo = _vk.ApplicationInfo()
        #appInfo.applicationName = 'pyvkApp'
        #appInfo.engineName = 'pyvkEngine'
        #appInfo.applicationVersion = _vk.makeVersion()
        #appInfo.engineVersion = _vk.makeVersion()
        #appInfo.apiVersion = _vk.Instance.version()
        #v = _vk.makeVersion()
        #appInfo = _vk.ApplicationInfo('pyvkApp', 'pyvkEngine', v, v, _vk.Instance.version())
        
        #createInfo = _vk.InstanceCreateInfo()
        #createInfo.applicationInfo = appInfo
        #createInfo = _vk.InstanceCreateInfo(appInfo, [], [])

        createInfo = _vk.InstanceCreateInfo()
        createInfo.applicationInfo.applicationName = 'pyvkApp'
        createInfo.applicationInfo.engineName = 'pyvkEngine'
        createInfo.applicationInfo.engineVersion = _vk.makeVersion()
        createInfo.applicationInfo.applicationVersion = _vk.makeVersion()
        createInfo.applicationInfo.apiVersion = _vk.makeVersion()

        extensionNames = [e.extensionName for e in _vk.Instance.getExtensionProperties()]
        extensionNames = ['VK_KHR_get_physical_device_properties2', 'VK_KHR_get_surface_capabilities2', 'VK_KHR_surface', 'VK_KHR_win32_surface']
        createInfo.enabledExtensionNames = extensionNames
        #print(createInfo.enabledExtensionNames)

        #layerNames = [l.layerName for l in _vk.Instance.getLayerProperties()]
        layerNames = ['VK_LAYER_KHRONOS_validation', ]
        createInfo.enabledLayerNames = layerNames

        self.__instance = _vk.Instance(createInfo)
        print(self.__instance.isValid)


if __name__ == '__main__':
    import sys

    app = QtGui.QGuiApplication(sys.argv)

    win = HelloTriangleApplication()
    win.show()

    def clenaup():
        global win
        del win

    app.aboutToQuit.connect(clenaup)

    sys.exit(app.exec_())

import time
import math
import array

import _vk
from PIL import Image
import numpy as np



WIDTH = 3200  # Size of rendered mandelbrot set.
HEIGHT = 2400  # Size of renderered mandelbrot set.
WORKGROUP_SIZE = 32  # Workgroup size in compute shader.


enableValidationLayers = True

class ComputeApplication(object):

    def __init__(self):
        self.__instance = None
        self.__debugMessenger = None

        # The physical device is some device on the system that supports usage of Vulkan.
        # Often, it is simply a graphics card that supports Vulkan.
        self.__physicalDevice = None

        # Then we have the logical device VkDevice, which basically allows
        # us to interact with the physical device.
        self.__device = None

        # The pipeline specifies the pipeline that all graphics and compute commands pass though in Vulkan.
        # We will be creating a simple compute pipeline in this application.
        self.__pipeline = None
        self.__pipelineLayout = None
        self.__computeShaderModule = None

        # The command buffer is used to record commands, that will be submitted to a queue.
        # To allocate such command buffers, we use a command pool.
        self.__commandPool = None
        self.__commandBuffer = None

        # Descriptors represent resources in shaders. They allow us to use things like
        # uniform buffers, storage buffers and images in GLSL.
        # A single descriptor represents a single resource, and several descriptors are organized
        # into descriptor sets, which are basically just collections of descriptors.
        self.__descriptorPool = None
        self.__descriptorSet = None
        self.__descriptorSetLayout = None

        # The mandelbrot set will be rendered to this buffer.
        # The memory that backs the buffer is bufferMemory.
        self.__buffer = None
        self.__bufferMemory = None

        # size of `buffer` in bytes.
        self.__bufferSize = 0

        self.__enabledLayers = []

        # In order to execute commands on a device(GPU), the commands must be submitted
        # to a queue. The commands are stored in a command buffer, and this command buffer
        # is given to the queue.
        # There will be different kinds of queues on the device. Not all queues support
        # graphics operations, for instance. For this application, we at least want a queue
        # that supports compute operations.

        # a queue supporting compute operations.
        self.__queue = None

        # Groups of queues that have the same capabilities(for instance, they all supports graphics and computer operations),
        # are grouped into queue families.

        # When submitting a command buffer, you must specify to which queue in the family you are submitting to.
        # This variable keeps track of the index of that queue in its family.
        self.__queueFamilyIndex = -1

        self.pixel = array.array('f', [0, 0, 0, 0])

        self.saveImageTime = 0
        self.cpuDataConverTime = 0

    def __del__(self):
        del self.__debugMessenger
        del self.__bufferMemory
        del self.__buffer
        del self.__computeShaderModule
        del self.__descriptorPool
        del self.__descriptorSetLayout
        del self.__pipelineLayout
        del self.__pipeline
        del self.__commandBuffer
        del self.__commandPool
        del self.__device
        del self.__instance

    def run(self):
        # Buffer size of the storage buffer that will contain the rendered mandelbrot set.
        self.__bufferSize = self.pixel.buffer_info()[1] * self.pixel.itemsize * WIDTH * HEIGHT

        # Initialize vulkan
        self.createInstance()
        self.findPhysicalDevice()
        self.createDevice()
        self.createBuffer()
        self.createDescriptorSetLayout()
        self.createDescriptorSet()
        self.createComputePipeline()
        self.createCommandBuffer()

        # Finally, run the recorded command buffer.
        self.runCommandBuffer()

        # The former command rendered a mandelbrot set to a buffer.
        # Save that buffer as a png on disk.
        st = time.time()

        self.saveRenderedImage()

        self.saveImageTime = time.time() - st

    def saveRenderedImage(self):
        # Map the buffer memory, so that we can read from it on the CPU.
        pmappedMemory = self.__bufferMemory.map(0, self.__bufferSize, 0)

        # Get the color data from the buffer, and cast it to bytes.
        # We save the data to a vector.
        st = time.time()

        pa = np.frombuffer(pmappedMemory, np.float32)
        pa = pa.reshape((HEIGHT, WIDTH, 4))
        pa *= 255

        self.cpuDataConverTime = time.time() - st

        # Done reading, so unmap.
        self.__bufferMemory.unmap()

        # Now we save the acquired color data to a .png.
        image = Image.fromarray(pa.astype(np.uint8))
        image.save('mandelbrot.png')

    @staticmethod
    def debugCallback(messageSeverity, messageType, callbackData, userData):
        #print(messageSeverity, messageType, callbackData)
        print(callbackData.message)

    def createInstance(self):
        enabledExtensions = []
        if enableValidationLayers:
            supportLayerNames = [prop.layerName for prop in _vk.Instance.getLayerProperties()]
            if 'VK_LAYER_KHRONOS_validation' not in supportLayerNames:
                raise Exception('Layer VK_LAYER_KHRONOS_validation not supported')
            self.__enabledLayers.append('VK_LAYER_KHRONOS_validation')

            supportExtensions = [prop.extensionName for prop in _vk.Instance.getExtensionProperties()]
            if _vk.VK_EXT_DEBUG_UTILS_EXTENSION_NAME not in supportExtensions:
                raise Exception('Extension {} not supported'.format(_vk.VK_EXT_DEBUG_UTILS_EXTENSION_NAME))
            enabledExtensions.append(_vk.VK_EXT_DEBUG_UTILS_EXTENSION_NAME)
        
        appInfo = _vk.ApplicationInfo()
        appInfo.applicationName = 'Hello world app'
        appInfo.applicationVersion = 0
        appInfo.engineName = 'awesomeengine'
        appInfo.engineVersion = 0
        appInfo.apiVersion = _vk.makeVersion()

        createInfo = _vk.InstanceCreateInfo()
        createInfo.applicationInfo = appInfo
        createInfo.enabledLayerNames = self.__enabledLayers
        createInfo.enabledExtensionNames = enabledExtensions

        self.__instance = _vk.Instance(createInfo)

        if enableValidationLayers:
            messageSeverity = _vk.VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | _vk.VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | _vk.VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT
            messageType = _vk.VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | _vk.VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | _vk.VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT

            createInfo = _vk.DebugUtilsMessengerCreateInfoEXT()
            createInfo.messageSeverity = messageSeverity
            createInfo.messageType = messageType
            createInfo.userCallback = self.debugCallback

            self.__debugMessenger = self.__instance.createDebugUtilsMessengerEXT(createInfo)

    def findPhysicalDevice(self):
        self.__physicalDevice = self.__instance.getPhysicalDevices()[0]

    def getComputeQueueFamilyIndex(self):
        # Now find a family that supports compute.
        for i, props in enumerate(self.__physicalDevice.queueFamilyProperties):
            if props.queueCount > 0 and props.queueFlags & _vk.VK_QUEUE_COMPUTE_BIT:
                # found a queue with compute. We're done!
                return i

        return -1

    def createDevice(self):
        # We create the logical device in this function.
        self.__queueFamilyIndex = self.getComputeQueueFamilyIndex()
        # When creating the device, we also specify what queues it has.
        queueCreateInfo = _vk.DeviceQueueCreateInfo(self.__queueFamilyIndex, [1.0,])

        deviceFeatures = _vk.PhysicalDeviceFeatures()
        deviceCreateInfo = _vk.DeviceCreateInfo()
        deviceCreateInfo.enabledLayerNames = self.__enabledLayers
        deviceCreateInfo.queueCreateInfos = [queueCreateInfo, ]
        deviceCreateInfo.enabledFeatures = deviceFeatures

        self.__device = self.__physicalDevice.createDevice(deviceCreateInfo)
        self.__queue = self.__device.getQueue(self.__queueFamilyIndex, 0)

    def findMemoryType(self, memoryTypeBits, properties):
        memoryProperties = self.__physicalDevice.memoryProperties

        # How does this search work?
        # See the documentation of VkPhysicalDeviceMemoryProperties for a detailed description.
        for i, mt in enumerate(memoryProperties.memoryTypes):
            if memoryTypeBits & (1 << i) and (mt.propertyFlags & properties) == properties:
                return i

        return -1

    def createBuffer(self):
        # We will now create a buffer. We will render the mandelbrot set into this buffer
        # in a computer shade later.
        bufferCreateInfo = _vk.BufferCreateInfo()
        bufferCreateInfo.size = self.__bufferSize
        bufferCreateInfo.usage = _vk.VK_BUFFER_USAGE_STORAGE_BUFFER_BIT
        bufferCreateInfo.sharingMode = _vk.VK_SHARING_MODE_EXCLUSIVE

        self.__buffer = self.__device.createBuffer(bufferCreateInfo)

        memoryRequirements = self.__buffer.getMemoryRequirements()

        index = self.findMemoryType(memoryRequirements.memoryTypeBits,
                                    _vk.VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | _vk.VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
        allocateInfo = _vk.MemoryAllocateInfo()
        allocateInfo.allocationSize = memoryRequirements.size
        allocateInfo.memoryTypeIndex = index

        self.__bufferMemory = self.__device.allocateMemory(allocateInfo)

        self.__buffer.bindMemory(self.__bufferMemory, 0)

    def createDescriptorSetLayout(self):
        # Here we specify a descriptor set layout. This allows us to bind our descriptors to
        # resources in the shader.

        # Here we specify a binding of type VK_DESCRIPTOR_TYPE_STORAGE_BUFFER to the binding point
        # 0. This binds to
        #   layout(std140, binding = 0) buffer buf
        # in the compute shader.

        descriptorSetLayoutBinding = _vk.DescriptorSetLayoutBinding()
        descriptorSetLayoutBinding.binding = 0
        descriptorSetLayoutBinding.descriptorType = _vk.VK_DESCRIPTOR_TYPE_STORAGE_BUFFER
        descriptorSetLayoutBinding.descriptorCount = 1
        descriptorSetLayoutBinding.stageFlags = _vk.VK_SHADER_STAGE_COMPUTE_BIT

        descriptorSetLayoutCreateInfo = _vk.DescriptorSetLayoutCreateInfo()
        descriptorSetLayoutCreateInfo.bindings = [descriptorSetLayoutBinding, ]

        # Create the descriptor set layout.
        self.__descriptorSetLayout = self.__device.createDescriptorSetLayout(descriptorSetLayoutCreateInfo)

    def createDescriptorSet(self):
        descriptorPoolSize = _vk.DescriptorPoolSize()
        descriptorPoolSize.type = _vk.VK_DESCRIPTOR_TYPE_STORAGE_BUFFER
        descriptorPoolSize.descriptorCount = 1

        descriptorPoolCreateInfo = _vk.DescriptorPoolCreateInfo()
        descriptorPoolCreateInfo.maxSets = 1
        descriptorPoolCreateInfo.poolSizes = [descriptorPoolSize,]

        self.__descriptorPool = self.__device.createDescriptorPool(descriptorPoolCreateInfo)

        descriptorSetAllocateInfo = _vk.DescriptorSetAllocateInfo()
        descriptorSetAllocateInfo.descriptorPool = self.__descriptorPool
        descriptorSetAllocateInfo.setLayouts = [self.__descriptorSetLayout,]

        self.__descriptorSet = self.__device.allocateDescriptorSets(descriptorSetAllocateInfo)[0]

        descriptorBufferInfo = _vk.DescriptorBufferInfo()
        descriptorBufferInfo.buffer = self.__buffer
        descriptorBufferInfo.offset = 0
        descriptorBufferInfo.range = self.__bufferSize

        writeDescriptorSet = _vk.WriteDescriptorSet()
        writeDescriptorSet.dstSet = self.__descriptorSet
        writeDescriptorSet.dstBinding = 0
        writeDescriptorSet.descriptorCount = 1
        writeDescriptorSet.descriptorType = _vk.VK_DESCRIPTOR_TYPE_STORAGE_BUFFER
        writeDescriptorSet.bufferInfo = [descriptorBufferInfo,]

        self.__device.updateDescriptorSets([writeDescriptorSet, ], [])

    def createComputePipeline(self):
        self.__computeShaderModule = self.__device.createShaderModule('shaders/mandelbrot_compute.spv')

        shaderStageCreateInfo = _vk.PipelineShaderStageCreateInfo()
        shaderStageCreateInfo.stage = _vk.VK_SHADER_STAGE_COMPUTE_BIT
        shaderStageCreateInfo.module = self.__computeShaderModule
        shaderStageCreateInfo.name = 'main'

        pipelineLayoutInfo = _vk.PipelineLayoutCreateInfo()
        pipelineLayoutInfo.setLayouts = [self.__descriptorSetLayout, ]
        
        self.__pipelineLayout = self.__device.createPipelineLayout(pipelineLayoutInfo)

        pipelineCreateInfo = _vk.ComputePipelineCreateInfo()
        pipelineCreateInfo.stage = shaderStageCreateInfo
        pipelineCreateInfo.layout = self.__pipelineLayout

        self.__pipeline = self.__device.createComputePipelines(_vk.PipelineCache(), [pipelineCreateInfo, ])[0]

    def createCommandBuffer(self):
        poolInfo = _vk.CommandPoolCreateInfo()
        poolInfo.queueFamilyIndex = self.__queueFamilyIndex

        self.__commandPool = self.__device.createCommandPool(poolInfo)

        allocInfo = _vk.CommandBufferAllocateInfo()
        allocInfo.commandPool = self.__commandPool
        allocInfo.level = _vk.VK_COMMAND_BUFFER_LEVEL_PRIMARY
        allocInfo.commandBufferCount = 1

        self.__commandBuffer = self.__device.allocateCommandBuffers(allocInfo)[0]

        beginInfo = _vk.CommandBufferBeginInfo()
        beginInfo.flags = _vk.VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT

        self.__commandBuffer.begin(beginInfo)

        self.__commandBuffer.bindPipeline(_vk.VK_PIPELINE_BIND_POINT_COMPUTE, self.__pipeline)
        self.__commandBuffer.bindDescriptorSets(
            _vk.VK_PIPELINE_BIND_POINT_COMPUTE, self.__pipelineLayout, 0, [self.__descriptorSet], []
            )

        self.__commandBuffer.dispatch(
            int(math.ceil(WIDTH / float(WORKGROUP_SIZE))),  # int for py2 compatible
            int(math.ceil(HEIGHT / float(WORKGROUP_SIZE))),  # int for py2 compatible
            1)

        self.__commandBuffer.end()

    def runCommandBuffer(self):
        submitInfo = _vk.SubmitInfo()
        submitInfo.commandBuffers = [self.__commandBuffer, ]

        fenceInfo = _vk.FenceCreateInfo()
        fenceInfo.flags = 0
        fence = self.__device.createFence(fenceInfo)

        self.__queue.submit([submitInfo, ], fence)

        fence.wait(100000000000)
        del fence


if __name__ == '__main__':
    startTime = time.time()

    app = ComputeApplication()
    app.run()

    endTime = time.time()
    if enableValidationLayers:
        print('raw image data (CPU) convert time: {} seconds'.format(app.cpuDataConverTime))
        print('Vulkan setup and compute time: {} seconds'.format(endTime-startTime-app.saveImageTime))
        print('save image time: {} seconds'.format(app.saveImageTime))
        print('total time used: {} seconds'.format(endTime-startTime))

    del app

# -*- coding: UTF-8 -*-

import sys

import _vk
import numpy as np
from PySide2 import (QtGui, QtCore)

validationLayers = [
    'VK_LAYER_KHRONOS_validation'
]

deviceExtensions = [
    'VK_KHR_swapchain'
]

VK_EXT_DEBUG_UTILS_EXTENSION_NAME = 'VK_EXT_debug_utils'

MAX_FRAMES_IN_FLIGHT = 3

enableValidationLayers = True


def debugCallback(messageSeverity, messageType, callbackData, userData):
    #print(messageSeverity, messageType, callbackData)
    print(callbackData.message)


class QueueFamilyIndices(object):

    def __init__(self):
        self.graphicsFamily = -1
        self.presentFamily = -1

    @property
    def isComplete(self):
        return self.graphicsFamily >= 0 and self.presentFamily >= 0


class SwapChainSupportDetails(object):

    def __init__(self):
        self.capabilities = None
        self.formats = None
        self.presentModes = None


class Vertex(object):
    POS = np.array([0, 0], np.float32)
    COLOR = np.array([0, 0, 0], np.float32)
    
    @staticmethod
    def getBindingDescription():
        bindingDescription = _vk.VertexInputBindingDescription()
        bindingDescription.binding = 0
        bindingDescription.stride = Vertex.POS.nbytes + Vertex.COLOR.nbytes
        bindingDescription.inputRate = _vk.VK_VERTEX_INPUT_RATE_VERTEX

        return bindingDescription

    @staticmethod
    def getAttributeDescriptions():
        a0 = _vk.VertexInputAttributeDescription()
        a0.binding = 0
        a0.location = 0
        a0.format = _vk.VK_FORMAT_R32G32_SFLOAT
        a0.offset = 0

        a1 = _vk.VertexInputAttributeDescription()
        a1.binding = 0
        a1.location = 1
        a1.format = _vk.VK_FORMAT_R32G32B32_SFLOAT
        a1.offset = Vertex.POS.nbytes
        return [a0, a1]


vertices = np.array(
    [
        0, -0.5, 1, 0, 0,
        .5, .5, 0, 1, 0,
        -.5, .5, 0, 0, 1
    ], np.float32
)


class HelloTriangleApplication(QtGui.QWindow):

    def __init__(self):
        super(HelloTriangleApplication, self).__init__()

        self.setWidth(1280)
        self.setHeight(720)

        self.setTitle("Vulkan Python - PySide2")

        # self.setSurfaceType(self.OpenGLSurface)

        self.__instance = None
        self.__debugMessenger = None
        self.__surface = None

        self.__physicalDevice = None
        self.__device = None
        self.__graphicQueue = None
        self.__presentQueue = None

        self.__swapChain = None
        self.__swapChainImages = []
        self.__swapChainImageFormat = None
        self.__swapChainExtent = None
        self.__swapChainImageViews = []
        self.__swapChainFramebuffers = []

        self.__renderPass = None
        self.__pipelineLayout = None
        self.__graphicsPipeline = None

        self.__commandPool = None

        self.__vertexBuffer = None
        self.__vertexBufferMemory = None

        self.__commandBuffers = []

        self.__indices = QueueFamilyIndices()

        self.__imageAvailableSemaphores = []
        self.__renderFinishedSemaphores = []
        self.__inFlightFences = []
        self.__currentFrame = 0

        self.initVulkan()

    def __del__(self):
        self.__device.waitIdle()
        self.__cleanupSwapChain()

        del self.__vertexBuffer
        del self.__vertexBufferMemory
        del self.__imageAvailableSemaphores
        del self.__renderFinishedSemaphores
        del self.__inFlightFences
        del self.__commandPool
        del self.__device
        del self.__debugMessenger
        del self.__surface
        del self.__instance
        print('instance destroyed')

    def initVulkan(self):
        self.__cretaeInstance()
        self.__setupDebugCallback()
        self.__createSurface()
        self.__pickPhysicalDevice()
        self.__createLogicalDevice()
        self.__createSwapChain()
        self.__createImageViews()
        self.__createRenderPass()
        self.__createGraphicsPipeline()
        self.__createFramebuffers()
        self.__createCommandPool()
        self.__createVertexBuffer()
        self.__createCommandBuffers()
        self.__createSyncObjects()

    def __cleanupSwapChain(self):
        del self.__swapChainFramebuffers
        self.__swapChainFramebuffers = []

        del self.__commandBuffers
        self.__commandBuffers = []

        del self.__graphicsPipeline
        self.__graphicsPipeline = None
        del self.__pipelineLayout
        self.__pipelineLayout = None
        del self.__renderPass
        self.__renderPass = None

        del self.__swapChainImageViews
        self.__swapChainImageViews = []

        del self.__swapChain
        self.__swapChain = None

    def __recreateSwapChain(self):
        self.__device.waitIdle()

        self.__cleanupSwapChain()

        self.__createSwapChain()
        self.__createImageViews()
        self.__createRenderPass()
        self.__createGraphicsPipeline()
        self.__createFramebuffers()
        self.__createCommandBuffers()

        self.__device.waitIdle()

    def __cretaeInstance(self):
        createInfo = _vk.InstanceCreateInfo()
        createInfo.applicationInfo.applicationName = 'pyvkApp'
        createInfo.applicationInfo.engineName = 'pyvkEngine'
        createInfo.applicationInfo.engineVersion = _vk.makeVersion()
        createInfo.applicationInfo.applicationVersion = _vk.makeVersion()
        createInfo.applicationInfo.apiVersion = _vk.makeVersion()

        debugInfo = _vk.DebugUtilsMessengerCreateInfoEXT()
        messageSeverity = _vk.VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | _vk.VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | _vk.VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT #| _vk.VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT
        debugInfo.messageSeverity = messageSeverity
        debugInfo.messageType = _vk.VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | _vk.VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | _vk.VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT
        debugInfo.userCallback = debugCallback

        createInfo.pNext = debugInfo

        if enableValidationLayers:
            extensionNames = self.__getRequiredExtensions()
            #extensionNames = ['VK_LAYER_KHRONOS_validation', 'VK_KHR_get_surface_capabilities2', 'VK_KHR_surface', 'VK_KHR_win32_surface']
            createInfo.enabledExtensionNames = extensionNames
            createInfo.enabledLayerNames = validationLayers

        self.__instance = _vk.Instance(createInfo)

    def __setupDebugCallback(self):
        if not enableValidationLayers:
            return

        messageSeverity = _vk.VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | _vk.VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | _vk.VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT
        messageType = _vk.VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | _vk.VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | _vk.VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT

        createInfo = _vk.DebugUtilsMessengerCreateInfoEXT()
        createInfo.messageSeverity = messageSeverity
        createInfo.messageType = messageType
        createInfo.userCallback = debugCallback

        self.__debugMessenger = self.__instance.createDebugUtilsMessengerEXT(createInfo)

    def __createSurface(self):
        if sys.platform == 'win32':
            self.__surface = self.__instance.createWin32Surface(self.winId())

    def __pickPhysicalDevice(self):
        physicalDevices = self.__instance.getPhysicalDevices()

        for device in physicalDevices:
            if self.__isDeviceSuitable(device):
                self.__physicalDevice = device
                break

        assert self.__physicalDevice.isValid

    def __createLogicalDevice(self):
        self.__indices = self.__findQueueFamilies(self.__physicalDevice)

        uniqueQueueFamilies = {}.fromkeys([self.__indices.graphicsFamily, self.__indices.presentFamily])
        queueCreateInfos = []
        for i in uniqueQueueFamilies:
            queueCreateInfo = _vk.DeviceQueueCreateInfo()
            queueCreateInfo.queueFamilyIndex = self.__indices.graphicsFamily
            queueCreateInfo.queuePriorities = [1.0,]
            queueCreateInfos.append(queueCreateInfo)

        deviceFeatures = _vk.PhysicalDeviceFeatures()
        createInfo = _vk.DeviceCreateInfo()
        createInfo.queueCreateInfos = [queueCreateInfo, ]
        createInfo.enabledFeatures = deviceFeatures
        createInfo.enabledExtensionNames = deviceExtensions
        if enableValidationLayers:
            createInfo.enabledLayerNames = validationLayers

        self.__device = self.__physicalDevice.createDevice(createInfo)
        #self.__device = _vk.Device(self.__physicalDevice, createInfo)

        self.__graphicQueue = self.__device.getQueue(self.__indices.graphicsFamily, 0)
        self.__presentQueue = self.__device.getQueue(self.__indices.presentFamily, 0)

    def __createSwapChain(self):
        swapChainSupport = self.__querySwapChainSupport(self.__physicalDevice)

        surfaceFormat = self.__chooseSwapSurfaceFormat(swapChainSupport.formats)
        presentMode = self.__chooseSwapPresentMode(swapChainSupport.presentModes)
        extent = self.__chooseSwapExtent(swapChainSupport.capabilities)

        imageCount = swapChainSupport.capabilities.minImageCount + 1
        if swapChainSupport.capabilities.maxImageCount > 0 and imageCount > swapChainSupport.capabilities.maxImageCount:
            imageCount = swapChainSupport.capabilities.maxImageCount

        indices = self.__findQueueFamilies(self.__physicalDevice)

        createInfo = _vk.SwapchainCreateInfoKHR()
        createInfo.surface = self.__surface
        createInfo.minImageCount = imageCount
        createInfo.imageFormat = surfaceFormat.format
        createInfo.imageColorSpace = surfaceFormat.colorSpace
        createInfo.imageExtent = extent
        createInfo.imageArrayLayers = 1
        createInfo.imageUsage = _vk.VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT
        createInfo.imageSharingMode = _vk.VK_SHARING_MODE_EXCLUSIVE
        createInfo.preTransform = swapChainSupport.capabilities.currentTransform
        createInfo.compositeAlpha = _vk.VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR
        createInfo.presentMode = presentMode
        createInfo.clipped = True
        if indices.graphicsFamily != indices.presentFamily:
            createInfo.imageSharingMode = _vk.VK_SHARING_MODE_CONCURRENT
            createInfo.queueFamilyIndices = [indices.graphicsFamily, indices.presentFamily]

        self.__swapChain = self.__device.createSwapchainKHR(createInfo)
        assert self.__swapChain.isValid

        self.__swapChainImages = self.__swapChain.getImagesKHR()

        self.__swapChainImageFormat = surfaceFormat.format
        self.__swapChainExtent = extent

    def __createImageViews(self):
        self.__swapChainImageViews = []

        for i, image in enumerate(self.__swapChainImages):
            createInfo = _vk.ImageViewCreateInfo()
            createInfo.image = image
            createInfo.viewType = _vk.VK_IMAGE_VIEW_TYPE_2D
            createInfo.format = self.__swapChainImageFormat
            createInfo.components.r = _vk.VK_COMPONENT_SWIZZLE_IDENTITY
            createInfo.components.g = _vk.VK_COMPONENT_SWIZZLE_IDENTITY
            createInfo.components.b = _vk.VK_COMPONENT_SWIZZLE_IDENTITY
            createInfo.components.a = _vk.VK_COMPONENT_SWIZZLE_IDENTITY
            createInfo.subresourceRange.aspectMask = _vk.VK_IMAGE_ASPECT_COLOR_BIT
            createInfo.subresourceRange.baseMipLevel = 0
            createInfo.subresourceRange.levelCount = 1
            createInfo.subresourceRange.baseArrayLayer = 0
            createInfo.subresourceRange.layerCount = 1

            self.__swapChainImageViews.append(self.__device.createImageView(createInfo))

    def __createRenderPass(self):
        colorAttachment = _vk.AttachmentDescription()
        colorAttachment.format = self.__swapChainImageFormat
        colorAttachment.samples = _vk.VK_SAMPLE_COUNT_1_BIT
        colorAttachment.loadOp = _vk.VK_ATTACHMENT_LOAD_OP_CLEAR
        colorAttachment.storeOp = _vk.VK_ATTACHMENT_STORE_OP_STORE
        colorAttachment.stencilLoadOp = _vk.VK_ATTACHMENT_LOAD_OP_DONT_CARE
        colorAttachment.stencilStoreOp = _vk.VK_ATTACHMENT_STORE_OP_DONT_CARE
        colorAttachment.initialLayout = _vk.VK_IMAGE_LAYOUT_UNDEFINED
        colorAttachment.finalLayout = _vk.VK_IMAGE_LAYOUT_PRESENT_SRC_KHR

        colorAttachmentRef = _vk.AttachmentReference()
        colorAttachmentRef.attachment = 0
        colorAttachmentRef.layout = _vk.VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL

        subpass = _vk.SubpassDescription()
        subpass.pipelineBindPoint = _vk.VK_PIPELINE_BIND_POINT_GRAPHICS
        subpass.colorAttachments = [colorAttachmentRef, ]

        dependency = _vk.SubpassDependency()
        dependency.srcSubpass = _vk.VK_SUBPASS_EXTERNAL
        dependency.dstSubpass = 0
        dependency.srcStageMask = _vk.VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT
        dependency.srcAccessMask = 0
        dependency.dstStageMask = _vk.VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT
        dependency.dstAccessMask = _vk.VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | _vk.VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT

        renderPassInfo = _vk.RenderPassCreateInfo()
        renderPassInfo.attachments = [colorAttachment, ]
        renderPassInfo.subpasses = [subpass, ]
        renderPassInfo.dependencies = [dependency, ]

        self.__renderPass = self.__device.createRenderPass(renderPassInfo)

    def __createGraphicsPipeline(self):
        vertShaderModule = self.__device.createShaderModule('shaders/17_shader_vertexbuffer_vert.spv')
        fragShaderModule = self.__device.createShaderModule('shaders/17_shader_vertexbuffer_frag.spv')

        vertShaderStageInfo = _vk.PipelineShaderStageCreateInfo()
        vertShaderStageInfo.stage = _vk.VK_SHADER_STAGE_VERTEX_BIT
        vertShaderStageInfo.module = vertShaderModule
        vertShaderStageInfo.name = 'main'

        fragShaderStageInfo = _vk.PipelineShaderStageCreateInfo()
        fragShaderStageInfo.stage = _vk.VK_SHADER_STAGE_FRAGMENT_BIT
        fragShaderStageInfo.module = fragShaderModule
        fragShaderStageInfo.name = 'main'

        shaderStages = [vertShaderStageInfo, fragShaderStageInfo]

        vertexInputInfo = _vk.PipelineVertexInputStateCreateInfo()
        vertexInputInfo.vertexBindingDescriptions = [Vertex.getBindingDescription(), ]
        vertexInputInfo.vertexAttributeDescriptions = Vertex.getAttributeDescriptions()
        
        inputAssembly = _vk.PipelineInputAssemblyStateCreateInfo()
        inputAssembly.topology = _vk.VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST
        inputAssembly.primitiveRestartEnable = False

        viewport = _vk.Viewport()
        viewport.x = 0.0
        viewport.y = 0.0
        viewport.width = float(self.__swapChainExtent.width)
        viewport.height = float(self.__swapChainExtent.height)
        viewport.minDepth= 0.0
        viewport.maxDepth = 1.0

        scissor = _vk.Rect2D()
        scissor.offset = _vk.Offset2D(0, 0)
        scissor.extent = self.__swapChainExtent

        viewportState = _vk.PipelineViewportStateCreateInfo()
        viewportState.viewports = [viewport, ]
        viewportState.scissors = [scissor, ]

        rasterizer = _vk.PipelineRasterizationStateCreateInfo()
        rasterizer.depthClampEnable = False
        rasterizer.rasterizerDiscardEnable = False
        rasterizer.polygonMode = _vk.VK_POLYGON_MODE_FILL
        rasterizer.lineWidth = 1.0
        rasterizer.cullMode = _vk.VK_CULL_MODE_BACK_BIT
        rasterizer.frontFace = _vk.VK_FRONT_FACE_CLOCKWISE
        rasterizer.depthBiasEnable = False

        multisampling = _vk.PipelineMultisampleStateCreateInfo()
        multisampling.sampleShadingEnable = False
        multisampling.rasterizationSamples = _vk.VK_SAMPLE_COUNT_1_BIT

        colorBlendAttachment = _vk.PipelineColorBlendAttachmentState()
        colorBlendAttachment.colorWriteMask = _vk.VK_COLOR_COMPONENT_R_BIT | _vk.VK_COLOR_COMPONENT_G_BIT | _vk.VK_COLOR_COMPONENT_B_BIT | _vk.VK_COLOR_COMPONENT_A_BIT
        colorBlendAttachment.blendEnable = False

        colorBlending = _vk.PipelineColorBlendStateCreateInfo()
        colorBlending.logicOpEnable = False
        colorBlending.logicOp = _vk.VK_LOGIC_OP_COPY
        colorBlending.attachments = [colorBlendAttachment, ]
        colorBlending.blendConstants = [0.0, 0.0, 0.0, 0.0]

        pipelineLayoutInfo = _vk.PipelineLayoutCreateInfo()
        
        self.__pipelineLayout = self.__device.createPipelineLayout(pipelineLayoutInfo)

        pipelineInfo = _vk.GraphicsPipelineCreateInfo()
        pipelineInfo.stages = shaderStages
        pipelineInfo.vertexInputState = vertexInputInfo
        pipelineInfo.inputAssemblyState = inputAssembly
        pipelineInfo.viewportState = viewportState
        pipelineInfo.rasterizationState = rasterizer
        pipelineInfo.multisampleState = multisampling
        pipelineInfo.colorBlendState = colorBlending
        pipelineInfo.layout = self.__pipelineLayout
        pipelineInfo.renderPass = self.__renderPass
        pipelineInfo.subpass = 0
        #pipelineInfo.basePipelineHandle = _vk.Pipeline()

        graphicsPipelines = self.__device.createGraphicsPipelines(_vk.PipelineCache(), [pipelineInfo, ])
        self.__graphicsPipeline = graphicsPipelines[0]

        del vertShaderModule
        del fragShaderModule

    def __createFramebuffers(self):
        
        for i, iv in enumerate(self.__swapChainImageViews):
            framebufferInfo = _vk.FramebufferCreateInfo()
            framebufferInfo.renderPass = self.__renderPass
            framebufferInfo.attachments = [iv, ]
            framebufferInfo.width = self.__swapChainExtent.width
            framebufferInfo.height = self.__swapChainExtent.height
            framebufferInfo.layers = 1

            frameBuffer = self.__device.createFramebuffer(framebufferInfo)
            self.__swapChainFramebuffers.append(frameBuffer)

    def __createCommandPool(self):
        poolInfo = _vk.CommandPoolCreateInfo()
        poolInfo.queueFamilyIndex = self.__indices.graphicsFamily

        self.__commandPool = self.__device.createCommandPool(poolInfo)

    def __createVertexBuffer(self):
        bufferInfo = _vk.BufferCreateInfo()
        bufferInfo.size = vertices.nbytes
        bufferInfo.usage = _vk.VK_BUFFER_USAGE_VERTEX_BUFFER_BIT
        bufferInfo.sharingMode = _vk.VK_SHARING_MODE_EXCLUSIVE

        self.__vertexBuffer = self.__device.createBuffer(bufferInfo)
        
        memRequirements = self.__vertexBuffer.getMemoryRequirements()

        allocInfo = _vk.MemoryAllocateInfo()
        allocInfo.allocationSize = memRequirements.size
        allocInfo.memoryTypeIndex = self.__findMemoryType(memRequirements.memoryTypeBits, _vk.VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | _vk.VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
        
        self.__vertexBufferMemory = self.__device.allocateMemory(allocInfo)
        
        self.__vertexBuffer.bindMemory(self.__vertexBufferMemory, 0)
        
        self.__vertexBufferMemory.map(0, bufferInfo.size, 0)
        
        self.__vertexBufferMemory.copyFromBytes(vertices.tobytes(), vertices.nbytes)
        
        self.__vertexBufferMemory.unmap()

    def __findMemoryType(self, typeFilter, properties):
        memProperties = self.__physicalDevice.memoryProperties
        for i, memType in enumerate(memProperties.memoryTypes):
            if typeFilter & (1 << i) and (memType.propertyFlags & properties) == properties:
                return i

        raise Exception("failed to find suitable memory type!")

    def __createCommandBuffers(self):
        allocInfo = _vk.CommandBufferAllocateInfo()
        allocInfo.commandPool = self.__commandPool
        allocInfo.level = _vk.VK_COMMAND_BUFFER_LEVEL_PRIMARY
        allocInfo.commandBufferCount = len(self.__swapChainFramebuffers)

        self.__commandBuffers = self.__device.allocateCommandBuffers(allocInfo)

        for i, cmdBuffer in enumerate(self.__commandBuffers):
            #cmdBuffer = self.__commandBuffers[i]

            beginInfo = _vk.CommandBufferBeginInfo()
            beginInfo.flags = _vk.VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT

            cmdBuffer.begin(beginInfo)

            renderPassInfo = _vk.RenderPassBeginInfo()
            renderPassInfo.renderPass = self.__renderPass
            renderPassInfo.framebuffer = self.__swapChainFramebuffers[i]
            renderPassInfo.renderArea.offset = _vk.Offset2D(0, 0)
            renderPassInfo.renderArea.extent = self.__swapChainExtent
            renderPassInfo.clearValues = [_vk.ClearValue(_vk.ClearColorValue(0.0, 0.0, 0.0, 1.0)),]

            cmdBuffer.beginRenderPass(renderPassInfo, _vk.VK_SUBPASS_CONTENTS_INLINE)

            cmdBuffer.bindPipeline(_vk.VK_PIPELINE_BIND_POINT_GRAPHICS, self.__graphicsPipeline)

            cmdBuffer.bindVertexBuffer(0, [self.__vertexBuffer, ], [0, ])

            cmdBuffer.draw(3, 1, 0, 0)

            cmdBuffer.endRenderPass()

            cmdBuffer.end()

    def __createSyncObjects(self):
        semaphoreInfo = _vk.SemaphoreCreateInfo()
        fenceInfo = _vk.FenceCreateInfo()
        fenceInfo.flags = _vk.VK_FENCE_CREATE_SIGNALED_BIT
        for i in range(len(self.__swapChainFramebuffers)):
            self.__imageAvailableSemaphores.append(self.__device.createSemaphore(semaphoreInfo))
            self.__renderFinishedSemaphores.append(self.__device.createSemaphore(semaphoreInfo))
            self.__inFlightFences.append(self.__device.createFence(fenceInfo))

    def __drawFrame(self):
        if not self.isExposed():
            return

        fence = self.__inFlightFences[self.__currentFrame]
        fence.wait(_vk.UINT64_MAX)
        fence.reset()

        imageIndex = self.__swapChain.acquireNextImageKHR(_vk.UINT64_MAX, self.__imageAvailableSemaphores[self.__currentFrame])

        waitSemaphores = [self.__imageAvailableSemaphores[self.__currentFrame], ]
        signalSemaphores = [self.__renderFinishedSemaphores[self.__currentFrame], ]

        submitInfo = _vk.SubmitInfo()
        submitInfo.waitDstStageMask = [_vk.VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, ]
        submitInfo.waitSemaphores = waitSemaphores
        submitInfo.commandBuffers = [self.__commandBuffers[self.__currentFrame], ]
        submitInfo.signalSemaphores = signalSemaphores

        self.__graphicQueue.submit([submitInfo, ], fence)

        presentInfo = _vk.PresentInfoKHR()
        presentInfo.waitSemaphores = signalSemaphores
        presentInfo.swapchains = [self.__swapChain, ]
        presentInfo.imageIndices = [imageIndex, ]

        self.__presentQueue.presentKHR(presentInfo)
        self.__presentQueue.waitIdle()

        self.__currentFrame = (self.__currentFrame + 1) % len(self.__swapChainFramebuffers)
        
        self.requestUpdate()

    def __chooseSwapSurfaceFormat(self, formats):
        if len(formats) == 1 and formats[0].format == _vk.VK_FORMAT_UNDEFINED:
            return [_vk.VK_FORMAT_B8G8R8_UNORM, _vk.VK_COLOR_SPACE_SRGB_NONLINEAR_KHR]

        for i in formats:
            if i.format == _vk.VK_FORMAT_B8G8R8_UNORM and i.colorSpace == _vk.VK_COLOR_SPACE_SRGB_NONLINEAR_KHR:
                return i

        return formats[0]

    def __chooseSwapPresentMode(self, presentModes):
        bestMode = _vk.VK_PRESENT_MODE_FIFO_KHR

        for i in presentModes:
            if i == _vk.VK_PRESENT_MODE_FIFO_KHR:
                return i
            elif i == _vk.VK_PRESENT_MODE_MAILBOX_KHR:
                return i
            elif i == _vk.VK_PRESENT_MODE_IMMEDIATE_KHR:
                return i

        return bestMode

    def __chooseSwapExtent(self, capabilities):
        width = max(capabilities.minImageExtent.width, min(capabilities.maxImageExtent.width, self.width()))
        height = max(capabilities.minImageExtent.height, min(capabilities.maxImageExtent.height, self.height()))
        return _vk.Extent2D(width, height)

    def __querySwapChainSupport(self, device):
        detail = SwapChainSupportDetails()

        detail.capabilities = device.getSurfaceCapabilitiesKHR(self.__surface)
        detail.formats = device.getSurfaceFormatsKHR(self.__surface)
        detail.presentModes = device.getSurfacePresentModeKHR(self.__surface)
        return detail

    def __isDeviceSuitable(self, device):
        indices = self.__findQueueFamilies(device)

        extensionsSupported = self.__checkDeviceExtensionSupport(device)

        swapChainAdequate = False
        if extensionsSupported:
            swapChainSupport = self.__querySwapChainSupport(device)
            swapChainAdequate = (swapChainSupport.formats is not None) and (swapChainSupport.presentModes is not None)

        return indices.isComplete and extensionsSupported and swapChainAdequate

    def __checkDeviceExtensionSupport(self, device):
        availableExtensions = device.getExtensionProperties()

        aen = [i.extensionName for i in availableExtensions]
        for i in deviceExtensions:
            if i not in aen:
                return False

        return True

    def __findQueueFamilies(self, device):
        indices = QueueFamilyIndices()

        for i, prop in enumerate(device.queueFamilyProperties):
            if prop.queueCount > 0 and prop.queueFlags & _vk.VK_QUEUE_GRAPHICS_BIT:
                indices.graphicsFamily = i

            presentSupport = device.getSurfaceSupportKHR(self.__surface, i)

            if prop.queueCount > 0 and presentSupport:
                indices.presentFamily = i
            
            if indices.isComplete:
                break

        return indices

    def __getRequiredExtensions(self):
        extensionNames = [e.extensionName for e in _vk.Instance.getExtensionProperties()]
        if enableValidationLayers:
            if _vk.VK_EXT_DEBUG_UTILS_EXTENSION_NAME not in extensionNames:
                extensionNames.append(_vk.VK_EXT_DEBUG_UTILS_EXTENSION_NAME)

        return extensionNames

    def __checkValidationLayerSupport(self):
        availableLayers = _vk.Instance.getLayerProperties()

        for layer in validationLayers:
            layerfound = False

            for layerProp in availableLayers:
                if layer == layerProp.layerName:
                    layerfound = True
                    break
            return layerfound

        return False

    def event(self, event):
        if event.type() == QtCore.QEvent.Resize and self.isExposed():
            if event.size() != event.oldSize():
                self.__recreateSwapChain()
                self.__drawFrame()

        elif event.type() == QtCore.QEvent.UpdateRequest:
            self.__drawFrame()
        elif event.type() == QtCore.QEvent.Expose:
            self.requestUpdate()

        return super(HelloTriangleApplication, self).event(event)



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


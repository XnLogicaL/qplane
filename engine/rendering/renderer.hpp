// This file is a part of the QPlane project
// Copyright (C) 2025 XnLogicaL
// Licensed under the GNU General Public License v3.0

#ifndef QPL_RENDERER_HPP
#define QPL_RENDERER_HPP

#include <array>     // For std::array
#include <vector>    // For std::vector
#include <set>       // For std::set
#include <cstring>   // For std::strcmp
#include <optional>  // For std::optional
#include <limits>    // For std::numeric_limits
#include <algorithm> // For std::clamp
#include <fstream>   // For std::ifstream
#include <filesystem>

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include <vulkan/vulkan.h>
#include <magic_enum/magic_enum.hpp>

#include <events/event.hpp>
#include <core/core.hpp>
#include <window.hpp>

namespace qpl {

struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;
  std::optional<uint32_t> presentFamily;

  QPL_INLINE bool IsComplete() {
    return graphicsFamily.has_value() && presentFamily.has_value();
  }
};

struct SwapChainSupportDetails {
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
};

QPL_INLINE std::vector<char> LoadShader(const std::string& filepath) {
  std::ifstream file(filepath, std::ios::binary | std::ios::ate);
  if (!file.is_open()) {
    QPL_CORE_ASSERT(false && "Failed to open shader file");
  }

  size_t fileSize = (size_t)file.tellg();
  std::vector<char> buffer(fileSize);
  file.seekg(0);
  file.read(buffer.data(), fileSize);
  return buffer;
}

//
// ---- Renderer --------------------------------
//
class Renderer {
public:
  Renderer(WindowContext&);
  ~Renderer();

  void Render();
  void Shutdown();

public:
#ifdef NDEBUG
  static constexpr bool EnableValidationLayers = false;
#else
  static constexpr bool EnableValidationLayers = false;
#endif

  static constexpr std::array<const char*, 1> ValidationLayers = {
    "VK_LAYER_KHRONOS_validation",
  };

  static constexpr std::array<const char*, 2> DeviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
  };

  static constexpr std::array<VkDynamicState, 2> DynamicStates = {
    VK_DYNAMIC_STATE_VIEWPORT,
    VK_DYNAMIC_STATE_SCISSOR,
  };

private:
  void CreateInstance();
  void CreateDebugMessenger();
  void CreateSurface();
  void CreateLogicalDevice();
  void CreateSwapChain();
  void CreateImageViews();
  void CreateRenderPass();
  void CreateGraphicsPipeline();
  void CreateFrameBuffers();
  void CreateCommandPool();
  void CreateCommandBuffer();
  void CreateSyncObjects();

  VkShaderModule CreateShaderModule(const std::vector<char>& code);

  bool CheckValidationLayerSupport();
  bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
  bool CheckDeviceSuitability(VkPhysicalDevice device);

  void ChoosePhysicalDevice();
  VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
  VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
  VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

  QueueFamilyIndices QueryQueueFamilies(VkPhysicalDevice device);
  SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

  void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

private:
  WindowContext& mWindow;

  VkInstance mInstance;
  VkDebugUtilsMessengerEXT mDebugMessenger;
  VkDevice mDevice;
  VkPhysicalDevice mPhysicalDevice;
  VkQueue mGraphicsQueue;
  VkQueue mPresentQueue;
  VkSurfaceKHR mSurface;
  VkSwapchainKHR mSwapChain;
  VkFormat mSwapChainImageFormat;
  VkExtent2D mSwapChainExtent;
  VkRenderPass mRenderPass;
  VkPipelineLayout mPipelineLayout;
  VkPipeline mGraphicsPipeline;
  VkCommandPool mCommandPool;
  VkCommandBuffer mCommandBuffer;
  VkSemaphore mImageAvailableSemaphore;
  VkSemaphore mRenderFinishedSemaphore;
  VkFence mInFlightFence;

  std::vector<VkImage> mSwapChainImages;
  std::vector<VkImageView> mSwapChainImageViews;
  std::vector<VkFramebuffer> mSwapChainFramebuffers;
};

} // namespace qpl

#endif

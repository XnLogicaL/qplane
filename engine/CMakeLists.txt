# Set the minimum CMake version
cmake_minimum_required(VERSION 3.14)

# Project name and language
project(qplane_engine LANGUAGES CXX)

# Include your engine source files, excluding vendor directories
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Filter out any source files under vendor/
foreach(SOURCE_FILE ${ENGINE_SOURCES})
  if (SOURCE_FILE MATCHES "[/\\]vendor[/\\]")
    list(REMOVE_ITEM ENGINE_SOURCES ${SOURCE_FILE})
  endif()
endforeach()

# Add the engine library target
add_library(qplane_engine STATIC ${ENGINE_SOURCES})

# Ensure the build is using C++23 after defining the target
target_compile_features(qplane_engine PUBLIC cxx_std_23)

# Set Vulkan include directory
set(VULKAN_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/Vulkan-Headers/include)

# Vulkan Headers (header-only)
add_library(VULKAN_HEADERS INTERFACE)
target_include_directories(VULKAN_HEADERS INTERFACE ${VULKAN_INCLUDE_DIR})
target_include_directories(qplane_engine PUBLIC ${VULKAN_INCLUDE_DIR})
add_library(Vulkan::Headers ALIAS VULKAN_HEADERS)

# Tell Vulkan-Loader to build its actual static/shared loader
set(BUILD_LOADER ON CACHE BOOL "" FORCE)
set(BUILD_STATIC_LOADER ON CACHE BOOL "" FORCE)  # Builds static lib
set(BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_WSI_XLIB_SUPPORT OFF CACHE BOOL "" FORCE)  # Optional

# Add Vulkan-Loader as a subdirectory (it should be a CMake project in vendor)
add_subdirectory(vendor/Vulkan-Loader)

# Create Vulkan::Vulkan alias for convenience
add_library(Vulkan::Vulkan ALIAS vulkan)

# Ensure SDL is built statically
set(SDL_STATIC ON CACHE BOOL "Force static linking for SDL3" FORCE)
set(SDL_SHARED OFF CACHE BOOL "Force static linking for SDL3" FORCE) # FUCK DYNAMIC LINKAGE

# Define SDL_STATIC before adding SDL subdirectory to force static linking
target_compile_definitions(qplane_engine PUBLIC SDL_STATIC)

# Add SDL3 as a subdirectory (it should be a CMake project in vendor)
add_subdirectory(vendor/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendor/magic_enum)

# Link Vulkan and SDL3 to the engine
target_link_libraries(qplane_engine PUBLIC SDL3::SDL3 Vulkan::Vulkan magic_enum)

# Include directories for the engine, add your engine's headers
target_include_directories(qplane_engine PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Optionally: For Vulkan/SDL Loader & Window handling, link them directly in your executable or library
# Make sure Vulkan-Loader and Vulkan-Headers are linked correctly
target_link_libraries(qplane_engine PRIVATE Vulkan::Headers)

# Ensure the build type is correct (Release, Debug, etc)
set(CMAKE_BUILD_TYPE Release)

# If you need to force the target to compile as static or with certain flags
set(CMAKE_EXE_LINKER_FLAGS "-static")

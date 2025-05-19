// This file is a part of the QPlane project
// Copyright (C) 2025 XnLogicaL
// Licensed under the GNU General Public License v3.0

#ifndef QPL_WINDOW_HPP
#define QPL_WINDOW_HPP

#include <vector>
#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include <vulkan/vulkan.h>
#include <core/core.hpp>

namespace qpl {

//
// ---- Window Config ---------------------------------
//
// This class contains all information necessary in order to initialize the main window of a
// game instance.
//
struct WindowConfig {
  int width, height;
  const char* title;
  bool fullscreen;
};

//
// ---- Window Context --------------------------------
//
class WindowContext final {
public:
  QPL_INLINE WindowContext(const WindowConfig& windowConfig)
    : config(windowConfig) {
    uint64_t SDLFlags = 0;

    // Fullscreen flag
    if (windowConfig.fullscreen) {
      SDLFlags |= SDL_WINDOW_FULLSCREEN;
    }

    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Initialize SDL_Window
    window = SDL_CreateWindow(
      windowConfig.title, windowConfig.width, windowConfig.height, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE | SDLFlags
    );
  }

  QPL_INLINE ~WindowContext() {
    SDL_DestroyWindow(window);
    SDL_Quit();
  }

  // Returns a pointer to the SDL window instance.
  QPL_INLINE SDL_Window* GetSDLWindow() const {
    return window;
  }

  QPL_INLINE const WindowConfig& GetConfig() const {
    return config;
  }

private:
  // Reference to window configuration
  const WindowConfig& config;

  // SDL state
  SDL_Window* window;
};

} // namespace qpl

#endif

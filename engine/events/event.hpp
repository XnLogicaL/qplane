// This file is a part of the QPlane project
// Copyright (C) 2025 XnLogicaL
// Licensed under the GNU General Public License v3.0

#ifndef QPL_EVENT_HPP
#define QPL_EVENT_HPP

#include <type_traits>

#include <SDL3/SDL.h>
#include <core/core.hpp>

namespace qpl {

enum class Event : uint32_t {
  // SDL Events
  SDL_First = SDL_EVENT_FIRST, // Sentinel

  SDL_Quit = SDL_EVENT_QUIT,
  SDL_WindowResize = SDL_EVENT_WINDOW_RESIZED,

  SDL_Last = SDL_EVENT_LAST, // Sentinel

  // Engine Events
  Engine_First = 0x9000, // Sentinel
};

} // namespace qpl

#endif

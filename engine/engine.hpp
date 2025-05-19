// This file is a part of the QPlane project
// Copyright (C) 2025 XnLogicaL
// Licensed under the GNU General Public License v3.0

#ifndef QPL_ENGINE_HPP
#define QPL_ENGINE_HPP

#include <core/core.hpp>
#include <events/event.hpp>
#include <events/event-dispatcher.hpp>
#include <rendering/renderer.hpp>
#include "window.hpp"

namespace qpl {

//
// ---- Engine Class ---------------------------------
//
class Engine final {
public:
  QPL_INLINE Engine(WindowConfig& windowConfig)
    : mWindowContext(windowConfig),
      mRenderer(mWindowContext) {}

  void Start();

  QPL_INLINE bool IsRunning() const {
    return mIsRunning;
  }

private:
  void Init();
  void PollEvents();
  void Update();
  void Render();
  void Shutdown();

private:
  // Main flag that controls the event loop.
  bool mIsRunning = false;

  // Window
  WindowContext mWindowContext;

  // Event handler
  EventDispatcher mEventDispatcher;

  // Renderer
  Renderer mRenderer;
};

} // namespace qpl

#endif

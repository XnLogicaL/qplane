// This file is a part of the QPlane project
// Copyright (C) 2025 XnLogicaL
// Licensed under the GNU General Public License v3.0

#include "engine.hpp"

namespace qpl {

void Engine::PollEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    mEventDispatcher.Dispatch((Event)event.type, &event);
  }
}

void Engine::Init() {
  mIsRunning = true;

  // Subscribe to events
  mEventDispatcher.Subscribe(Event::SDL_Quit, [this](void*) { mIsRunning = false; });
}

void Engine::Update() {}

void Engine::Render() {
  mRenderer.Render();
}

void Engine::Shutdown() {
  mRenderer.Shutdown();
}

void Engine::Start() {
  Init();

  while (IsRunning()) {
    PollEvents();
    Update();
    Render();
  }

  Shutdown();
}

} // namespace qpl

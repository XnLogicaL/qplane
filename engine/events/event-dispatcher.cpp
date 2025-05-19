// This file is a part of the QPlane project
// Copyright (C) 2025 XnLogicaL
// Licensed under the GNU General Public License v3.0

#include "event-dispatcher.hpp"

namespace qpl {

void EventDispatcher::Subscribe(Event event, EventCallback&& callback) {
  mSubscribers[event].push_back(std::move(callback));
}

void EventDispatcher::Dispatch(const Event& event, void* pEvent) {
  for (const EventCallback& callback : mSubscribers[event]) {
    callback(pEvent);
  }
}

} // namespace qpl

// This file is a part of the QPlane project
// Copyright (C) 2025 XnLogicaL
// Licensed under the GNU General Public License v3.0

#ifndef EVENT_DISPATCHER_HPP
#define EVENT_DISPATCHER_HPP

#include <vector>
#include <bit>
#include <unordered_map>
#include <functional>
#include <typeindex>

#include <core/core.hpp>
#include "event.hpp"

namespace qpl {

//
// ---- Event Dispatcher --------------------------------
//
class EventDispatcher final {
public:
  using EventCallback = std::function<void(void*)>;

  void Subscribe(Event event, EventCallback&& callback);

  void Dispatch(const Event& event, void* pEvent);

private:
  std::unordered_map<Event, std::vector<EventCallback>> mSubscribers;
};

} // namespace qpl

#endif

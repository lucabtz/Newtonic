/*
 *   Newtonic
 *   Copyright (C) 2019 Luca "ekardnam" Bertozzi <luca.bertozzi11@studio.unibo.it>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "eventbus.h"

#include "util.h"
#include "core.h"

namespace Newtonic
{
  std::unordered_map<EventType, ListenerGroup> EventBus::s_listeners;
  std::queue<std::shared_ptr<Event>> EventBus::s_eventQueue;

  void EventBus::Push(std::shared_ptr<Event> event)
  {
    NW_WRAP_DEBUG(Core::GetCoreLogger().Debug(FormatString("Event: %s pushed", event->GetLogMessage().c_str())));
    s_eventQueue.push(event);
  }

  void EventBus::Listen(EventType type, const EventListener & listener)
  {
    s_listeners[type].push_back(listener);
  }

  void EventBus::DispatchAll()
  {
    while (!s_eventQueue.empty()) DispatchOne();
  }

  void EventBus::DispatchOne()
  {
    if (s_eventQueue.empty())
    {
      NW_WRAP_DEBUG(Core::GetCoreLogger().Debug("Nothing to dispatch"));
      return;
    }
    std::shared_ptr<Event> event = s_eventQueue.front();
    s_eventQueue.pop();
    for (const auto & listener : s_listeners[event->GetType()])
    {
      NW_WRAP_DEBUG(Core::GetCoreLogger().Debug(FormatString("Event: %s dispatched", event->GetLogMessage().c_str()))); 
      listener(event);
    }
  }
}

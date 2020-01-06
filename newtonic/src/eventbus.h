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

#pragma once

#include "event.h"

#include <unordered_map>
#include <memory>
#include <functional>
#include <vector>
#include <queue>

namespace Newtonic
{
  using EventListener = std::function<void(std::shared_ptr<Event>)>;
  using ListenerGroup = std::vector<EventListener>;

  class EventBus
  {
  public:
    /**
     * Pushes the event in the event queue
     */
    static void Push(std::shared_ptr<Event> event);

    /**
     * Listens for events of type type with the given Newtonic::EventListener
     */
    static void Listen(EventType type, const EventListener & listener);

    /**
     * Dispatches all events in the queue to the listeners
     */
    static void DispatchAll();

    /**
     * Dispatches one event in the queue to the listeners
     */
    static void DispatchOne();

  private:
    static std::unordered_map<EventType, ListenerGroup> s_listeners;
    static std::queue<std::shared_ptr<Event>> s_eventQueue;
  };
}

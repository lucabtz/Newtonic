/*
 *   Newtonic - Graphics for Physics
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
#include <functional>
#include <memory>
#include <queue>
#ifndef _MESSAGE_TYPEDEFS_H
#define _MESSAGE_TYPEDEFS_H
 namespace Newtonic
 {
   class Message;

   typedef std::shared_ptr<Message> MessagePtr;
   typedef std::queue<MessagePtr> MessageQueue ;
   typedef std::function<void(MessagePtr)> MailBox;

   enum class MessageType
   {
     EVENT_SCREEN_RESIZED = 0x0,
   };
 }

 #endif // _MESSAGE_TYPEDEFS_H

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

 #ifndef _MESSAGE_BUS_H
 #define _MESSAGE_BUS_H

 #include "message.h"

 #include <queue>
 #include <memory>
 #include <vector>
 #include <string>

 namespace Newtonic
 {

   void ConsoleLog(const char * s);
   void LogFromSender(const char * sender, const char * msg);

   class MessageBus
   {
     std::queue<std::shared_ptr<Message>> m_messageQueue;
     std::vector<void (*)(std::shared_ptr<Message>)> m_mailBoxes;

   public:
     void PostMessage(std::shared_ptr<Message> msg, std::string sender);
     void RegisterMailBox(void (*mailBox)(std::shared_ptr<Message>));

     void Work();

   };

 }

 #endif // _MESSAGE_BUS_H

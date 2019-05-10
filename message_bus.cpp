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

 #include "message_bus.h"

 #include "message.h"

 #include <stdio.h>

 namespace Newtonic
 {
   void ConsoleLog(const char * s)
   {
     printf("[CONSOLE] %s\n", s);
   }

   void LogFromSender(const char * sender, const char * msg)
   {
     printf("[CONSOLE] FROM: %s MESSAGE: %s\n", sender, msg);
   }

   void MessageBus::PostMessage(
     MessagePtr msg,
     std::string sender)
   {
     LogFromSender(sender.c_str(), msg->GetLogMessage().c_str());
     m_messageQueues[msg->GetType()].push(msg);
   }

   void MessageBus::RegisterMailBox(MessageType msgType, MailBox mailBox)
   {
     m_mailBoxes[msgType].push_back(mailBox);
   }

   void MessageBus::Work()
   {
     for (auto & pair : m_messageQueues)
     {
       MessageType msgType = pair.first;
       MessageQueue queue = pair.second;

       while (!queue.empty())
       {
         MessagePtr msg = queue.front();
         queue.pop();
         for (auto & mb : m_mailBoxes[msgType]) mb(msg);
       }
     }
   }

 }

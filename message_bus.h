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

 #include <vector>
 #include <string>
 #include <map>

 #include "message_typedefs.h"

 #include "message.h"

 namespace Newtonic
 {

   class Message;

   typedef std::shared_ptr<Message> MessagePtr;
   typedef std::queue<MessagePtr> MessageQueue ;
   typedef std::function<void(MessagePtr)> MailBox;

   void ConsoleLog(const char * s);
   void LogFromSender(const char * sender, const char * msg);

   class MessageBus
   {
     std::map<MessageType, MessageQueue> m_messageQueues;
     std::map<MessageType, std::vector<MailBox>> m_mailBoxes;

   public:
     void PostMessage(MessagePtr msg, std::string sender);
     void RegisterMailBox(MessageType msgType, MailBox mailBox);

     void Work();

   };

 }

 #endif // _MESSAGE_BUS_H

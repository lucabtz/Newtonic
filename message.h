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

#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <string>
#include <sstream>

#include "message_typedefs.h"
#include "common.h"

namespace Newtonic
{

  class Message
  {
    MessageType m_type;

  public:
    Message(MessageType type) : m_type(type) {};
    MessageType GetType() { return m_type; }
    virtual std::string GetLogMessage() const { return ""; }
  };

  template <typename MessageT>
  std::shared_ptr<MessageT> MessageCast(MessagePtr msg)
  {
    return std::dynamic_pointer_cast<MessageT>(msg);
  }

  class EventScreenResizedMessage : public Message
  {
    Viewport m_newSize;
    Viewport m_oldSize;

  public:
    EventScreenResizedMessage(Viewport _old, Viewport _new) :
      Message(MessageType::EVENT_SCREEN_RESIZED),
      m_newSize(_new),
      m_oldSize(_old) {};

    Viewport GetNewSize() { return m_newSize; }
    Viewport GetOldSize() { return m_oldSize; }

    std::string GetLogMessage() const override
    {
      std::stringstream res;
      res <<
        "Window resized from (" <<
        m_oldSize.width <<
        "," <<
        m_oldSize.height <<
        ") to (" <<
        m_newSize.width <<
        "," <<
        m_newSize.height <<
         ")";
      return res.str();
    }

  };

}


 #endif // _MESSAGE_H

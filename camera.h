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

#ifndef _CAMERA_H
#define _CAMERA_H

#include <iostream>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "message.h"
#include "common.h"
#include "engine.h"
#include "transform.h"

namespace Newtonic
{
  class MessageBus;

  class Camera
  {
    Viewport m_viewport;
    std::unique_ptr<Transform> m_cameraTransform;

    glm::mat4 m_projMatrix;

    MessageBus *m_msgBus;

  public:
    Camera()
    {
      m_msgBus = g_engine->GetMessageBus();
      m_msgBus->RegisterMailBox(MessageType::EVENT_SCREEN_RESIZED,
        [this](MessagePtr msg)
        {
          auto event = MessageCast<EventScreenResizedMessage>(msg);
          this->SetViewport(event->GetNewSize());
        }
      );
      SetViewport(g_engine->GetViewport());
      m_projMatrix = glm::perspective(
        glm::radians(45.0f),
        (float)m_viewport.width / (float)m_viewport.height,
        0.1f,
        100.0f
      );
    }

    glm::mat4 GetProjection() const;
    glm::mat4 GetView() const;

    void SetViewport(Viewport new_)
    {
      m_viewport = new_;
    }
  };
}

#endif // _CAMERA_H

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

 #include "input.h"

 #include "engine.h"
 #include "message.h"

 #include <iostream>

 namespace Newtonic
 {
   void KeyCallback(
     GLFWwindow * wnd, int scancode, int key, int action, int modes)
   {
     auto im = g_engine->GetInputManager();
     if (action == GLFW_PRESS)        im->SetStatus(key, true);
     else if (action == GLFW_RELEASE) im->SetStatus(key, false);
   }

   Input::Input(GLFWwindow * wnd) :
    m_wnd(wnd)
   {
     m_keyStatuses = new bool[200];      //TODO check the 200
     for (int i = 0; i < 200; ++i) m_keyStatuses[i] = false;
     glfwSetKeyCallback(m_wnd, KeyCallback);

     m_mouseBtnStatuses = new bool[5];
     for (int i = 0; i < 5; ++i) m_mouseBtnStatuses[i] = false;

     glfwSetInputMode(m_wnd, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

     m_vp = g_engine->GetViewport();

     g_engine->GetMessageBus()->RegisterMailBox(MessageType::EVENT_SCREEN_RESIZED,
       [this](MessagePtr msg)
       {
         auto event = MessageCast<EventScreenResizedMessage>(msg);
         Viewport newVp = event->GetNewSize();
         this->m_vp = newVp;
         std::cout << "[INPUT] Updating the viewport to "
                   << newVp.width << ", " << newVp.height << std::endl;
       },
       "input handle screen resize"
     );
   }

   void Input::Work()
   {
     if (m_hiddenCursorMode)
     {
       int centerX = m_vp.width / 2, centerY = m_vp.height / 2;
       double mouseX, mouseY;
       int ix, iy;
       glfwGetCursorPos(m_wnd, &mouseX, &mouseY);
       ix = (int) mouseX - centerX, iy = (int) mouseY - centerY;

       m_axisHorizontal = ix, m_axisVertical = iy;

       glfwSetCursorPos(m_wnd, centerX, centerY);
     }
   }

 }

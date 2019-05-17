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

 #ifndef _INPUT_H
 #define _INPUT_H

 #include <GL/glew.h>
 #include <GLFW/glfw3.h>

 #include <iostream>

 #include "common.h"

 namespace Newtonic
 {
   typedef int Key;
   typedef int MouseAxis;

   constexpr MouseAxis HORIZONTAL = 0x0,
                       VERTICAL = 0x1;


   class Input
   {
     GLFWwindow *m_wnd;
     bool * m_keyStatuses;
     bool * m_mouseBtnStatuses;

     bool m_hiddenCursorMode = true;
     Viewport m_vp;

     int m_axisHorizontal = 0;
     int m_axisVertical = 0;

     void SetStatus(Key k, bool status)
     {
       m_keyStatuses[k] = status;
       std::cout << "[INPUT] Key status " << k << " " << status << std::endl;
     }
   public:
     friend void KeyCallback(
       GLFWwindow * wnd, int scancode, int key, int action, int modes);

     Input(GLFWwindow * wnd);
     ~Input() { delete[] m_keyStatuses; delete[] m_mouseBtnStatuses; }

     void Work();

     bool IsKeyDown(Key k) { return m_keyStatuses[k]; }
     bool IsKeyUp(Key k) { return !IsKeyDown(k); }

     int GetAxis(MouseAxis axis)
     {
       switch (axis)
       {
       case HORIZONTAL:
          return m_axisHorizontal;
       case VERTICAL:
          return m_axisVertical;
       }

       return 0;
     }

     void SetHiddenCursorMode(bool mode)
     {
       m_hiddenCursorMode = mode;
       if (m_hiddenCursorMode) glfwSetInputMode(m_wnd, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
       else                    glfwSetInputMode(m_wnd, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
     }

   };
 }

 #endif

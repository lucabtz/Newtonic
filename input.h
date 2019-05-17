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
   typedef int Btn;
   typedef int MouseAxis;

   constexpr MouseAxis HORIZONTAL = 0x0,
                       VERTICAL = 0x1;

   constexpr int MAX_KEYS = 200, MAX_BTNS = 5;

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
       m_keyStatuses[k % MAX_KEYS] = status;
       std::cout << "[INPUT] Key status " << k << " " << status << std::endl;
     }
     void SetBtnStatus(Btn k, bool status)
     {
       m_mouseBtnStatuses[k % MAX_BTNS] = status;
       std::cout << "[INPUT] Mouse btn status " << k << " " << status << std::endl;
     }
   public:
     friend void KeyCallback(
       GLFWwindow * wnd, int scancode, int key, int action, int modes
     );

     friend void MouseButtonCallback(
       GLFWwindow * wnd, int button, int action, int modes
     );

     /**
      * Constructor for the input manager.
      * Engine instanciates this for you
      * @param wnd the GLFW window
      */
     Input(GLFWwindow * wnd);
     ~Input() { delete[] m_keyStatuses; delete[] m_mouseBtnStatuses; }

     /**
      * Update call for the input manager
      */
     void Work();

     /**
      * Checks if the given key is being pressed
      * @param  k the key's key code
      * @return   a boolean value that answers the question "is key down?"
      */
     bool IsKeyDown(Key k) { return m_keyStatuses[k % MAX_KEYS]; }
     /**
      * Checks if the given key is NOT being pressed
      * @param  k the key's key code
      * @return   a boolean value that answers the question "is key up?"
      */
     bool IsKeyUp(Key k) { return !IsKeyDown(k); }
     /**
      * Checks if the given mouse button is being pressed
      * @param  k the mouse button code
      * @return   a boolean that answers the question "is the button being pressed"
      */
     bool IsButtonDown(Btn k) { return m_mouseBtnStatuses[k % MAX_BTNS]; }
     /**
      * Returns how "fast" the mouse is moving on a certain axis.
      * Should be used in hidden cursor mode only
      * @param  axis the axis code. Can either be Newtonic::VERTICAL, Newtonic::HORIZONTAL
      * @return      how fast the mouse is noving on such direction
      */
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

     /**
      * Sets the hidden cursor mode i.e. cursor is not visible and GetAxis works good
      * @param mode true means hidden cursor mode is active
      */
     void SetHiddenCursorMode(bool mode)
     {
       m_hiddenCursorMode = mode;
       if (m_hiddenCursorMode) glfwSetInputMode(m_wnd, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
       else                    glfwSetInputMode(m_wnd, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
     }
   };
 }

 #endif

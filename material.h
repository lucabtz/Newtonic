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

#include "color.h"
#include "OBJ_Loader.h"

 namespace Newtonic
 {
   struct Material
   {
     Color m_ambientColor;
     Color m_diffuseColor;
     Color m_specularColor;
     float m_specularExponent;

     Material(objl::Material & m)
     {
       #define COPY_VEC(my, other) my.x = other.X, my.y = other.Y, my.z = other.Z
       COPY_VEC(m_ambientColor, m.Ka);
       COPY_VEC(m_diffuseColor, m.Kd);
       COPY_VEC(m_specularColor, m.Ks);
       #undef COPY_VEC
       m_specularExponent = m.Ns;
     }
   };
 }

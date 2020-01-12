/*
 *   Newtonic
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

#pragma once

#include "../serialization.h"
#include "datacomponent.h"
#include "../transform.h"

namespace Newtonic
{
  class TransformComponent : public DataComponent
  {
  public:
    Transform & GetTransform() { return m_transform; }
    void SetTransform(const Transform & transform) { m_transform = transform; }
  private:
    Transform m_transform;

    NW_PRIVATE_SERIALIZATION;
    template<typename Archive>
    void serialize(Archive & ar)
    {
      ar(m_transform);
    }
  };
}

CEREAL_REGISTER_TYPE(Newtonic::TransformComponent)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Newtonic::DataComponent, Newtonic::TransformComponent)

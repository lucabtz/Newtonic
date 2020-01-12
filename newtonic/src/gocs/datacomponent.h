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
#include "component.h"

namespace Newtonic
{
  class DataComponent : public Component
  {
  public:
    void Update(float dt) override {};
    void LateUpdate(float dt) override {};
    void Render() override {};
  };

}

CEREAL_REGISTER_TYPE(Newtonic::DataComponent)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Newtonic::Component, Newtonic::DataComponent)

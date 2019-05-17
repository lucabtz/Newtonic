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

#include "actor.h"
#include "behaviour.h"

namespace Newtonic
{

  void Actor::AddBehaviour(std::shared_ptr<Behaviour> && behaviour)
  {
    behaviour->SetActor(this);
    m_behaviours.push_back(std::move(behaviour));
  }

  void Actor::Update(float dt)
  {
    for (auto & b : m_behaviours) b->Update(dt);
  }

  void Actor::Render()
  {
    for (auto & b : m_behaviours) b->Render();
  }

  void Actor::Init()
  {
    for (auto & b : m_behaviours) b->Init();
  }

}

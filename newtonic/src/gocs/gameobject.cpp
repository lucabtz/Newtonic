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

#include "gameobject.h"

namespace Newtonic
{
  void GameObject::Update(float dt)
  {
    for (const auto & component : m_components) component->Update(dt);
  }

  void GameObject::LateUpdate(float dt)
  {
    for (const auto & component : m_components) component->LateUpdate(dt);
  }

  void GameObject::Render()
  {
    for (const auto & component : m_components) component->Render();
  }

  GameObject * GameObject::GetParent() const
  {
    return m_parent;
  }

  void GameObject::InitChildren()
  {
    for (const auto & child : m_children) child->m_parent = this;
  }

  void GameObject::InitComponents()
  {
    for (const auto & component : m_components) component->m_gameObject = this;
  }

  void GameObject::AddChild(std::unique_ptr<GameObject> child)
  {
    child->m_parent = this;
    m_children.push_back(std::move(child));
  }

  void GameObject::AddComponent(std::unique_ptr<Component> component)
  {
    component->m_gameObject = this;
    m_components.push_back(std::move(component));
  }

  const std::string & GameObject::GetName() const
  {
    return m_name;
  }

  void GameObject::SetName(const std::string & name)
  {
    m_name = name;
  }

  unsigned int GameObject::GetChildrenCount() const
  {
    return m_children.size();
  }

  unsigned int GameObject::GetComponentCount() const
  {
    return m_components.size();
  }

  GameObject * GameObject::GetChild(unsigned int index) const
  {
    return m_children[index].get();
  }
}

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

#include <memory>
#include <vector>

namespace Newtonic
{
  class GameObject
  {
  public:
    void Update(float dt);
    void LateUpdate(float dt);
    void Render();
    void Awake();

    GameObject * GetParent() const;

    void AddChild(std::unique_ptr<GameObject> child);
    void AddComponent(std::unique_ptr<Component> component);

    const std::string & GetName() const;
    void SetName(const std::string & name);

    unsigned int GetChildrenCount() const;
    unsigned int GetComponentCount() const;

    GameObject * GetChild(unsigned int index) const;

  private:
    std::string m_name;
    std::vector<std::unique_ptr<GameObject>> m_children;
    std::vector<std::unique_ptr<Component>> m_components;
    GameObject * m_parent;

    void InitChildren();
    void InitComponents();

    NW_PRIVATE_SERIALIZATION;

    template<typename Archive>
    void save(Archive & ar) const
    {
      ar(CEREAL_NVP(m_name), CEREAL_NVP(m_children), CEREAL_NVP(m_components));
    }

    template<typename Archive>
    void load(Archive & ar)
    {
      ar(m_name, m_children, m_components);
      InitChildren();
      InitComponents();
    }
  };
}

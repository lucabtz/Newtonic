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

// main.cpp is used for fast tests, it has no use in the final library

#include <stdio.h>
#include "engine.h"
#include "mesh.h"
#include "actor.h"
#include "scene.h"
#include "mesh_renderer.h"
#include <memory>

int main(int argc, char **argv)
{
    puts("Newtonic testing");


    Newtonic::Engine engine;
    engine.Init();
    engine.OpenWindow("Newtonic");

    Newtonic::Assets & assetsManager = engine.GetAssetsManager();

    assetsManager.LoadShader("basic_mesh", "shaders/mesh.vert", "shaders/mesh.frag");
    assetsManager.LoadMesh("triangle", std::vector<GLfloat> {
      -1.0f, -1.0f, 0.0f,
      1.0f, -1.0f, 0.0f,
      0.0f,  1.0f, 0.0f,
    });

    auto initialScene = std::make_unique<Newtonic::Scene>();
    auto triangleActor = std::make_shared<Newtonic::Actor>();

    triangleActor->AddBehaviour(std::make_shared<Newtonic::MeshRenderer>(
      assetsManager.GetMesh("triangle"),
      assetsManager.GetShader("basic_mesh")
    ));
    initialScene->AddActor(triangleActor);

    engine.SetScene(std::move(initialScene));

    engine.Loop();
    return 0;
}

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

#include "engine.h"
#include "common.h"
#include "assets.h"
#include "scene.h"
#include "message_bus.h"
#include "input.h"

#include "mesh_shader.h"

#include <stdio.h>
#include <iostream>

namespace Newtonic
{
	Newtonic::Engine * g_engine;

	static  const std::vector<GLfloat> s_cubeVerts
	{
	  -1.0, -1.0,  1.0,
	  1.0, -1.0,  1.0,
	  -1.0,  1.0,  1.0,
	  1.0,  1.0,  1.0,
	  -1.0, -1.0, -1.0,
	  1.0, -1.0, -1.0,
	  -1.0,  1.0, -1.0,
	  1.0,  1.0, -1.0
	};
	static const std::vector<unsigned int> s_cubeIdx
	{
		// front face
	  0, 1, 2,
		2, 3, 2,

		//back face
		4, 5, 6,
		6, 7, 5,

		//right face
		1, 3, 7,
		1, 5, 7,

		//left face
		0, 2, 6,
		0, 4, 6,

		//top face
		3, 2, 6,
		3, 7, 6,

		//bottom face
		1, 0, 4,
		1, 5, 4
	};

	void GLFWErrorHandler(int err, const char * desc)
	{
		puts(desc);
	}

	void FramebufferSizeCallback(GLFWwindow * wnd, int w, int h)
	{
		Viewport newVp(w, h);
		auto msg =
			std::make_shared<EventScreenResizedMessage>(
				g_engine->m_viewport,
				newVp
			);
		g_engine->m_messageBus->PostMessage(msg, "Engine");
		g_engine->m_viewport = newVp;
	}

	void Engine::Init()
	{
		g_engine = this;
		glfwSetErrorCallback(GLFWErrorHandler);

		glewExperimental = true;
		if (!glfwInit())
		{
			throw NewtonicException("Could not initialize GLFW");
		}
	}

	void Engine::OpenWindow(const char *title, Viewport viewport)
	{
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_viewport = viewport;

		m_window = glfwCreateWindow(viewport.width, viewport.height, title, NULL, NULL);
		if(m_window == NULL)
		{
		    glfwTerminate();
		    throw NewtonicException("Could not create GLFW window");
		}
		glfwMakeContextCurrent(m_window);
		glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);

		glewExperimental = true;
		if (glewInit() != GLEW_OK)
		{
				throw NewtonicException("Could not initialize GLEW");
		}

		m_assets = new Assets;
		m_messageBus = new MessageBus;
		m_input = new Input(m_window);


		// Load some default meshes into the engine
		GetAssetsManager()->LoadMesh("cube", s_cubeVerts, s_cubeIdx);

		// Load some default shaders into the engine
		auto meshShader = std::make_shared<MeshShader>(
			"shaders/mesh.vert",
			"shaders/mesh.frag",
			"modl", "view", "proj"
		);
		GetAssetsManager()->LoadShaderT("mesh_shader", std::move(meshShader));
	}


	void Engine::Loop()
	{
		glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glEnable(GL_DEPTH_TEST);

		float then = glfwGetTime();
		float now = then;
		float dt = 0.0;

		bool focused = true;

		do
		{
			then = now;
			now = glfwGetTime();
			dt = now - then;

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_messageBus->Work();
			m_input->Work();

			glViewport(0, 0, m_viewport.width, m_viewport.height);
			m_scene->Render();

			m_scene->Update(dt);

			if (m_input->IsKeyDown(9)) /*ESC key*/ { m_input->SetHiddenCursorMode(false); focused = false; }
			if (m_input->IsButtonDown(0) /* Right mouse button */ && !focused) { m_input->SetHiddenCursorMode(true); focused = true; }

			glfwSwapBuffers(m_window);
			glfwPollEvents();
		} while(!glfwWindowShouldClose(m_window));
	}

	void Engine::SetScene(Scene *scene)
	{
		if (m_scene) delete m_scene;
		m_scene = scene;
		m_scene->Init();
	}

	Engine::~Engine()
	{
		if (m_scene) delete m_scene;
		delete m_assets;
		delete m_messageBus;
		delete m_input;
	}

}

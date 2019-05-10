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

#include <stdio.h>
#include <iostream>

namespace Newtonic
{
	Newtonic::Engine * g_engine;

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

		m_assets = std::make_unique<Assets>();
		m_messageBus = std::make_unique<MessageBus>();
		m_scene = std::make_unique<Scene>();
	}


	void Engine::Loop()
	{
		glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		do
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_messageBus->Work();
			m_scene->Render();

			glfwSwapBuffers(m_window);
			glfwPollEvents();
		} while(!glfwWindowShouldClose(m_window));
	}

	void Engine::SetScene(std::unique_ptr<Scene> scene)
	{
		m_scene = std::move(scene);
	}

}

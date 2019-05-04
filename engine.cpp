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
#include "mesh.h"

#include <stdio.h>

namespace Newtonic
{

	void GLFWErrorHandler(int err, const char * desc)
	{
		puts(desc);
	}

	void Engine::Init()
	{
		glfwSetErrorCallback(GLFWErrorHandler);

		glewExperimental = true;
		if (!glfwInit())
		{
			throw NewtonicException("Could not initialize GLFW");
		}
	}

	void Engine::OpenWindow(const char *title)
	{
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(1024, 768, title, NULL, NULL);
		if(m_window == NULL)
		{
		    glfwTerminate();
		    throw NewtonicException("Could not create GLFW window");
		}
		glfwMakeContextCurrent(m_window);

		glewExperimental = true;
		if (glewInit() != GLEW_OK)
		{
				throw NewtonicException("Could not initialize GLEW");
		}

		m_assets = std::make_unique<Assets>();
	}


	void Engine::Loop()
	{
		glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		do
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_scene->Render();

			glfwSwapBuffers(m_window);
			glfwPollEvents();
		} while(!glfwWindowShouldClose(m_window));
	}

	Assets & Engine::GetAssetsManager()
	{
		return *m_assets;
	}

	void Engine::SetScene(std::unique_ptr<Scene> scene)
	{
			m_scene = std::move(scene);
	}

}

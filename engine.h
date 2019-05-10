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

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <memory>

#include "message_bus.h"
#include "message.h"
#include "common.h"


#ifndef _ENGINE_H
#define _ENGINE_H

namespace Newtonic
{

	class Scene;
	class Assets;

	class Engine
	{
		GLFWwindow *m_window;
		Viewport m_viewport;

		std::unique_ptr<Scene> m_scene;
		std::unique_ptr<Assets> m_assets;
		std::unique_ptr<MessageBus> m_messageBus;

	public:

		friend void FramebufferSizeCallback(GLFWwindow * wnd, int w, int h);

		void Init();
		void OpenWindow(const char *title, Viewport viewport);

		Assets *GetAssetsManager()
		{
			return m_assets.get();
		}
		MessageBus *GetMessageBus()
		{
			return m_messageBus.get();
		}

		void SetScene(std::unique_ptr<Scene> scene);

		void Loop();

		Viewport GetViewport() { return m_viewport; }

	};

		extern Engine * g_engine;

}


#endif // _ENGINE_H

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

#include "src/opengl.h"
#include "src/math.h"
#include "src/logger.h"
#include "src/core.h"
#include "src/transform.h"
#include "src/util.h"
#include "src/viewport.h"
#include "src/window.h"
#include "src/shader.h"
#include "src/vertexbufferlayout.h"
#include "src/vertexbuffer.h"
#include "src/vertexarray.h"
#include "src/indexbuffer.h"
#include "src/renderer.h"
#include "src/camera.h"
#include "src/cameraperspective.h"
#include "src/input.h"
#include "src/keys.h"
#include "src/image.h"
#include "src/texture.h"
#include "src/timestep.h"
#include "src/eventbus.h"
#include "src/event.h"
#include "src/application.h"

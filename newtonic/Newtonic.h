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

#include "include/renderer/opengl.h"

#include "include/serialization.h"
#include "include/math.h"
#include "include/logger.h"
#include "include/core.h"
#include "include/transform.h"
#include "include/util.h"
#include "include/viewport.h"
#include "include/window.h"
#include "include/timestep.h"
#include "include/eventbus.h"
#include "include/event.h"
#include "include/application.h"
#include "include/input.h"
#include "include/keys.h"
#include "include/image.h"
#include "include/assetresourceinfo.h"
#include "include/assetinstance.h"
#include "include/assetmanager.h"
#include "include/uniform.h"
#include "include/materialinfo.h"

#include "include/renderer/texture.h"
#include "include/renderer/shader.h"
#include "include/renderer/vertexbufferlayout.h"
#include "include/renderer/vertexbuffer.h"
#include "include/renderer/vertexarray.h"
#include "include/renderer/indexbuffer.h"
#include "include/renderer/renderer.h"
#include "include/renderer/camera.h"
#include "include/renderer/cameraperspective.h"
#include "include/renderer/mesh.h"
#include "include/renderer/meshvertex.h"
#include "include/renderer/material.h"

#include "include/gocs/component.h"
#include "include/gocs/gameobject.h"
#include "include/gocs/behaviour.h"
#include "include/gocs/datacomponent.h"
#include "include/gocs/renderjob.h"

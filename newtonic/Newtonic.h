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

#include "src/renderer/opengl.h"

#include "src/math.h"
#include "src/logger.h"
#include "src/core.h"
#include "src/transform.h"
#include "src/util.h"
#include "src/viewport.h"
#include "src/window.h"
#include "src/timestep.h"
#include "src/eventbus.h"
#include "src/event.h"
#include "src/application.h"
#include "src/input.h"
#include "src/keys.h"
#include "src/image.h"
#include "src/serialization.h"
#include "src/assetresourceinfo.h"
#include "src/assetinstance.h"
#include "src/assetmanager.h"

#include "src/renderer/texture.h"
#include "src/renderer/shader.h"
#include "src/renderer/vertexbufferlayout.h"
#include "src/renderer/vertexbuffer.h"
#include "src/renderer/vertexarray.h"
#include "src/renderer/indexbuffer.h"
#include "src/renderer/renderer.h"
#include "src/renderer/camera.h"
#include "src/renderer/cameraperspective.h"
#include "src/renderer/mesh.h"
#include "src/renderer/meshvertex.h"

#include "src/gocs/component.h"
#include "src/gocs/gameobject.h"
#include "src/gocs/behaviour.h"
#include "src/gocs/datacomponent.h"
#include "src/gocs/renderjob.h"
#include "src/gocs/transformcomponent.h"

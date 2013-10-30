/*
 * worldpolygon.cpp
 * Copyright (C) 2013  Michał Garapich <michal@garapich.pl>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "db/point.h"
#include "db/worldmap.h"

#include "debugging/glerrors.h"

#include "glutils/vertexbufferobject.h"

#include "vatsinatorapplication.h"

#include "worldpolygon.h"
#include "defines.h"

struct WorldPolygon::WorldMapVBO {
  VertexBufferObject* border;
  int                 borderSize;
  VertexBufferObject* triangles;
  int                 trianglesSize;
};
  

WorldPolygon::WorldPolygon() :
    __world(nullptr) {}

WorldPolygon::~WorldPolygon() {
#ifndef CONFIG_NO_VBO
  delete __world->triangles;
  delete __world->border;
  delete __world;
#endif
}

void
WorldPolygon::init() {
#ifndef CONFIG_NO_VBO
  __createVbos();
#endif
}

void
WorldPolygon::paint() {
  glEnableClientState(GL_VERTEX_ARRAY);
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glColor3f(0.0, 0.0, 1.0);
  
#ifndef CONFIG_NO_VBO
  __world->border->bind();
  __world->triangles->bind();

  glVertexPointer(2, GL_FLOAT, 0, 0); checkGLErrors(HERE);
  glDrawElements(GL_TRIANGLES, __world->trianglesSize, GL_UNSIGNED_SHORT, 0); checkGLErrors(HERE);

  __world->triangles->unbind();
  __world->border->unbind();
#else
  glVertexPointer(2, GL_FLOAT, 0, &WorldMap::getSingleton().borders()[0]); checkGLErrors(HERE);
  glDrawElements(GL_TRIANGLES, WorldMap::getSingleton().borders().size(), GL_UNSIGNED_SHORT,
                 &WorldMap::getSingleton().triangles()[0]); checkGLErrors(HERE);
#endif
}

void
WorldPolygon::__createVbos() {
  VatsinatorApplication::log("WorldPolygon: preparing VBO...");
  
  __world = new WorldMapVBO();

  __world->border = new VertexBufferObject(GL_ARRAY_BUFFER);
  __world->border->sendData(sizeof(Point) * WorldMap::getSingleton().borders().size(),
                            &(WorldMap::getSingleton().borders()[0]));

  __world->borderSize = WorldMap::getSingleton().borders().size();

  __world->triangles = new VertexBufferObject(GL_ELEMENT_ARRAY_BUFFER);
  __world->triangles->sendData(sizeof(unsigned short) * WorldMap::getSingleton().triangles().size(),
                               &(WorldMap::getSingleton().triangles()[0]));

  __world->trianglesSize = WorldMap::getSingleton().triangles().size();

  VatsinatorApplication::log("WorldPolygon: VBO ready.");
}

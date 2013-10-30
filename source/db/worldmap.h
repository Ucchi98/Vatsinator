/*
    worldmap.h
    Copyright (C) 2012-2013  Michał Garapich michal@garapich.pl

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef WORLDMAP_H
#define WORLDMAP_H

#include <QObject>
#include <QVector>

#include "db/point.h"

#include "singleton.h"

class VertexBufferObject;

class WorldMap :
    public QObject,
    public Singleton<WorldMap> {

  Q_OBJECT
  
  
public:
  WorldMap();
  
  const QVector<Point> &
  borders() const { return __borders; }
  
  const QVector<unsigned short> &
  triangles() const { return __triangles; }

private:
  void __readDatabase();

  QVector<Point>          __borders;
  QVector<unsigned short> __triangles;


};

#endif // WORLDMAP_H

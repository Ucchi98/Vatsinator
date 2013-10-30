/*
 * mapview.h
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

#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QGraphicsView>
#include <QPointF>
#include <QPoint>

#include "ui/graphics/worldpolygon.h"

class MapView : public QGraphicsView {
  
  Q_OBJECT

public:
  MapView(QWidget* = 0);
  
  QPointF mapToLonLat(const QPoint&);
  
protected:
  void drawBackground(QPainter*, const QRectF&) override;
  
//   void mousePressEvent(QMouseEvent*) override;
//   void mouseReleaseEvent(QMouseEvent*) override;
  void mouseMoveEvent(QMouseEvent*) override;
  void wheelEvent(QWheelEvent*) override;
  
private:
  void __updateLabel();
//   void __updateSceneRect();
  
  QPointF __position; /**< lon, lat */
  QPoint __mousePosition; /** x, y */
  QPoint __lastClickPosition; /** x, y */
  qreal __zoom;
  
  WorldPolygon __world;

};

#endif // MAPVIEW_H

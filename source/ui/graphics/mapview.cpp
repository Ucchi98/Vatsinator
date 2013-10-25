/*
 * mapview.cpp
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

#include <QtGui>

#include "ui/graphics/mapconfig.h"
#include "ui/windows/vatsinatorwindow.h"

#include "mapview.h"
#include "defines.h"

static constexpr qreal xFactor = MapConfig::baseWindowWidth() / 2 / MapConfig::longitudeMax();
static constexpr qreal yFactor = MapConfig::baseWindowHeight() / 2 / MapConfig::latitudeMax();

MapView::MapView(QWidget* _parent) :
    QGraphicsView(_parent),
    __position(0.0, 0.0),
    __zoom(1) {}

QPointF
MapView::mapToLonLat(const QPoint& _point) {
  return QPointF(_point.x() * xFactor * __zoom, _point.y() * yFactor * __zoom);
}

// void
// MapView::mousePressEvent(QMouseEvent* _event) {
//   __mousePosition = _event->pos();
//   
//   if (_event->buttons() & Qt::LeftButton)
//     __lastClickPosition = _event->pos();
// }
// 
// void
// MapView::mouseReleaseEvent(QMouseEvent* _event) {
//   __mousePosition = _event->pos();
//   
//   setCursor(QCursor(Qt::ArrowCursor));
// }
// 
void
MapView::mouseMoveEvent(QMouseEvent* _event) {
  QGraphicsView::mouseMoveEvent(_event);
  
  __mousePosition = _event->pos();
  __updateLabel();
}

void
MapView::wheelEvent(QWheelEvent* _event) {
  int steps = _event->delta() / 120;
  qreal z;
  
  if (steps >= 0)
    z = 2.0 * static_cast<qreal>(steps);
  else
    z = 1.0 / (2.0 * static_cast<qreal>(qAbs(steps)));
  
  scale(z, z);
    __zoom *= z;
  
  _event->accept();
}

void
MapView::__updateLabel() {
  QPointF lonLat = mapToScene(__mousePosition);
  VatsinatorWindow::getSingleton().positionBox()->setText(
    QString("%1 %2 %3 %4").arg(
      QString(lonLat.y() >= 0 ? "N" : "S"),
      QString::number(qAbs(lonLat.y()), 'g', 6),
      QString(lonLat.x() > 0 ? "E" : "W"),
      QString::number(qAbs(lonLat.x()), 'g', 6) + " "
    )
  );
}
/*
void
MapView::__updateSceneRect() {
  QPointF topLeft = mapToScene(0, 0);
  QPointF bottomRight = mapToScene(width() - 1, height() - 1);
  
  setSceneRect(QRectF(topLeft, bottomRight));
}*/


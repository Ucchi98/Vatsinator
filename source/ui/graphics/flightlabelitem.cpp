/*
 * flightlabelitem.cpp
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

#include "ui/graphics/flightitem.h"
#include "ui/graphics/mapconfig.h"

#include "vatsimdata/client/pilot.h"

#include "flightlabelitem.h"
#include "defines.h"

FlightLabelItem::FlightLabelItem(QGraphicsItem* _parent) :
    QGraphicsItem(_parent),
    __label(MapConfig::pilotLabelBackground()) {
  setFlags(ItemIgnoresTransformations);
  
  setZValue(2);
  
  FlightItem* flightItem = dynamic_cast<FlightItem*>(parentItem());
  Q_ASSERT(flightItem);
  
  /* Draw label text on the label background */
  QPainter painter(&__label);
  painter.setRenderHint(QPainter::TextAntialiasing);
  painter.setRenderHint(QPainter::SmoothPixmapTransform);
  painter.setRenderHint(QPainter::HighQualityAntialiasing);
  painter.setFont(MapConfig::pilotFont());
  painter.setPen(MapConfig::pilotPen());
  QRect rectangle(28, 10, 73, 13); // size of the tooltip.png
  painter.drawText(rectangle, Qt::AlignCenter, flightItem->callsign());
  
  qreal xPos = 0 - (__label.width() / 2);
  qreal yPos = 0 - __label.height() - 12;
  
  __topLeft = QPoint(xPos, yPos);
  __topLeftF = QPointF(xPos, yPos);
}

void
FlightLabelItem::paint(QPainter* _painter, const QStyleOptionGraphicsItem*, QWidget*) {
  _painter->drawPixmap(__topLeft, __label);
}

QRectF
FlightLabelItem::boundingRect() const {
  return QRectF(__topLeftF, __label.size());
}

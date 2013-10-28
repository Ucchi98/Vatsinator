/*
 * airportlabelitem.cpp
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

#include "ui/graphics/airportitem.h"
#include "ui/graphics/mapconfig.h"

#include "airportlabelitem.h"
#include "defines.h"

AirportLabelItem::AirportLabelItem(QGraphicsItem* _parent) :
    QGraphicsItem(_parent),
    __label(MapConfig::airportLabelBackground()) {
  
  AirportItem* apItem = dynamic_cast<AirportItem*>(parentItem());
  Q_ASSERT(apItem);
  
  QPainter painter(&__label);
  painter.setRenderHint(QPainter::TextAntialiasing);
  painter.setRenderHint(QPainter::SmoothPixmapTransform);
  painter.setRenderHint(QPainter::HighQualityAntialiasing);
  painter.setFont(MapConfig::airportFont());
  painter.setPen(MapConfig::airportPen());
  QRect rectangle(8, 2, 48, 12); // size of the tooltip.png
  painter.drawText(rectangle, Qt::AlignCenter, apItem->icao());
  
  qreal xPos = 0 - (__label.width() / 2);
  qreal yPos = 0 - __label.height() + 22;
  
  __topLeft = QPoint(xPos, yPos);
  __topLeftF = QPointF(xPos, yPos);
}

void
AirportLabelItem::paint(QPainter* _painter, const QStyleOptionGraphicsItem*, QWidget*) {
  _painter->drawPixmap(__topLeft, __label);
}

QRectF
AirportLabelItem::boundingRect() const {
  return QRectF(__topLeftF, __label.size());
}

/*
 * airportitem.h
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

#ifndef AIRPORTITEM_H
#define AIRPORTITEM_H

#include <QGraphicsItem>
#include <QPointF>
#include <QPoint>

class Airport;

class AirportItem : public QGraphicsItem {
  
public:
  AirportItem(const Airport*);
  
  void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;
  QRectF boundingRect() const override;
  
private:
  QString __tooltipText() const;
  
  const Airport* __airport;
  QPixmap __icon;
  
  QPoint __topLeft;
  QPointF __topLeftF;

};

#endif // AIRPORTITEM_H

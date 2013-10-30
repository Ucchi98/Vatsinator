/*
 * flightitem.h
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

#ifndef FLIGHTITEM_H
#define FLIGHTITEM_H

#include <QCoreApplication>
#include <QGraphicsItem>
#include <QRectF>
#include <QPixmap>

class FlightLabelItem;
class Pilot;

class FlightItem : public QGraphicsItem {
  
  Q_DECLARE_TR_FUNCTIONS(FlightItem);

public:
  FlightItem(const Pilot*);
  virtual ~FlightItem();
  
  void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;
  QRectF boundingRect() const override;
  
  const QString& callsign() const;
  
  inline const Pilot *
  pilot() const { return __pilot; }
  
protected:
  void hoverEnterEvent(QGraphicsSceneHoverEvent*) override;
  void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;

private:
  QString __tooltipText() const;
  
  const Pilot* __pilot;
  QPixmap __model;
  
  QPoint __topLeft;
  QPointF __topLeftF;
  
  FlightLabelItem* __label;

};

#endif // FLIGHTITEM_H

/*
 * airportitem.cpp
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

#include "db/airportdatabase.h"

#include "ui/graphics/mapconfig.h"

#include "vatsimdata/airport.h"
#include "vatsimdata/airport/activeairport.h"
#include "vatsimdata/models/controllertablemodel.h"

#include "airportitem.h"
#include "defines.h"

AirportItem::AirportItem(const Airport* _airport) :
    QGraphicsItem(nullptr),
    __airport(_airport) {
  setFlags(ItemIgnoresTransformations);
  setCursor(QCursor(Qt::PointingHandCursor));
  setToolTip(__tooltipText());
  
  setPos(__airport->data()->longitude, 0 - __airport->data()->latitude);
  
  const ActiveAirport* ap = dynamic_cast<const ActiveAirport*>(__airport);
  if (ap)
  __icon = ap->staffModel()->staff().isEmpty() ? MapConfig::airportIcon() : MapConfig::staffedAirportIcon();
  
  qreal xPos = 0 - __icon.width() / 2;
  qreal yPos = 0 - __icon.height() / 2;
  
  __topLeft = QPoint(xPos, yPos);
  __topLeftF = QPointF(xPos, yPos);
}

void
AirportItem::paint(QPainter* _painter, const QStyleOptionGraphicsItem*, QWidget*) {
  _painter->drawPixmap(__topLeft, __icon);
}

QRectF
AirportItem::boundingRect() const {
  return QRectF(__topLeftF, __icon.size());
}

QString
AirportItem::__tooltipText() const {
  QString text = static_cast<QString>("<center>") %
      static_cast<QString>(__airport->data()->icao) %
      static_cast<QString>("<br><nobr>") %
      QString::fromUtf8(__airport->data()->name) %
      static_cast<QString>(", ") %
      QString::fromUtf8(__airport->data()->city) %
      static_cast<QString>("</nobr>");
  
  const ActiveAirport* aa = dynamic_cast<const ActiveAirport*>(__airport);
  if (aa) {
    for (const Controller* c: aa->staffModel()->staff())
      text.append(static_cast<QString>("<br><nobr>") %
          c->callsign() % " " % c->frequency() % " " % c->realName() %
          "</nobr>"
    );
  }
  
  return text;
}

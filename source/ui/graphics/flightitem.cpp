/*
 * flightitem.cpp
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

#include "modules/modelmatcher.h"

#include "ui/graphics/flightlabelitem.h"
#include "ui/graphics/mapconfig.h"

#include "vatsimdata/airport/activeairport.h"
#include "vatsimdata/client/pilot.h"
#include "vatsimdata/vatsimdatahandler.h"

#include "flightitem.h"
#include "defines.h"

FlightItem::FlightItem(const Pilot* _pilot) :
    QGraphicsItem(nullptr),
    __pilot(_pilot) {
  setFlags(ItemIgnoresTransformations);
  
  setZValue(1);
  setAcceptHoverEvents(true);
  
  setPos(__pilot->position().longitude, 0 - __pilot->position().latitude);
  
  QTransform transform;
  transform.rotate(__pilot->heading());
  
  __model = ModelMatcher::getSingleton().matchMyModel(__pilot->aircraft())
      .transformed(transform, Qt::SmoothTransformation);
  
  qreal xPos = 0 - __model.width() / 2;
  qreal yPos = 0 - __model.height() / 2;
  
  __topLeft = QPoint(xPos, yPos);
  __topLeftF = QPointF(xPos, yPos);
  
  setToolTip(__tooltipText());
  setCursor(QCursor(Qt::PointingHandCursor));
  
  __label = new FlightLabelItem(this);
}

void
FlightItem::paint(QPainter* _painter, const QStyleOptionGraphicsItem*, QWidget*) {
  _painter->drawPixmap(__topLeft, __model);
}

QRectF
FlightItem::boundingRect() const {
  return QRectF(__topLeftF, __model.size());
}

const QString &
FlightItem::callsign() const {
  return __pilot->callsign();
}

void
FlightItem::hoverEnterEvent(QGraphicsSceneHoverEvent*) {
  setZValue(zValue() + 2);
  update();
}

void
FlightItem::hoverLeaveEvent(QGraphicsSceneHoverEvent*) {
  setZValue(zValue() - 2);
  update();
}

QString
FlightItem::__tooltipText() const {
  static const QMap<QString, ActiveAirport*>& airports = VatsimDataHandler::getSingleton().activeAirports();
  
  return static_cast<QString>("<center>") %
    __pilot->callsign() % "<br><nobr>" %
    __pilot->realName() % " (" % __pilot->aircraft() % ")</nobr><br><nobr>" %
    (__pilot->route().origin.isEmpty() ?
      tr("(unknown)") :
      (airports[__pilot->route().origin]->data() ?
        __pilot->route().origin % " " % QString::fromUtf8(airports[__pilot->route().origin]->data()->city) :
        __pilot->route().origin)
    ) %
    " > " %
    (__pilot->route().destination.isEmpty() ?
      tr("(unknown)") :
      (airports[__pilot->route().destination]->data() ?
        __pilot->route().destination % " " % QString::fromUtf8(airports[__pilot->route().destination]->data()->city) :
        __pilot->route().destination)
    ) %
    "</nobr><br>" %
    tr("Ground speed: %1 kts").arg(QString::number(__pilot->groundSpeed())) %
    "<br>" %
    tr("Altitude: %1 ft").arg(QString::number(__pilot->altitude())) %
    "</center>";
}

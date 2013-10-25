/*
    flightdetailswindow.cpp
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

#include <QtGui>

#include "db/airportdatabase.h"

#include "modules/flighttracker.h"

#include "ui/userinterface.h"

#include "ui/windows/airportdetailswindow.h"

#include "vatsimdata/vatsimdatahandler.h"

#include "vatsimdata/airport/activeairport.h"

#include "vatsimdata/client/pilot.h"

#include "vatsinatorapplication.h"

#include "flightdetailswindow.h"
#include "defines.h"

FlightDetailsWindow::FlightDetailsWindow(QWidget* _parent) :
    BaseWindow(_parent) {
  setupUi(this);
  
  connect(qApp, SIGNAL(aboutToQuit()),
          this, SLOT(hide()));

  connect(TrackFlightBox,                       SIGNAL(stateChanged(int)),
          this,                                 SLOT(stateHandle(int)));
  connect(ShowButton,                           SIGNAL(clicked()),
          this,                                 SLOT(__handleShowClicked()));
  connect(VatsimDataHandler::getSingletonPtr(), SIGNAL(vatsimDataUpdated()),
          this,                                 SLOT(__updateData()));
}

void
FlightDetailsWindow::show(const Client* _client) {
  Q_ASSERT(dynamic_cast<const Pilot*>(_client));
  __current = dynamic_cast<const Pilot*>(_client);
  __currentCallsign = __current->callsign();

  if (__current->isPrefiledOnly())
    return;

  setWindowTitle(tr("%1 - flight details").arg(__current->callsign()));

  CallsignLabel->setText(__current->callsign());
  RouteLabel->setText(__current->route().origin % " -> " % __current->route().destination);

  PilotLabel->setText(__current->realName() + " (" + QString::number(__current->pid()) + ")");
  AltitudeLabel->setText(tr("%1 feet").arg(QString::number(__current->altitude())));
  GroundSpeedLabel->setText(tr("%1 kts").arg(QString::number(__current->groundSpeed())));
  HeadingLabel->setText(QString::number(__current->heading()));

  if (__current->flightStatus() == Pilot::AIRBORNE)
    CurrentStatusLabel->setText(tr("airborne"));
  else if (__current->flightStatus() == Pilot::DEPARTING)
    CurrentStatusLabel->setText(tr("departing"));
  else
    CurrentStatusLabel->setText(tr("arrived"));

  ServerLabel->setText(__current->server());
  TimeOnlineLabel->setText(__current->onlineFrom().toString("dd MMM yyyy, hh:mm"));
  SquawkLabel->setText(__current->squawk());
  AltimeterLabel->setText(__current->pressure().mb % " / " % __current->pressure().ihg);
  
  VatawareLink->setText("<a href=\"http://www.vataware.com/pilot.cfm?cid=" %
      QString::number(__current->pid()) %
      static_cast<QString>("\">") %
      tr("Vataware statistics for this pilot") %
      static_cast<QString>("</a>"));

  FlightRulesLabel->setText((__current->flightRules() == Pilot::IFR) ? "IFR" : "VFR");

  __updateToFromButtons();

  AircraftLabel->setText(__current->aircraft());
  TrueAirSpeedLabel->setText(tr("%1 kts").arg(QString::number(__current->tas())));
  CruiseAltitude->setText(__current->route().altitude);

  RouteField->setPlainText(__current->route().route);
  RemarksField->setPlainText(__current->remarks());

  if (FlightTracker::getSingleton().tracked() == __current)
    TrackFlightBox->setCheckState(Qt::Checked);
  else
    TrackFlightBox->setCheckState(Qt::Unchecked);

  if (!isVisible())
    QWidget::show();
  else
    activateWindow();
}

void
FlightDetailsWindow::stateHandle(int _state) {
  emit flightTrackingStateChanged(__current, _state);
}

void
FlightDetailsWindow::__updateToFromButtons() {
  if (!__current->route().origin.isEmpty()) {
    Airport* ap = VatsimDataHandler::getSingleton().activeAirports()[__current->route().origin];
    QString text = __current->route().origin;

    if (ap->data()) {
      text.append(static_cast<QString>(" ") %
                  QString::fromUtf8(ap->data()->name));

      if (!QString::fromUtf8(ap->data()->name).contains(QString::fromUtf8(ap->data()->city)))
        text.append(
          static_cast<QString>(" - ") %
          QString::fromUtf8(ap->data()->city));

      OriginButton->setAirportPointer(ap);
    } else {
      OriginButton->setAirportPointer(NULL);
    }

    OriginButton->setText(text);
  } else {
    OriginButton->setText("(unknown)");
    OriginButton->setAirportPointer(NULL);
  }

  if (!__current->route().destination.isEmpty()) {
    Airport* ap = VatsimDataHandler::getSingleton().activeAirports()[__current->route().destination];
    QString text = __current->route().destination;

    if (ap->data()) {
      text.append(static_cast<QString>(" ") %
                  QString::fromUtf8(ap->data()->name));

      if (!QString::fromUtf8(ap->data()->name).contains(QString::fromUtf8(ap->data()->city)))
        text.append(
          static_cast<QString>(" - ") %
          QString::fromUtf8(ap->data()->city));

      ArrivalButton->setAirportPointer(ap);
    } else {
      ArrivalButton->setAirportPointer(NULL);
    }

    ArrivalButton->setText(text);
  } else {
    ArrivalButton->setText("(unknown)");
    ArrivalButton->setAirportPointer(NULL);
  }
}

void
FlightDetailsWindow::__updateData() {
  __current = VatsimDataHandler::getSingleton().findPilot(__currentCallsign);

  if (!__current || __current->isPrefiledOnly()) {
    __currentCallsign = "";
    hide();
  } else {
    __updateToFromButtons();
  }
}

void
FlightDetailsWindow::__handleShowClicked() {
  Q_ASSERT(__current);
//   MapWidget::getSingleton().showClient(__current);
}



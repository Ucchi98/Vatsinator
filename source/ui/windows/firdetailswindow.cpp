/*
    firdetailswindow.cpp
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
#include "db/firdatabase.h"

#include "modules/vatbookhandler.h"
#include "modules/models/bookedatctablemodel.h"

#include "ui/userinterface.h"

#include "ui/buttons/clientdetailsbutton.h"
#include "ui/buttons/airportdetailsbutton.h"

#include "ui/windows/airportdetailswindow.h"
#include "ui/windows/atcdetailswindow.h"
#include "ui/windows/flightdetailswindow.h"

#include "vatsimdata/airport.h"
#include "vatsimdata/vatsimdatahandler.h"

#include "vatsimdata/client/controller.h"
#include "vatsimdata/fir.h"
#include "vatsimdata/client/pilot.h"

#include "vatsimdata/models/airporttablemodel.h"
#include "vatsimdata/models/controllertablemodel.h"
#include "vatsimdata/models/flighttablemodel.h"

#include "firdetailswindow.h"
#include "defines.h"

FirDetailsWindow::FirDetailsWindow(QWidget* _parent) :
    QWidget(_parent) {
  setupUi(this);
  UserInterface::setWindowPosition(this);
}

void
FirDetailsWindow::show(const Fir* _f) {
  __currentICAO = _f->getIcao();

  __fillLabels(_f);
  __updateModels(_f);
  __adjustTables();

  QWidget::show();
}

void
FirDetailsWindow::__updateModels(const Fir* _f) {
  Q_ASSERT(_f);
  
  FlightsTable->setModel(_f->getFlightsModel());
  ATCTable->setModel(_f->getStaffModel());
  AirportsTable->setModel(_f->getAirportsModel());
  
  BookedATCTable->setModel(VatbookHandler::getSingleton().getNotNullModel(_f->getIcao()));
}

void
FirDetailsWindow::__fillLabels(const Fir* _f) {
  if (_f->getCountry() != "USA")
    setWindowTitle(tr("%1 - FIR details").arg(_f->getIcao()));
  else
    setWindowTitle(tr("%1 - ARTCC details").arg(_f->getIcao()));

  if (!_f->isOceanic())
    ICAOLabel->setText(_f->getIcao());
  else
    ICAOLabel->setText(_f->getIcao() + " Oceanic");

  NameLabel->setText(_f->getName());
}

void
FirDetailsWindow::__adjustTables() {
  FlightsTable->hideColumn(FlightTableModel::Name);
  
  FlightsTable->setColumnWidth(FlightTableModel::Callsign, 150);
  FlightsTable->setColumnWidth(FlightTableModel::From, 170);
  FlightsTable->setColumnWidth(FlightTableModel::To, 170);
  FlightsTable->setColumnWidth(FlightTableModel::Aircraft, 150);

  ATCTable->setColumnWidth(ControllerTableModel::Callsign, 150);
  ATCTable->setColumnWidth(ControllerTableModel::Name, 340);
  ATCTable->setColumnWidth(ControllerTableModel::Frequency, 150);

  AirportsTable->setColumnWidth(AirportTableModel::Label, 270);
  AirportsTable->setColumnWidth(AirportTableModel::Facilities, 170);
  AirportsTable->setColumnWidth(AirportTableModel::Outbounds, 100);
  AirportsTable->setColumnWidth(AirportTableModel::Inbounds, 100);
  
  BookedATCTable->setColumnWidth(BookedAtcTableModel::Callsign, 150);
  BookedATCTable->setColumnWidth(BookedAtcTableModel::Name, 300);
  BookedATCTable->setColumnWidth(BookedAtcTableModel::Date, 150);
  BookedATCTable->setColumnWidth(BookedAtcTableModel::Hours, 150);
}

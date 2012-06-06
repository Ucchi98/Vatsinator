/*
    flightslistwindow.cpp
    Copyright (C) 2012  Michał Garapich garrappachc@gmail.com

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

#include "ui/windows/flightdetailswindow.h"

#include "vatsimdata/vatsimdatahandler.h"
#include "vatsimdata/models/flighttablemodel.h"

#include "flightslistwindow.h"
#include "defines.h"

FlightsListWindow::FlightsListWindow(QWidget* _parent) :
		QWidget(_parent) {
	setupUi(this);
	__setWindowPosition();
	FlightsTable->setModel(VatsimDataHandler::GetSingleton().getFlightsModel());
	FlightsTable->hideColumn(FlightTableModel::Button);
	__setColumnsWidths();
	
	connect(FlightsTable,	SIGNAL(doubleClicked(const QModelIndex&)),
		this,		SLOT(__handleDoubleClicked(const QModelIndex&)));
}

void
FlightsListWindow::resizeEvent(QResizeEvent* _event) {
	QWidget::resizeEvent(_event);
	__setColumnsWidths();
}

void
FlightsListWindow::__setColumnsWidths() {
	const int CALLSIGN_SIZE = 100;
	const int ACFT_SIZE = 120;
	const int SCROLLBAR_SIZE = 30;
	
	int spaceLeft = FlightsTable->width() - CALLSIGN_SIZE - ACFT_SIZE - SCROLLBAR_SIZE;
	spaceLeft /= 3;
	
	FlightsTable->setColumnWidth(FlightTableModel::Callsign, CALLSIGN_SIZE);
	FlightsTable->setColumnWidth(FlightTableModel::Name, spaceLeft);
	FlightsTable->setColumnWidth(FlightTableModel::From, spaceLeft);
	FlightsTable->setColumnWidth(FlightTableModel::To, spaceLeft);
	FlightsTable->setColumnWidth(FlightTableModel::Aircraft, ACFT_SIZE);
}

void
FlightsListWindow::__setWindowPosition() {
	QDesktopWidget* desktop = QApplication::desktop();
	
	int screenWidth, width;
	int screenHeight, height;
	
	int x, y;
	
	QSize windowSize;
	
	screenWidth = desktop -> width();
	screenHeight = desktop -> height();
	
	windowSize = size();
	width = windowSize.width();
	height = windowSize.height();
	
	x = (screenWidth - width) / 2;
	y = (screenHeight - height) / 2;
	y -= 50;
	
	move(x, y);
}

void
FlightsListWindow::__handleDoubleClicked(const QModelIndex& _index) {
	Q_ASSERT(dynamic_cast< const FlightTableModel* >(_index.model()));
	
	FlightDetailsWindow::GetSingleton().show(
		(dynamic_cast< const FlightTableModel* >(_index.model()))->getFlights()[_index.row()]
	);
}
/*
    controllertablemodel.cpp
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

#include "vatsimdata/controller.h"

#include "controllertablemodel.h"
#include "defines.h"

ControllerTableModel::ControllerTableModel(QObject* _parent) :
		QAbstractTableModel(_parent) {}

void
ControllerTableModel::addStaff(const Controller* _c) {
	__staff.push_back(_c);
}

int
ControllerTableModel::rowCount(const QModelIndex& ) const {
	return __staff.size();
}

int
ControllerTableModel::columnCount(const QModelIndex& ) const {
	/* 0 - callsign
	 * 1 - name
	 * 2 - freq
	 * 3 - button
	 */
	return 4;
}

QVariant
ControllerTableModel::data(const QModelIndex& _index, int _role) const {
	if (!_index.isValid() || _index.row() >= rowCount() || _index.column() >= columnCount())
		return QVariant();
	
	switch (_role) {
		case Qt::TextAlignmentRole:
			return Qt::AlignCenter;
		case Qt::DisplayRole:
			switch (_index.column()) {
				case Callsign:
					return __staff[_index.row()]->callsign;
				case Name:
					return __staff[_index.row()]->realName;
				case Frequency:
					return __staff[_index.row()]->frequency;
				default:
					return QVariant();
			}
		default:
			return QVariant();
	}
}

QVariant
ControllerTableModel::headerData(int _section, Qt::Orientation _orientation, int _role) const {
	if (_section >= columnCount() || _orientation == Qt::Vertical || _role != Qt::DisplayRole)
		return QVariant();
	
	switch (_section) {
		case 0:
			return "Callsign";
		case 1:
			return "Name";
		case 2:
			return "Frequency";
		default:
			return "";
	}
}

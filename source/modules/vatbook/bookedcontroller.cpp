/*
    bookedcontroller.cpp
    Copyright (C) 2012  Michał Garapich michal@garapich.pl

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

#include "bookedcontroller.h"
#include "defines.h"

/*
 * 0 Callsign
 * 1 Pid
 * 2 Real name
 * 3 Type
 * 4 Session type
 * 5 
 * ...
 * 13
 * 14 Booked to
 * 15
 * 16 Date booked
 * 17 
 * ...
 * 36
 * 37 Booked from
 */

BookedController::BookedController(const QStringList& _data) :
    __callsign(_data[0]),
    __realName(_data[2]),
    __trainingSession(_data[4][0] == '1'),
    __dateBooked(QDate::fromString(_data[16], "yyyyMMdd")),
    __bookedFrom(QTime::fromString(_data[37], "hhmm")),
    __bookedTo(QTime::fromString(_data[14], "hhmm")) {}

QString
BookedController::getIcao() const {
  return __callsign.split('_').first();
}
    

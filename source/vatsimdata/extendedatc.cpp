/*
 * extendedatc.cpp
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

#include <QtCore>

#include "vatsinatorapplication.h"

#include "extendedatc.h"
#include "defines.h"

ExtendedAtc::ExtendedAtc(const QVariant& _jsonFormat) {
  __fromVariant(_jsonFormat);
}

void
ExtendedAtc::__fromVariant(const QVariant& _jsonFormat) {
  QVariantMap data = _jsonFormat.toMap();
  if (!data.contains("pattern")) {
    VatsinatorApplication::log("ExtendedAtc: could not find pattern for object!");
    return;
  }
  
  __pattern = data["pattern"].toString();
  __regExp.setPattern(__pattern);
  __regExp.setPatternSyntax(QRegExp::Wildcard);
  
  if (data.contains("limits")) {
    for (auto coord: data["limits"].toList())
      __limits << coord.toFloat();
  }
}

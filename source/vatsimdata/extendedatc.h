/*
 * extendedatc.h
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

#ifndef EXTENDEDATC_H
#define EXTENDEDATC_H

#include <QRegExp>
#include <QVector>
#include <QString>

class QVariant;

class ExtendedAtc {

public:
  ExtendedAtc() = default;
  ExtendedAtc(const QVariant&);
  
  inline bool
  hasLimits() const {
    return __limits.size() > 0;
  }
  
  inline const QVector<float> &
  limits() const {
    return __limits;
  }
  
  inline const QString &
  pattern() const {
    return __pattern;
  }
  
  inline const QRegExp &
  regExp() const {
    return __regExp;
  }
  
private:
  void __fromVariant(const QVariant&);
  
  QString __pattern;
  QRegExp __regExp;
  QVector<float> __limits;
  
};

#endif // EXTENDEDATC_H

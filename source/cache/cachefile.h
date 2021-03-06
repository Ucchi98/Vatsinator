/*
    cachefile.h
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


#ifndef CACHEFILE_H
#define CACHEFILE_H

#include <QFile>

class CacheFile : public QFile {
  
  /*
   * This class is used to store vatsinator data in cache file.
   * It is used, for example, in order to store downloaded data
   * between sessions.
   */
  
  Q_OBJECT
  
public:
  CacheFile(const QString&);
  
  /**
   * NOTE: QFile::exists() is not virtual.
   */
  bool exists() const;
  
  bool open(OpenMode  = QIODevice::ReadOnly | QIODevice::Text);
  
};

#endif // CACHEFILE_H

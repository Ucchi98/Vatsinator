/*
    modelmatcher.h
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


#ifndef MODELMATCHER_H
#define MODELMATCHER_H

#include <QCoreApplication>
#include <QString>
#include <QPixmap>
#include <QMap>

#include "singleton.h"

class ModelMatcher : public Singleton<ModelMatcher> {

  /**
   * This class matches the models to the planes.
   */
  
  Q_DECLARE_TR_FUNCTIONS(ModelMatcher);

public:
  
  ModelMatcher();

  /**
   * @param acft Aircraft code that comes from the flight plan.
   * @return Model texture.
   */
  QPixmap matchMyModel(const QString&) const;

private:
  /**
   * Reads the models.dat file.
   */
  void __readDatFile();
  
  /**
   * Loads pixmaps for aircraft types.
   */
  void __loadPixmaps();

  QMap<QString, QString> __acftTypes;
  QMap<QString, QPixmap>  __typePixmaps;


};

#endif // MODELMATCHER_H

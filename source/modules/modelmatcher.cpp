/*
    modelmatcher.cpp
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

#include "vatsimdata/vatsimdatahandler.h"

#include "storage/filemanager.h"
#include "vatsinatorapplication.h"

#include "modelmatcher.h"
#include "defines.h"

ModelMatcher::ModelMatcher() {
  __acftTypes["ZZZZ"] = "1p"; // default
  
  __readDatFile();
  __loadPixmaps();
}

QPixmap
ModelMatcher::matchMyModel(const QString& _acft) const {
  QRegExp exp("([a-zA-Z0-9]{4})");
  if (exp.indexIn(_acft))
    return __typePixmaps[__acftTypes.value(exp.cap(1), "1p")];
  else
    return __typePixmaps[__acftTypes.value("ZZZZ")];
}

void
ModelMatcher::__readDatFile() {
  QFile modelsFile(FileManager::path("data/model"));

  if (!modelsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    VatsinatorApplication::alert(
      tr("File %1 could not be opened! Check file permissions or reinstall the application.")
        .arg(modelsFile.fileName()));
    return;
  }

  while (!modelsFile.atEnd()) {
    QString line(modelsFile.readLine());
    line = line.simplified();
    
    if (line.startsWith('#') || line.isEmpty())
      continue;
    
    auto splitted = line.split(' ');
    __acftTypes.insert(splitted[0], splitted[1]);
  }
}

void
ModelMatcher::__loadPixmaps() {
  QString path(FileManager::staticPath(FileManager::Pixmaps));
  
  __typePixmaps.insert("1p", QPixmap(path % "/1p32.png"));
  __typePixmaps.insert("2p", QPixmap(path % "/2p32.png"));
  __typePixmaps.insert("4p", QPixmap(path % "/4p32.png"));
  __typePixmaps.insert("2j", QPixmap(path % "/2j32.png"));
  __typePixmaps.insert("3j", QPixmap(path % "/3j32.png"));
  __typePixmaps.insert("4j", QPixmap(path % "/4j32.png"));
  __typePixmaps.insert("conc", QPixmap(path % "/conc32.png"));
}

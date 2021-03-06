/*
    vatbookhandler.h
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


#ifndef VATBOOKHANDLER_H
#define VATBOOKHANDLER_H

#include <QHash>
#include <QTimer>
#include <QObject>
#include <QString>

#include "singleton.h"

struct B;
class BookedAtcTableModel;
class HttpHandler;

class VatbookHandler :
    public QObject,
    public Singleton< VatbookHandler > {
  
  /*
   * This class provides VATBOOK integration.
   */
  
  Q_OBJECT
  
public:
  
  explicit VatbookHandler(QObject* = 0);
  virtual ~VatbookHandler();
  
  inline BookedAtcTableModel *
  getModel(const QString& _icao) {
    return __bookings.value(_icao, NULL); 
  }
  
  /**
   * If model does not exist, returns VatbookHandler::emptyBookedAtcTable,
   * which is better for views, as NULL makes the headers disappear.
   */
  inline BookedAtcTableModel *
  getNotNullModel(const QString& _icao) {
    return __bookings.value(_icao, VatbookHandler::emptyBookedAtcTable);
  }
  
  static BookedAtcTableModel* emptyBookedAtcTable;
  
private:
  
  void __clear();
  void __parseData(const QString&);
  
  /* This map contains pairs airport/fir icao - atcs */
  QHash< QString, BookedAtcTableModel* > __bookings;
  
  HttpHandler* __httpHandler;
  QTimer       __timer;
  
private slots:
  
  void __dataFetched(const QString&);
  void __handleError();
  void __timeToUpdate();
  
};

#endif // VATBOOKHANDLER_H

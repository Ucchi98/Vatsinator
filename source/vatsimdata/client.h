/*
    client.h
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


#ifndef CLIENT_H
#define CLIENT_H

#include <QDateTime>
#include <QString>
#include <QStringList>

class Client {

  /*
   * Abstract class for connected client.
   * Inherited by Pilot and Controller classes.
   */

public:
  // types
  enum Type {
    PILOT, ATC
  };
  
  struct Position {
    float latitude;
    float longitude;
  };
  
  /**
   * Prevent from creating foo-clients.
   */
  Client() = delete;
  
  /**
   * The data list. This can be, for example, one line
   * obtained from vatsim data servers, divided with ":".
   * For more info see client.cpp file.
   */
  Client(const QStringList&);
  
  /**
   * Client can be pilot or ATC.
   * Use this class instead of dynamic_cast to check the subclass
   * type - it is a little bit faster.
   */
  virtual inline Client::Type clientType() const = 0;

  virtual ~Client() {}

  inline unsigned
  getPid() const { return __pid; }
  
  inline const QString &
  getCallsign() const { return __callsign; }
  
  inline const QString &
  getRealName() const { return __realName; }
  
  inline const QString &
  getServer() const { return __server; }
  
  inline const QDateTime &
  getOnlineFrom() const { return __onlineFrom; }
  
  inline const Client::Position &
  getPosition() const { return __position; }
  
protected:
  /* Client data */
  unsigned  __pid;
  QString   __callsign;
  QString   __realName;

  QString   __server;
  QDateTime __onlineFrom;

  Client::Position __position;

};

#endif // CLIENT_H

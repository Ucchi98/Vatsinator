/*
    airportdetailswindow.h
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


#ifndef AIRPORTDETAILSWINDOW_H
#define AIRPORTDETAILSWINDOW_H

#include "ui/windows/basewindow.h"

#include "ui/ui_airportdetailswindow.h"
#include "singleton.h"

class Airport;
class Controller;
class Pilot;
class WeatherForecast;
class WeatherForecastModel;

class AirportDetailsWindow :
    public BaseWindow,
    public Singleton< AirportDetailsWindow >,
    private Ui::AirportDetailsWindow {

  Q_OBJECT

public:
  AirportDetailsWindow(QWidget* = nullptr);
  virtual ~AirportDetailsWindow();

public slots:
  void show(const Airport*);
  void updateMetar();
  void updateMetar(QString);

private:
  void __updateModels(const Airport* = NULL);
  void __fillLabels(const Airport*);
  void __adjustTables();
  
private slots:
  void __updateData();
  void __updateForecast(WeatherForecastModel*);
  void __handleShowClicked();

private:
  QString __currentICAO;
  const Airport* __current;
  
  WeatherForecast* __forecast;
  
  WeatherForecastModel* __progressModel;

};

#endif // AIRPORTDETAILSWINDOW_H

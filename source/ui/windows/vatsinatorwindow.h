/*
 * vatsinatorwindow.h
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

#ifndef VATSINATORWINDOW_H
#define VATSINATORWINDOW_H

#include <QMainWindow>

#include "singleton.h"
#include "ui/ui_vatsinatorwindow.h"

class QGraphicsView;
class QLabel;
class QProgressBar;

class VatsinatorWindow :
    public QMainWindow,
    public Singleton<VatsinatorWindow>,
    private Ui::VatsinatorWindow {
  
  Q_OBJECT
  
signals:
  void autoUpdatesEnabled(bool);

public:
  explicit VatsinatorWindow(QWidget* = 0);
  virtual ~VatsinatorWindow();
  
  /**
   * Sets the specified message in the bottom-left bar corner
   * or puts simple "Last update" text.
   * @param text If specified, this text will be shown.
   */
  void statusBarUpdate(const QString& = "");
  
  /**
   * The middle part of status bar - how many clients, etc etc.
   */
  void infoBarUpdate();
  
  inline QGraphicsView *
  map() { return Map; }

  inline QProgressBar*
  progressBar() { return __progressBar; }

  inline QLabel*
  positionBox() { return PositionBox; }
  
  inline bool
  autoUpdatesEnabled() const { return EnableAutoUpdatesAction->isChecked(); }
  
protected:
  void closeEvent(QCloseEvent*) override;
  void showEvent(QShowEvent*) override;

private:
  void __storeWindowGeometry();
  void __restoreWindowGeometry();
  
private slots:
  void __dataDownloading();
  void __statusUpdated();
  void __dataUpdated();
  void __dataCorrupted();
  void __enableRefreshAction();
  
private:  
  QLabel*       __statusBox;
  QProgressBar* __progressBar;
  
  
};

#endif // VATSINATORWINDOW_H

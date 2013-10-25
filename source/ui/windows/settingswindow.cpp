/*
    settingswindow.cpp
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

#include "storage/languagemanager.h"
#include "storage/settingsmanager.h"

#include "ui/pages/abstractsettingspage.h"
#include "ui/pages/miscellaneouspage.h"

#include "ui/userinterface.h"

#include "settingswindow.h"
#include "defines.h"

SettingsWindow::SettingsWindow(QWidget* _parent) :
    BaseWindow(_parent) {
  setupUi(this);
  
  connect(qApp, SIGNAL(aboutToQuit()),
          this, SLOT(hide()));

  connect(OKCancelButtonBox,    SIGNAL(clicked(QAbstractButton*)),
          this,                 SLOT(__handleButton(QAbstractButton*)));
}

void
SettingsWindow::addPage(AbstractSettingsPage* _page) {
  __pages << _page;
  
  QListWidgetItem *item = new QListWidgetItem(CategoryList);
  
  QIcon listIcon(_page->listIcon());
  item->setIcon(listIcon);
  item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
  
  item->setText(_page->listElement());
  
  SwappingWidget->addWidget(_page);
  
  if (CategoryList->count() == 1)
    item->setSelected(true);
}

void
SettingsWindow::__handleButton(QAbstractButton* _btn) {
  if (OKCancelButtonBox->button(QDialogButtonBox::RestoreDefaults) == _btn)
    emit restoreDefaults();
  else if (OKCancelButtonBox->button(QDialogButtonBox::Apply) == _btn
        || OKCancelButtonBox->button(QDialogButtonBox::Ok) == _btn)
    emit settingsApplied();
}


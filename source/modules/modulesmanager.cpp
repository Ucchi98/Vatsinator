/*
    modulesmanager.cpp
    Copyright (C) 2012  Michał Garapich garrappachc@gmail.com

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

#include "modules/flighttracker.h"
#include "modules/modelsmatcher.h"

#include "vatsinatorapplication.h"

#include "modulesmanager.h"
#include "defines.h"

ModulesManager::ModulesManager() :
		__flightTracker(new FlightTracker()),
		__modelsMatcher(new ModelsMatcher()) {
	connect(VatsinatorApplication::GetSingletonPtr(),	SIGNAL(glInitialized()),
		this,		SLOT(__initAfterGL()),	Qt::DirectConnection);
}

ModulesManager::~ModulesManager() {
	delete __flightTracker;
	delete __modelsMatcher;
}

void
ModulesManager::init() {
	__flightTracker->init();
}

void
ModulesManager::__initAfterGL() {
	__modelsMatcher->init();
}

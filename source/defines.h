/*
    defines.h
    This file contains some const variables.
    
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

#ifndef DEFINES_H
#define DEFINES_H

#include "config.h"

// where to get all the data from
#define VATSIM_STATUS_URL "http://status.vatsim.net/status.txt"

// Vatsinator homepage url
#define VATSINATOR_HOMEPAGE "http://vatsinator.org/"

// Vatsinator_repo url
#define VATSINATOR_REPO_URL "https://raw.github.com/Garrappachc/Vatsinator-repo/master"

// set files location
#ifndef Q_OS_DARWIN

#define AIRPORTS_DB      VATSINATOR_PREFIX "WorldAirports.db"
#define FIRS_DB          VATSINATOR_PREFIX "WorldFirs.db"
#define MODELS_DAT       VATSINATOR_PREFIX "models.dat"
#define WORLD_MAP        VATSINATOR_PREFIX "WorldMap.db"
#define PIXMAPS_DIR      VATSINATOR_PREFIX "pixmaps"
#define TRANSLATIONS_DIR VATSINATOR_PREFIX "translations"

#else

#define AIRPORTS_DB      QCoreApplication::applicationDirPath() + "/../Resources/WorldAirports.db"
#define FIRS_DB          QCoreApplication::applicationDirPath() + "/../Resources/WorldFirs.db"
#define MODELS_DAT       QCoreApplication::applicationDirPath() + "/../Resources/models.dat"
#define WORLD_MAP        QCoreApplication::applicationDirPath() + "/../Resources/WorldMap.db"
#define PIXMAPS_DIR      QCoreApplication::applicationDirPath() + "/../Resources/pixmaps"
#define TRANSLATIONS_DIR QCoreApplication::applicationDirPath() + "/../Resources/translations"

#endif // Q_OS_DARWIN

// cache file name
#define CACHE_FILE_NAME "lastdata"

// below/above these values user can't zoom the map
#define ZOOM_MINIMUM                  1
#define ZOOM_MAXIMUM                  1500
#define ACTUAL_ZOOM_MINIMUM           0
#define ZOOM_NORMALIZE_COEFFICIENT    0.5
#define ZOOM_BASE                     1.1  

// the range below which the mouse is in the object's
#define OBJECT_TO_MOUSE   0.03

// how far from the airport the pilot must be to be recognized as "departing"
// or "arrived"
#define PILOT_TO_AIRPORT  0.1

// how to recognize unavailable metars
#define METAR_NO_AVAIL    "No METAR available"

// for these values the GL's context rendering size reprezents
// (-1.0; 1.0) orthogonal ranges for both x and y axes
#define BASE_SIZE_WIDTH   800
#define BASE_SIZE_HEIGHT  600

#define PILOTS_LABELS_FONT_COLOR    0, 0, 0
#define AIRPORTS_LABELS_FONT_COLOR  250, 250, 250
#define FIRS_LABELS_FONT_COLOR      173, 173, 173

// camera position won't go further
#define RANGE_Y   1.0

// fonts properties
#define PILOT_FONT_PIXEL_SIZE   10
#define PILOT_FONT_WEIGHT       QFont::Normal
#define AIRPORT_FONT_PIXEL_SIZE 8
#define AIRPORT_FONT_WEIGHT     QFont::Bold
#define FIR_FONT_PIXEL_SIZE     10
#define FIR_FONT_WEIGHT         QFont::Bold


// if debug, add MemoryTracker to the buildset
#ifndef NO_DEBUG
# define DEBUG_NEW new(__FILE__, __LINE__)
# include "vdebug/memorytracker.h"
#else
# define DEBUG_NEW new (std::nothrow)
#endif
#define new DEBUG_NEW

#endif // DEFINES_H

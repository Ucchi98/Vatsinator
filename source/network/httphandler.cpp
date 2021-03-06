/*
    httphandler.cpp
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
#include <QtNetwork>

#include "httphandler.h"

#include "defines.h"

HttpHandler::HttpHandler(QProgressBar* _pb, QObject* _parent) :
    QObject(_parent),
    __progressBar(_pb),
    __reply(0) {
}

void
HttpHandler::fetchData(const QString& _url) {
  __urls.enqueue(_url);

  if (!__reply)
    __startRequest();
}

void
HttpHandler::__startRequest() {
  if (!__urls.isEmpty()) {
    QNetworkRequest request(__urls.dequeue());
    request.setRawHeader("User-Agent", "Vatsinator " VATSINATOR_VERSION);
    __reply = __nam.get(request);
  } else {
    return;
  }

  connect(__reply, SIGNAL(finished()), this, SLOT(__finished()));
  connect(__reply, SIGNAL(readyRead()), this, SLOT(__readyRead()));
  connect(__reply, SIGNAL(error(QNetworkReply::NetworkError)),
          this,    SLOT(__onError(QNetworkReply::NetworkError)));

  if (__progressBar)
    connect(__reply, SIGNAL(downloadProgress(qint64, qint64)),
            this,    SLOT(__updateProgress(qint64, qint64)));

  __temp.clear();

  if (__progressBar)
    __progressBar->setEnabled(true);
}

void
HttpHandler::__readyRead() {
  __temp.append(__reply->readAll());
}

void
HttpHandler::__finished() {
  disconnect(__reply, SIGNAL(finished()), this, SLOT(__finished()));
  disconnect(__reply, SIGNAL(readyRead()), this, SLOT(__readyRead()));
  disconnect(__reply, SIGNAL(downloadProgress(qint64, qint64)),
             this,    SLOT(__updateProgress(qint64, qint64)));
  disconnect(__reply, SIGNAL(error(QNetworkReply::NetworkError)),
             this,    SLOT(__onError(QNetworkReply::NetworkError)));
  
  __reply->deleteLater();
  __reply = NULL;
  
  if (__progressBar) {
    __progressBar->reset();
    __progressBar->setEnabled(false);
  }
  
    __data = __temp;
    emit finished(__data);
    
    if (anyTasksLeft())
      __startRequest();
}

void
HttpHandler::__updateProgress(qint64 _bRead, qint64 _bTotal) {
  __progressBar->setMaximum(_bTotal);
  __progressBar->setValue(_bRead);
}

void
HttpHandler::__onError(QNetworkReply::NetworkError) {
  disconnect(__reply, SIGNAL(finished()), this, SLOT(__finished()));
  disconnect(__reply, SIGNAL(readyRead()), this, SLOT(__readyRead()));
  disconnect(__reply, SIGNAL(downloadProgress(qint64, qint64)),
             this,    SLOT(__updateProgress(qint64, qint64)));
  disconnect(__reply, SIGNAL(error(QNetworkReply::NetworkError)),
             this,    SLOT(__onError(QNetworkReply::NetworkError)));
  
  __reply->deleteLater();
  __reply = NULL;
  
  if (__progressBar) {
    __progressBar->reset();
    __progressBar->setEnabled(false);
  }
  
  emit fetchError();
  
  if (!__urls.isEmpty())
    __startRequest();
}

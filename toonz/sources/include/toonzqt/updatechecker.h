#pragma once

#ifndef UPDATE_CHECKER_H
#define UPDATE_CHECKER_H

#include <QtGlobal>
#include <QObject>
#include "tcommon.h"

#include <QNetworkAccessManager>
#include <QUrl>
#include <QString>
#include <QSharedPointer>
#include <QTimerEvent>

#undef DVAPI
#undef DVVAR
#ifdef TOONZQT_EXPORTS
#define DVAPI DV_EXPORT_API
#define DVVAR DV_EXPORT_VAR
#else
#define DVAPI DV_IMPORT_API
#define DVVAR DV_IMPORT_VAR
#endif

class DVAPI UpdateChecker final : public QObject {
  Q_OBJECT

  QSharedPointer<QNetworkAccessManager> manager_;

  QString m_latestVersion;

public:
  UpdateChecker(QUrl const& updateUrl);

  QString getLatestVersion() const { return m_latestVersion; }

protected:
  void timerEvent(QTimerEvent*);

protected slots:
  void httpRequestFinished(QNetworkReply*);

signals:
  /**
   ** @param error
   **
   **    0: no error;
   **    1: error in the connection;
   **    2: forced timeout
   */
  void done(int error);
};

#endif  // UPDATE_CHECKER_H

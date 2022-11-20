#ifndef UPDATECONTROLLER_H
#define UPDATECONTROLLER_H

/*
Author: Jonathan Baird
Date: 16NOV2022
Purpose: Update controller for antivirus program | Networking | Download Signatures
Contact: tr14rc3@gmail.com
*/

#include <QObject>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QFile>
#include <QTimer>
#include <QTextStream>
#include <QDataStream>


class UpdateController : public QObject{
    Q_OBJECT

public:
    UpdateController();

public slots:
    void replyFinished();
    void slotReadyRead();
    void updateDownloadProgress(qint64, qint64);
    void processIncomingData();
    void downloadSignatures();

signals:
    void resultReady(const QString);
    void currentProgress(int a, int b);
    void currentProgressFiles(int);
    void dataSize(int xx);
    void state(QString);

private:
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QNetworkReply *networkResponse;
    QTimer *fileDownloader;
    int incomingDataSize;
};
#endif // UPDATECONTROLLER_H

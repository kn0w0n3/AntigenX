#ifndef URLCHECKER_H
#define URLCHECKER_H
#include <QThread>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>

class UrlChecker: public QThread{
    Q_OBJECT

public:
    UrlChecker(QThread *parent = 0);
    void run();
    void makeRequest(QString, QString);
    ~UrlChecker(){wait();}

signals:
    void urlCheckStatus(QString);
    void streamingLogData(QString);
    void dataReadyRead(QString);

public slots:
    void readyRead(QNetworkReply *);
    void readyErrors(QNetworkReply *);

private:
    QNetworkAccessManager *googleApiManager;
    QNetworkRequest *googleApiRequest;
    QNetworkReply *googleNetworkResponse;
    bool accessManagerRunning = false;
};

#endif // URLCHECKER_H

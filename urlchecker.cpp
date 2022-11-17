#include "urlchecker.h"

UrlChecker::UrlChecker(QThread *parent) : QThread(parent){
      qDebug() << "In google thread constructor........ ";
    //Connection for the Google Safe browsing API
    googleApiManager = new QNetworkAccessManager(this);
    //connect(googleApiManager, &QNetworkAccessManager::finished, this, &UrlChecker::readyRead);
    //connect(googleApiManager, &QNetworkAccessManager::sslErrors, this, &UrlChecker::readyErrors);

}

void UrlChecker::run() {
    emit urlCheckStatus("started");

    //msleep(100); // block for x seconds


    emit urlCheckStatus("stopped");
}

void UrlChecker::makeRequest(QString googleUrl, QString jsonData){
        qDebug() << "The incoming Google string URL is: " << googleUrl;
        QNetworkAccessManager *mgr = new QNetworkAccessManager(this);
        QByteArray byteArrayData;

        byteArrayData = jsonData.toLocal8Bit();
        //byteArrayData = byteArrayData.append(jsonData);
        qDebug() << "The JSON byte array data is: " << byteArrayData;

        QByteArray urlByteArrayData;
        urlByteArrayData = urlByteArrayData.append(googleUrl);

        QUrl url = QUrl::fromUserInput(googleUrl);
        //QUrl url = googleUrl;
        QNetworkRequest request(url);

        qDebug() << "The QUrl is:" << url;
        if(url.isEmpty() == true){
            qDebug() << "The URL is emppty..............";
        }
        qDebug() << "The URL data is: " << url.toString();
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));

        //This (GET request) can be used to test if there's a response from Google without using a JSON array.
        //QNetworkReply *reply = mgr->get(request);

        //The POST request requires two arguments. The first argument is a QUrl. The second argument is a QByteArray.
        //Google provides this as an example: POST https://safebrowsing.googleapis.com/v4/threatMatches:find?key=API_KEY HTTP/1.1 - is it clear what to include in our string? No. See below.
        //The string to provide to QUrl is "https://safebrowsing.googleapis.com/v4/threatMatches:find?key=API_KEY" Leave off the HTTP/1.1 and make sure to replace the "API_KEY" text with an API key
        QNetworkReply *reply = mgr->post(request, byteArrayData);
        QObject::connect(reply, &QNetworkReply::finished, [=](){
            if(reply->error() == QNetworkReply::NoError){
                QString contents = QString::fromUtf8(reply->readAll());
                qDebug() << "Contents are: " << contents;
            }
            else{
                QString err = reply->errorString();
                qDebug() << "Error contents are: " <<  err;
            }
            reply->deleteLater();
        });
}

void UrlChecker::readyRead(QNetworkReply *reply){
    /*
    QString replyText;
    replyText = reply->readAll();
    qDebug() << "In readyRead() UrlChecker........ ";
    qDebug() << "ReplyText is: "  << replyText;

    emit this->dataReadyRead(replyText);
    */
}

void UrlChecker::readyErrors(QNetworkReply *errorReply){
    QString errorReplyText = errorReply->readAll();

    qDebug() << "In readyErrors() UrlChecker........ ";
    qDebug() << "errorReply text is: "  << errorReplyText;

}

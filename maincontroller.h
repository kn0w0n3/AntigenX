#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include <QObject>
#include <QFileInfo>
#include <QThread>
#include <QFileDialog>
#include <QStringList>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>

#include "singlescan.h"
#include "updatecontroller.h"
#include "directoryscan.h"
#include "urlchecker.h"


class MainController:  public QWidget{
    Q_OBJECT

public:
    MainController(QWidget *parent = nullptr);

signals:
    void change(QString);
    void scanStarted(void);
    void scanComplete(void);
    void sendResultToQml(QString singleScanResult);
    void sSRToQMLDone(void);
    void totalBytesToQml(int tBTQML);
    void bytesReadToQml(int bRTQML);
    void txtBytesReadToQml(QString txtBRTQML);
    void pBarActivity(QString);
    void pBarVisibility(bool);
    void fileCountInfo(QString numFilesScanned_);

    //Google Safe Browse Signals
    void urlResultsToQml(QString urlResut_1);
    void urlScanStarted();
    void urlScanComplete();

public slots:
    void singleFileScan();
    void scanDirectory();
    void handleScanStart();
    void handleScanOpsInfo(QString);
    void handleScanComplete();
    void test();
    void displayInfectedFiles(QString);
    void stopThread();
    QString getFiles();
    int getCurrentValue();
    QString getTxtCurrentValue();
    int getTotalBytesValue();
    QString getpBarText();
    bool getpBarVisibility();
    void setFiles(QString);
    void downloadSignatures();
    void updateProgressBar(int, int);
    void updateProgBarFileOps(int);
    void updateStatus(QString);

    QString getDirScanFileCount();

    void checkUrl(QString);
    void processNetworkData(QString);

private:
    SingleScan *singleFileScanThread;
    bool checkTextOne;
    bool checkTextTwo;
    QString *fileName;
    QString theInfectedFile;
    UpdateController *updateController;
    QThread *updateThread;
    int currentValue;
    int totBytesVal;
    QString gValBarActivity;
    bool gValBarVisibility;
    DirectoryScan *directoryScan;
    int fileCount;
    QString txtBytestoQML = "50";
    QString dirScanedFileCount;
    UrlChecker *urlChecker;
    QJsonObject jSonObject;
    QString jsonFilePath = "/home/voldem0rt/Documents/Qt_Projects/AntigenX-main/url-check-json2.txt";
    QString googleUrl = "https://safebrowsing.googleapis.com/v4/threatMatches:find?key=";
    //QString googleUrl = "https://safebrowsing.googleapis.com/v4/threatLists?key=";

    QString urlToCheck = "";
    //QString apiKey = ""

    QString json_string;
    QJsonDocument testDoc;
    QByteArray jsonByteArray;

    //Variables for JSON data returned from Google
    QString googleReplyData;
    QString matches_G;
    QString threatType_G;
    QString SOCIAL_ENGINEERING_G;
    QString platformType_G;
    QString threat_G;
    QString url_G;
};

#endif // MAINCONTROLLER_H

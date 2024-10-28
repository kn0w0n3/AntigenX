#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QThread>
#include <QWidget>

//File Ops Libs
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>

//Network Libs
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

//JSON Libs
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QString>

//Developer Classes
#include "singlescan.h"
#include "updatecontroller.h"
#include "directoryscan.h"

#include <QDebug>

class MainController:  public QWidget{
    Q_OBJECT

public:
    MainController(QWidget *parent = nullptr);

signals:
    //Directory Scan Signals
    void dScanStarted(void);
    void dScanDone(void);
    void dNumFilesScanned(QString dirNumFilesScaned_X);
    void dInfectedFiles(QString infectedFiles_X);

    void change(QString);

    //Single Scan Signals
    void sScanStarted(void);
    void sScanDone(void);
    void sendResultToQml(QString singleScanResult);
    void sInfectedFiles(QString sInfectedFiles_Y);
    void sSRToQMLDone(void);

    //Progress bar signals
    void totalBytesToQml(int tBTQML);
    void bytesReadToQml(int bRTQML);
    void txtBytesReadToQml(QString txtBRTQML);
    void pBarActivity(QString);
    void pBarVisibility(bool);

    //Google Safe Browse Signals
    void urlResultsToQml(QString urlResut_1);
    void urlScanStarted(void);
    void urlScanComplete(void);

public slots:
    void scanDirectory(void);

    //Slots for single scan
    void singleFileScan(void);
    void handleScanStart(void);
    void handleScanOpsInfo(QString);
    void relayScanDoneDir(void);
    void relayScanDoneSir(void);

    void displayInfectedFiles(QString);
    //void stopThread(void);
    //QString getFiles();

    //Slots for progress bar
    //int getCurrentValue(void);
    //QString getTxtCurrentValue(void);
    //int getTotalBytesValue(void);
    //QString getpBarText();

    void updateProgressBar(int, int);
    //void updateProgBarFileOps(int);
    //void setFiles(QString);
    void downloadSignatures(void);
    //bool getpBarVisibility(void);

    //void updateStatus(QString);
    void checkUrl(QString);
    void processNetworkData(QString);

private:
    SingleScan *singleFileScanThread;
    UpdateController *updateController;
    DirectoryScan *directoryScan;
    QThread *updateThread;

    bool checkTextOne;
    bool checkTextTwo;
    bool gValBarVisibility;

    int currentValue;
    int totBytesVal;
    int fileCount;

    QString *fileName;
    QString theInfectedFile;
    QString txtBytestoQML = "50";
    QString dirScanedFileCount;
    QString gValBarActivity;

    //URL and JSON variables
    QJsonObject jSonObject;
    QString json_string;

    //Linux Path
    //QString jsonFilePath = "/home/voldem0rt/Documents/Qt_Projects/AntigenX-main/url-check-json2.txt";
    //Windows Path
    QString jsonFilePath = "C:/Users/Voldem0rt/Documents/Qt_Projects/AntigenX/url-check-json2.txt";
    //QString googleUrl = "https://safebrowsing.googleapis.com/v4/threatLists?key=YOUR_API_KEY";

    QString urlToCheck = "";
    //QString apiKey = ""

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

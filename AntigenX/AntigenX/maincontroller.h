#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include <QObject>
#include <QFileInfo>
#include <QThread>
#include <QFileDialog>
#include <QStringList>
//#include <QCryptographicHash>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QWidget>
#include "singlescan.h"
#include "updatecontroller.h"
#include "directoryscan.h"


class MainController:  public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString infectFile READ getFiles WRITE setFiles NOTIFY sendResultToQml)

    //Send bytes read to the progress bar to GUI
    Q_PROPERTY(float currentValueQml READ getCurrentValue NOTIFY bytesReadToQml)

    //Set the total number of bytes
    Q_PROPERTY(float totalBytesValueQml READ getTotalBytesValue NOTIFY totalBytesToQml)

    //Control text over progress bar
    Q_PROPERTY(QString progressBarActivity READ getpBarText NOTIFY pBarActivity)

    //Set visibility of progress bar
    Q_PROPERTY(bool progressBarVisibility READ getpBarVisibility NOTIFY pBarVisibility)

public:
    MainController(QWidget *parent = nullptr);
    //Q_INVOKABLE void testx(QString strg) {qDebug() << "Received string: " << strg;}

signals:
    void change(QString);
    void sendResultToQml(QString);
    void totalBytesToQml(qint64);
    void bytesReadToQml(qint64);
    void pBarActivity(QString);
    void pBarVisibility(bool);

public slots:
    void singleFileScan();
    void scanDirectory();
    void handleScanStart();
    void handleScanComplete();
    void test();
    void displayInfectedFiles(QString);
    void stopThread();
    QString getFiles();
    int getCurrentValue();
    int getTotalBytesValue();
    QString getpBarText();
    bool getpBarVisibility();
    void setFiles(QString);
    void downloadSignatures();
    void updateProgressBar(qint64, qint64);
    void updateProgBarFileOps(int);
    void updateStatus(QString);

private:
    SingleScan *singleFileScanThread;
    bool checkTextOne;
    bool checkTextTwo;
    QString *fileName;
    QString theInfectedFile;
    UpdateController *updateController;
    QThread *updateThread;
    float currentValue;
    float totBytesVal;
    QString gValBarActivity;
    bool gValBarVisibility;
    DirectoryScan *directoryScan;
    int fileCount;
};

#endif // MAINCONTROLLER_H

#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include <QObject>
#include <QFileInfo>
#include <QThread>
#include <QFileDialog>
#include <QStringList>
#include <QCryptographicHash>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QWidget>
#include "singlescan.h"

class MainController:  public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString infectFile READ getFiles WRITE setFiles NOTIFY sendResultToQml)
public:
    MainController(QWidget *parent = nullptr);


    Q_INVOKABLE void testx(QString strg) {qDebug() << "Received string: " << strg;}

signals:
    void change(QString);
    void sendResultToQml(QString);

public slots:
    void singleFileScan();
    void handleScanStart();
    void handleScanComplete();
    void displayInfectedFiles(QString);
    void stopThread();
    QString getFiles();
    void setFiles(QString);

private:
    SingleScan *singleFileScanThread;
    bool checkTextOne;
    bool checkTextTwo;
    QString *fileName;
    QString theInfectedFile;

};

#endif // MAINCONTROLLER_H

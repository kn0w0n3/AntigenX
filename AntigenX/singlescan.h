#ifndef SINGLESCAN_H
#define SINGLESCAN_H

#include <QThread>
#include <QObject>
#include <QFileDialog>
//#include <QStringListIterator>
#include <QCryptographicHash>
#include <QListIterator>
#include <QTextStream>
#include <QDebug>

class SingleScan: public QThread{
    Q_OBJECT

public:
    SingleScan(QThread *parent = 0);
    void run();
    bool stopSingleThread = false;

signals:
    void scanStart();
    void scanComplete();
    void infectedFiles(QString);
    void scannedFileNumS(QString);

public slots:
    void getRequiredFiles();

private:
    QStringList virusList;
    int hashType;
    QByteArray hashDataMd5;
    QStringList hashList;
    QString fileName;
    QString filePath;
    int numScannedFiles;
    bool fileInfected;
};
#endif // SINGLESCAN_H

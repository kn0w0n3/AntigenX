#ifndef SINGLESCAN_H
#define SINGLESCAN_H

#include <QThread>
#include <QObject>
#include <QFileDialog>
//#include <QStringListIterator>
#include <QCryptographicHash>
#include <QListIterator>
#include <QTextStream>

class SingleScan: public QThread

{
    Q_OBJECT
    //Q_PROPERTY(QString fileToDisplay READ NOTIFY infectedFiles)

public:
    SingleScan(QThread *parent = 0);
    void run();
    bool stopSingleThread;

signals:
    void scanStart();
    void scanComplete();
    void infectedFiles(QString);

public slots:
    void getRequiredFiles();

private:
    QStringList virusList;
    //QString passFileToScan;
    //QStringList alist;
    //QString location;
    //QStringList hashValues;
    int hashType;
    //QStringList currentList;
    //QString theInfectedFile;
    QByteArray hashDataMd5;
    QStringList hashList;
    QString fileName;
    QString filePath;

};
#endif // SINGLESCAN_H

#ifndef SINGLESCAN_H
#define SINGLESCAN_H

#include <QThread>
#include <QObject>
#include <QFileDialog>
//#include <QStringListIterator>
#include <QListIterator>

class SingleScan: public QThread

{
    Q_OBJECT
    //Q_PROPERTY(QString fileToDisplay READ NOTIFY infectedFiles)

public:
    SingleScan(QStringList, QString, QString, QStringList, QThread *parent = 0);
    void run();
    bool stopSingleThread;

signals:
    void scanStart();
    void scanComplete();
    void infectedFiles(QString);

public slots:


private:
    QStringList virusList;
    QString passFileToScan;
    QStringList alist;
    QString location;
    QStringList hashValues;
    int hashType;
    //QStringList currentList;
    //QString theInfectedFile;

};
#endif // SINGLESCAN_H

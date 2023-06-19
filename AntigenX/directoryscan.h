#ifndef DIRECTORYSCAN_H
#define DIRECTORYSCAN_H

/*
Author: Jonathan Baird
Date: 16NOV2022
Purpose: Thread for directory scan
Contact: tr14rc3@gmail.com
*/

#include <QThread>
#include <QObject>
#include <QDirIterator>
#include <QFileDialog>
#include <QTextStream>
#include <QListIterator>
#include <QCryptographicHash>
#include <QDebug>

class DirectoryScan : public QThread{
    Q_OBJECT

public:
    DirectoryScan(QThread *parent = 0);
    void run();
    bool stopThread;

signals:
    void scanStartx();
    void scanCompletex();
    void infectedFilesx(QString);
    void scannedFileNumD(QString);

public slots:
void getRequiredFiles();

private:
    QStringList directories;
    QStringList virusList;
    QStringList list;
    QString tempX;
    QByteArray hashDataMd5;
    QStringList hashList;
    QStringList pathForHashList;
    QStringList filenameOfHash;
    int lineNumberOfVirusFile;
    int numberOfHashesTested;
    int lineNumberOfFilePaths;
    bool exitVirusListLoop;
    int expectedNumFilesToScan;
    bool infectedFiles;
};
#endif // DIRECTORYSCAN_H

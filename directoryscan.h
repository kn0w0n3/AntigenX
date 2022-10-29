#ifndef DIRECTORYSCAN_H
#define DIRECTORYSCAN_H
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

public slots:
void getRequiredFiles();

private:
    QStringList directories;
    QStringList virusList;
    QStringList list;
    QByteArray hashDataMd5;
    QStringList hashList;
    QStringList pathForHashList;
    QStringList filenameOfHash;
    int lineNumberOfVirusFile;
    int numberOfHashesTested;
    int lineNumberOfFilePaths;
    bool exitVirusListLoop;
    int numFilesScanned;
};
#endif // DIRECTORYSCAN_H

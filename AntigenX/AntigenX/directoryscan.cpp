#include "directoryscan.h"

DirectoryScan::DirectoryScan(QThread *parent) : QThread(parent) {
   getRequiredFiles();
}

void DirectoryScan::run() {
    emit scanStartx();

    foreach (QString element, list) {
        QDirIterator directory(element, QDirIterator::Subdirectories);
        while (directory.hasNext()) {
            if(!stopThread){
                directory.next();
                foreach (const QString &str, virusList) {
                    if (directory.fileName() == str){
                        emit infectedFilesx(directory.filePath());
                    }
                }
            }
        }
    }
    emit scanCompletex();
}

void DirectoryScan::getRequiredFiles(){
    QString file = QFileDialog::getExistingDirectory(Q_NULLPTR, tr("Select Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    list<< file;

    if(file.isEmpty()){
        return;
    }

    QFile inputFile("/home/voldem0rt/Desktop/AntigenX/AntigenX/viruslist.txt");
    if (inputFile.open(QIODevice::ReadOnly)){
        QTextStream in(&inputFile);

        //QStringList virusList;
        while (!in.atEnd()){
           QString line = in.readLine();
            virusList << line;
        }
        inputFile.close();
    }
}



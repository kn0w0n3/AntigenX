#include "singlescan.h"

/*
Author: Jonathan Baird
Date: 16NOV2022
Purpose: Thread for single scan
Contact: tr14rc3@gmail.com
*/

SingleScan::SingleScan(QThread *parent) : QThread(parent){
    numScannedFiles = 0;
    fileInfected = false;
    getRequiredFiles();
}

void SingleScan::run(){
    qDebug() << "In single scan run()..........";
    emit scanStart();
    //numScannedFiles++;
    emit scannedFileNumS("1");
        foreach (const QString &str, virusList){
            //qDebug() << "In single scan first for loop..........";
            hashType = 0;
            if(stopSingleThread == false){
                foreach(const QString &hString, hashList){
                        //qDebug() << "In single scan second for loop..........";
                    hashType++;
                    if (hString == str) {
                        //currentList << location;
                        emit infectedFiles(fileName + " " + filePath);
                        emit infectedFiles("Hash: " + hString);
                        fileInfected = true;

                        if(hashType == 1){
                            emit infectedFiles("Hash Type: MD4");
                        }
                        else if(hashType == 2){
                            emit infectedFiles("Hash Type: MD5");
                        }
                        else if(hashType == 3){
                            emit infectedFiles("Hash Type: SHA1");
                        }
                        else if(hashType == 4){
                            emit infectedFiles("Hash Type: SHA256");
                        }
                    }
                    //else{
                        //emit infectedFiles("0");
                        //qDebug() << "Trying to emit infected files 0..........";
                    //}
                }
            }
        }
        if(fileInfected == false){
            emit infectedFiles("0");
        }
        emit scanComplete();
}

void SingleScan::getRequiredFiles(){
    qDebug() << "In get required files..........";
    QString file = QFileDialog::getOpenFileName(Q_NULLPTR, tr("Select Directory"), "/home");
    QFileInfo fi(file);
    fileName = fi.fileName();
    QFile fileLocation(file);
    filePath = fi.filePath();
    //qDebug() << "In get required files past vars..........";
    //Check to see if file is bigger than 2 GB
    if(fi.size() > 2147483648){
        //theInfectedFile = "FIle size limit is 2 gb";
        //emit sendResultToQml(theInfectedFile);
        //return;
        //qDebug() << "In fi size if statement..........";
    }
    if (fileLocation.open(QIODevice::ReadOnly)){
        //qDebug() << "In hashing funtion";
        QByteArray fileData = fileLocation.readAll();
        hashDataMd5 = QCryptographicHash::hash(fileData, QCryptographicHash::Md5).toHex();
        hashList << hashDataMd5;
        //qDebug() << hashDataMd5;
    }

    //Determining location options for deployment needs to be looked into
    //Move this to thread and perhaps the hashing
    //Need to automate the location
    QFile inputFile("/home/voldem0rt/Documents/Qt_Projects/AntigenX-main/viruslist.txt");
    if (inputFile.open(QIODevice::ReadOnly)) {
        //qDebug() << "In file read funtion";
        QTextStream in(&inputFile);
        while (!in.atEnd()) {

            QString line = in.readLine();
            virusList << line;
        }
        inputFile.close();
    }
}

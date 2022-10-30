#include "singlescan.h"

SingleScan::SingleScan(QThread *parent) : QThread(parent){
    numScannedFiles = 0;
    getRequiredFiles();
}

void SingleScan::run(){
    emit scanStart();
    //numScannedFiles++;
    emit scannedFileNumS("1");
        foreach (const QString &str, virusList){   
            hashType = 0;
            if(!stopSingleThread){
                foreach(const QString &hString, hashList){

                    hashType++;
                    if (hString == str) {
                        //currentList << location;
                        emit infectedFiles(fileName + " " + filePath);
                        emit infectedFiles("Hash: " + hString);

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
                }
            }
        }
        emit scanComplete();
}

void SingleScan::getRequiredFiles(){
    QString file = QFileDialog::getOpenFileName(Q_NULLPTR, tr("Select Directory"), "/home");
    QFileInfo fi(file);
    fileName = fi.fileName();
    QFile fileLocation(file);
    filePath = fi.filePath();

    //Check to see if file is bigger than 2 GB
    if(fi.size() > 2147483648){
        //theInfectedFile = "FIle size limit is 2 gb";
        //emit sendResultToQml(theInfectedFile);
        //return;
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
    QFile inputFile("/home/voldem0rt/Desktop/AntigenX-main/viruslist.txt");
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

#include "singlescan.h"

SingleScan::SingleScan(QStringList list, QString fileToScan, QString fileLocation, QStringList hash, QThread *parent) : QThread(parent), virusList(list), passFileToScan(fileToScan), location(fileLocation), hashValues(hash){


}

void SingleScan::run() {
    emit scanStart();
        foreach (const QString &str, virusList) {
            hashType = 0;
            if(!stopSingleThread){
                foreach(const QString &hString, hashValues){
                    //qDebug() << hString;
                    //testing only remove later
                    emit infectedFiles(location);
                    hashType++;
                    if (hString == str) {
                        //currentList << location;
                        emit infectedFiles(location);
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





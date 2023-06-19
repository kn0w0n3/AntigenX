#include "updatecontroller.h"

UpdateController::UpdateController(){

    //Create the network access manager for dowloading updates/signature files.
    manager = new QNetworkAccessManager(this);

    //Timer to download signatures every ten seconds.
    fileDownloader = new QTimer();
    connect(fileDownloader, SIGNAL(timeout()), this, SLOT(downloadSignatures()));
    qDebug() << "Update controller initializing";
    //fileDownloader->start(30000);
    //downloadSignatures();
}

void UpdateController::replyFinished(){
    //qDebug() << networkResponse;
}

//Get the data size
void UpdateController::slotReadyRead(){
    incomingDataSize = static_cast<int>(networkResponse->size());
    //qDebug()<<incomingDataSize;
}

//Get the sie of the file and update the progress bar via signals and slots.
void UpdateController::updateDownloadProgress(qint64 bytesRead, qint64 bytesTotal){

    int x = static_cast<int>(bytesRead);
    int y = static_cast<int>(bytesTotal);
    qDebug()<< "read bytes qint64 to string " + QString::number(x) ;
    qDebug()<<"bytes total  qint64 to string " + QString::number(y);
    //emit state("Downloading");
    emit currentProgress(x, y);
}

//Process the data and write to file
void UpdateController::processIncomingData(){
    emit dataSize(incomingDataSize);
    qDebug() << "The data size... " + QString::number(incomingDataSize);
    //QFile file("C:/Users/Voldem0rt/Documents/Qt_Projects/AntigenX/viruslist.txt");
    QFile file("/home/voldem0rt/Desktop/AntigenX-main/viruslist.txt");
    if (file.open(QIODevice::WriteOnly)){
        int size = 0;
        while(size <= incomingDataSize){
            QTextStream out(&file);
            out << networkResponse->readLine(20);
            size += 20;
            emit currentProgressFiles(size);
            emit state("Installing");
            if(size >= incomingDataSize){
                emit currentProgressFiles(incomingDataSize);
                emit state("Complete");
            }
        }
    }else{
        qDebug() << "File Error";
        return;
    }
}

//Set the URL for the file download. Connect signals and slots to get the data and metadata.
void UpdateController::downloadSignatures(){
    qDebug() << "Requesting data over network!";

    //392mb file size test
     request.setUrl(QUrl("https://www.secretcitylabs.com/VirusShare_00000.md5.txt"));
    //request.setUrl(QUrl("https://cdimage.kali.org/kali-2020.4/kali-linux-2020.4-installer-netinst-amd64.iso"));

    networkResponse = manager->get(request);
    connect(networkResponse, &QNetworkReply::finished, this, &UpdateController::processIncomingData);
    connect(networkResponse, &QIODevice::readyRead, this, &UpdateController::slotReadyRead);
    connect(networkResponse, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(updateDownloadProgress(qint64,qint64)));
}

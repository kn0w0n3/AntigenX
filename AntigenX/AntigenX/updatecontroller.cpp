#include "updatecontroller.h"

UpdateController::UpdateController(){
    //Create the network access manager
    manager = new QNetworkAccessManager(this);

    //Timer to download signatures every ten seconds.
    fileDownloader = new QTimer();
    connect(fileDownloader, SIGNAL(timeout()), this, SLOT(downloadSignatures()));
    fileDownloader->start(120000);
    downloadSignatures();
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
    //qDebug()<<bytesTotal;
    //qDebug()<<bytesRead;
    //emit state("Downloading");
    emit currentProgress(bytesRead, bytesTotal);
}

//Process the data and write to file
void UpdateController::processIncomingData(){
    emit dataSize(incomingDataSize);
    //qDebug() << "The data size" + incomingDataSize;
    QFile file("/home/voldem0rt/Desktop/AntigenX/AntigenX/viruslist.txt");
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
     request.setUrl(QUrl("https://www.antigen-x.com/viruslist.txt"));
    //request.setUrl(QUrl("http://212.183.159.230/1GB.zip"));
    //request.setUrl(QUrl("http://212.183.159.230/512MB.zip"));
    //request.setUrl(QUrl("http://212.183.159.230/5MB.zip"));


    //request.setUrl(QUrl("https://cdimage.kali.org/kali-2020.4/kali-linux-2020.4-installer-netinst-amd64.iso"));

    networkResponse = manager->get(request);
    connect(networkResponse, &QNetworkReply::finished, this, &UpdateController::processIncomingData);
    connect(networkResponse, &QIODevice::readyRead, this, &UpdateController::slotReadyRead);
    connect(networkResponse, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(updateDownloadProgress(qint64,qint64)));
}

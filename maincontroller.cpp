#include "maincontroller.h"

MainController::MainController(QWidget *parent) :QWidget(parent){
    fileCount = 0;
}

void MainController::singleFileScan(){
    singleFileScanThread = new SingleScan();
    connect(singleFileScanThread, &SingleScan::scanStart, this, &MainController::handleScanStart);
    connect(singleFileScanThread, &SingleScan::scanComplete, this, &MainController::handleScanComplete);
    connect(singleFileScanThread, &SingleScan::infectedFiles, this, &MainController::displayInfectedFiles);
    connect(singleFileScanThread, &SingleScan::scannedFileNumS, this, &MainController::handleScanOpsInfo);

    connect(singleFileScanThread, &SingleScan::finished, singleFileScanThread, &QObject::deleteLater);
    singleFileScanThread->start();
}

//TODO Set up the scan start message for directory scan to notify qml.
void MainController::scanDirectory(){
    directoryScan = new DirectoryScan();
    connect(directoryScan, &DirectoryScan::scanStartx, this, &MainController::handleScanStart);
    connect(directoryScan, &DirectoryScan::scanCompletex, this, &MainController::handleScanComplete);
    connect(directoryScan, &DirectoryScan::infectedFilesx, this, &MainController::displayInfectedFiles);
    connect(directoryScan, &DirectoryScan::scannedFileNumD, this, &MainController::handleScanOpsInfo);
    connect(directoryScan, &DirectoryScan::finished, directoryScan, &QObject::deleteLater);
    //directoryScan->stopThread = false;
    directoryScan->start();
}

//Set message on screen based on operation
void MainController::handleScanStart(){
    //qDebug() << "Back in main control hndle scan start";
    emit scanStarted();
}

void MainController::handleScanOpsInfo(QString fileNumData){
    //qDebug() << fileNumData;
    //qDebug() << "In handleScanOPs in Main.......... file count";
    dirScanedFileCount = fileNumData;
    emit fileCountInfo(dirScanedFileCount);
}

//Display info on screen based on scan completion
void MainController::handleScanComplete(){
    if(fileCount > 0){
        //send message to qml
        fileCount = 0;
    }else{
        theInfectedFile = "No Threats Found!";
        emit sendResultToQml(theInfectedFile);
        emit scanComplete();
    }
}

void MainController::test(){
    //qDebug() << "works now";
}

//Receive data from the thread and send it the the qml GUI
void MainController::displayInfectedFiles(QString files){
     //qDebug() << "In display infected files";
     fileCount++;
     qDebug() << fileCount;
     theInfectedFile = files;
     //Send the data to the GUI
     emit sendResultToQml(theInfectedFile);
}

void MainController::stopThread(){

}

QString MainController::getFiles(){
    return theInfectedFile;
}

int MainController::getCurrentValue(){
    return currentValue;
}

QString MainController::getTxtCurrentValue(){
     txtBytestoQML = QString::number(currentValue);
     //qDebug() << txtBytestoQML;
     return txtBytestoQML;
}

int MainController::getTotalBytesValue(){
    return totBytesVal;
}

QString MainController::getpBarText(){
    return gValBarActivity;
}

bool MainController::getpBarVisibility(){
    return gValBarVisibility;
}

void MainController::setFiles(QString){

}

void MainController::downloadSignatures(){
    //qDebug() <<"Attempting to download signatures......";
    updateThread = new QThread();
    updateController = new UpdateController();
    connect(updateController, &UpdateController::currentProgress, this, &MainController::updateProgressBar);
    connect(updateController, &UpdateController::currentProgressFiles, this, &MainController::updateProgBarFileOps);
    connect(updateController, &UpdateController::state, this, &MainController::updateStatus);
    updateController->moveToThread(updateThread);
    connect(updateThread, &QThread::finished, updateController, &QObject::deleteLater);
    updateThread->start();
}

//Send Progress Bar download values to QML GUI
void MainController::updateProgressBar(int bytesRead, int totalBytes ){
    emit pBarActivity("Downloading...");
    totBytesVal = totalBytes;
    //qDebug() << totBytesVal;
    currentValue = bytesRead;
    //qDebug() << currentValue;
    emit totalBytesToQml(totalBytes);
    emit txtBytesReadToQml(txtBytestoQML);
    emit bytesReadToQml(bytesRead);    
}

void MainController::updateProgBarFileOps(int n){

}

void MainController::updateStatus(QString state){

}

QString MainController::getDirScanFileCount(){
    return dirScanedFileCount;
    emit fileCountInfo(dirScanedFileCount);
}

void MainController::checkUrl(QString userSuppliedUrl){

    urlToCheck  = userSuppliedUrl;
    qDebug()<<"In check checkUrl() function.........";

    //Set the file path for the text file containing the JSON data
    QFile jsonTextFile(jsonFilePath);

    //Check to see if the file is open for writing
    if(!jsonTextFile.open(QIODevice::ReadOnly)){
        qDebug()<<"Failed to open " << jsonFilePath;
        //exit(1);
    }

        //Read the text from the file
        QTextStream file_text(&jsonTextFile);
        json_string = file_text.readAll();
        //qDebug() <<"The JSON string text from the file is: " << json_string;


    jsonTextFile.close();

    jsonByteArray = json_string.trimmed().toLocal8Bit();
    //qDebug() << "The JSON byte array data is: " << jsonByteArray;

    qDebug() << "The Google string URL is: " << googleUrl;
    QNetworkAccessManager *mgr = new QNetworkAccessManager(this);

    QUrl url = QUrl::fromUserInput(googleUrl);
    //QUrl url = googleUrl;
    QNetworkRequest request(url);
    qDebug() << "The URL data is: " << url.toString();

    if(url.isEmpty() == true){
        qDebug() << "The URL is emppty..............";
    }

    //Set header for JSON as specified by Google.
    //POST https://safebrowsing.googleapis.com/v4/threatMatches:find?key=API_KEY HTTP/1.1
    //Content-Type: application/json
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //This (GET request) can be used to test if there's a response from Google without using a JSON array.
    //QNetworkReply *reply = mgr->get(request);

    //The POST request requires two arguments. The first argument is a QUrl. The second argument is a QByteArray.
    //Google provides this as an example: POST https://safebrowsing.googleapis.com/v4/threatMatches:find?key=API_KEY HTTP/1.1 - is it clear what to include in our string? No. See below.
    //The string to provide to QUrl is "https://safebrowsing.googleapis.com/v4/threatMatches:find?key=API_KEY" Leave off the HTTP/1.1 and make sure to replace the "API_KEY" text with an API key
    QNetworkReply *reply = mgr->post(request, jsonByteArray);
    QObject::connect(reply, &QNetworkReply::finished, [=](){
        if(reply->error() == QNetworkReply::NoError){
            //QByteArray arrayContents = reply->readAll();
            QString contents = QString::fromUtf8(reply->readAll());
            googleReplyData = contents;
            emit urlResultsToQml(googleReplyData);
            qDebug() << "Reply from Google is: " << contents;
            //qDebug() << "Saved Reply from Google is: " << contents;
            //Display the data on GUI labels.
        }
        else{
            QString err = reply->errorString();
            qDebug() << "Error contents are: " <<  err;
        }
        reply->deleteLater();
    });
//emit urlScanComplete();

}




void MainController::processNetworkData(QString ApiData){
    qDebug() << ApiData;
}



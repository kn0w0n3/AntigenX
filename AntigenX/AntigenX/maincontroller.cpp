#include "maincontroller.h"

MainController::MainController(QWidget *parent) :QWidget(parent){
//QFileDialog dialog(this);
    fileCount = 0;
    downloadSignatures();
}

void MainController::singleFileScan(){    
    singleFileScanThread = new SingleScan();
    //connect(singleFileScanThread, &SingleScan::scanStart, this, &MainController::handleScanStart);
    connect(singleFileScanThread, &SingleScan::scanComplete, this, &MainController::handleScanComplete);
    connect(singleFileScanThread, &SingleScan::infectedFiles, this, &MainController::displayInfectedFiles);
    connect(singleFileScanThread, &SingleScan::finished, singleFileScanThread, &QObject::deleteLater);
    singleFileScanThread->start();
}

void MainController::scanDirectory(){
    directoryScan = new DirectoryScan();
    //connect(directoryScan, &DirectoryScan::scanStartx, this, &MainController::handleScanStart);
    connect(directoryScan, &DirectoryScan::scanCompletex, this, &MainController::handleScanComplete);
    connect(directoryScan, &DirectoryScan::infectedFilesx, this, &MainController::displayInfectedFiles);
    connect(directoryScan, &DirectoryScan::finished, directoryScan, &QObject::deleteLater);
    //directoryScan->stopThread = false;
    directoryScan->start();
}

//Set message on screen based on operation
void MainController::handleScanStart(){
    qDebug() << "Back in main controll hndle scan start";
}

//Display info on screen based on scan completion
void MainController::handleScanComplete(){
    //if the ui list is empty, add no threats found to the screen
    qDebug() << "At handle scan complete";
    //qDebug() << fileCount;
    if(fileCount > 0){
        //send message to qml
        fileCount = 0;
    }else{
        theInfectedFile = "No Threats Found!";
        emit sendResultToQml(theInfectedFile);
        qDebug() << "SHOUL D SEND MESSAGE NOW";
    }
}

void MainController::test(){
    qDebug() << "works now";
}

//Receive data from the thread and send it the the qml GUI
void MainController::displayInfectedFiles(QString files){
    qDebug() << "In display infected files";
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
    //qDebug()<< currentValue;
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
    //qDebug() <<"Attempting to download signatures!";
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
void MainController::updateProgressBar(qint64 bytesRead, qint64 totalBytes ){
    gValBarActivity = "Downloading...";
    gValBarVisibility = true;
    emit pBarActivity("Downloading...");
    emit pBarVisibility(true);
    totBytesVal = totalBytes;
    currentValue = bytesRead;
    emit totalBytesToQml(totalBytes);
    emit bytesReadToQml(bytesRead);
    if(currentValue >= totBytesVal ) {
        currentValue = 0;
        emit bytesReadToQml(currentValue);
        gValBarActivity = "";
        emit pBarActivity("");
        gValBarVisibility = false;
        emit pBarVisibility(false);
    }
}

void MainController::updateProgBarFileOps(int n){


}

void MainController::updateStatus(QString state){

}




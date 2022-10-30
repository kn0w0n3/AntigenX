#include "maincontroller.h"

MainController::MainController(QWidget *parent) :QWidget(parent){
    fileCount = 0;
    database = new Database();
    //connect(directoryScan, &DirectoryScan::scannedFileNum, this, &MainController::handleScanOpsInfo);
    //downloadSignatures();
    //qDebug() << "Emitting file count test.....";
    //emit fileCountInfo(dirScanedFileCount);
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

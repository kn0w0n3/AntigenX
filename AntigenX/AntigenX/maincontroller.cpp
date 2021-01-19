#include "maincontroller.h"

MainController::MainController(QWidget *parent) :QWidget(parent){
//QFileDialog dialog(this);

}

void MainController::singleFileScan(){
//qDebug() << "Hello world";


    //stopMouseMovement = true;
    //if(!checkTextOne){

        //ui->listWidget->clear();
        QString file = QFileDialog::getOpenFileName(this, tr("Select Directory"), "/home");

        QFileInfo fi(file);
        QString name = fi.fileName();
        QFile fileLocation(file);
        //QString info = fileLocation;
        //qDebug() << info;

        //QByteArray hashDataMd4;
        QByteArray hashDataMd5;
        //QByteArray hashDataSha1;
        //QByteArray hashDataSha256;

        QStringList hashList;

        //Check to see if file is bigger than 2 GB
        //if(fi.size() > 2147483648){
             //ui->listWidget->addItem("Error: File size exceeded. Maximum file size is 2GB");

             //return;
        //}

        if (fileLocation.open(QIODevice::ReadOnly)){
            qDebug() << "In hashing funtion";
            QByteArray fileData = fileLocation.readAll();
            //hashDataMd4 = QCryptographicHash::hash(fileData, QCryptographicHash::Md4).toHex();
            hashDataMd5 = QCryptographicHash::hash(fileData, QCryptographicHash::Md5).toHex();
           //hashDataSha1 = QCryptographicHash::hash(fileData, QCryptographicHash::Sha1).toHex();
            //hashDataSha256 = QCryptographicHash::hash(fileData, QCryptographicHash::Sha256).toHex();
            //hashList << hashDataMd4 << hashDataMd5 << hashDataSha1 << hashDataSha256;
            hashList << hashDataMd5;
            qDebug() << hashDataMd5;
        }

        //This will need to be a permanant location in st
        QFile inputFile("/home/voldem0rt/Desktop/AntigenX/AntigenX/viruslist.txt");
        if (inputFile.open(QIODevice::ReadOnly)) {
            qDebug() << "In file read funtion";
            QTextStream in(&inputFile);

            QStringList virusList;
            while (!in.atEnd()) {

                QString line = in.readLine();
                virusList << line;
                qDebug() << line;
            }
            inputFile.close();

            singleFileScanThread = new SingleScan(virusList, name, file, hashList);
            connect(singleFileScanThread, &SingleScan::scanStart, this, &MainController::handleScanStart);
            connect(singleFileScanThread, &SingleScan::scanComplete, this, &MainController::handleScanComplete);
            connect(singleFileScanThread, &SingleScan::infectedFiles, this, &MainController::displayInfectedFiles);
            //connect(singleFileScanThread, &SingleScan::finished, singleScanThread, &QObject::deleteLater);
            //singleFileScanThread->stopSingleThread = false;
            singleFileScanThread->start();
            //startAnimation();
            //startGearAnimation();

            //if(checkTextTwo){
                //delete textTwo;
                //checkTextTwo = false;
            //}
        }
    //}
    else{

        //warningDialog = new WarningDialog();
        //warningDialog->setWindowFlags(Qt::FramelessWindowHint);
        //warningDialog->exec();
    }

}

void MainController::handleScanStart(){
    qDebug() << "Back in main controll hndle scan start";
}

void MainController::handleScanComplete(){
    //if the ui list is empty, add no threats found to the screen
}

void MainController::displayInfectedFiles(QString files){
     theInfectedFile = files;
     //Now send the data to the qml screen
     qDebug() << "Infected files emitted";
     emit sendResultToQml(theInfectedFile);
}

void MainController::stopThread(){

}

QString MainController::getFiles(){
    return theInfectedFile;
}

void MainController::setFiles(QString f){

}


#include "maincontroller.h"

MainController::MainController(QWidget *parent) :QWidget(parent){
    fileCount = 0;
}

//Function to scan a single file for viruses/malware on a separate thread.
void MainController::singleFileScan(){
    singleFileScanThread = new SingleScan();
    connect(singleFileScanThread, &SingleScan::scanStart, this, &MainController::handleScanStart);
    connect(singleFileScanThread, &SingleScan::scanComplete, this, &MainController::relayScanDoneSir);
    connect(singleFileScanThread, &SingleScan::infectedFiles, this, &MainController::displayInfectedFiles);
    connect(singleFileScanThread, &SingleScan::scannedFileNumS, this, &MainController::handleScanOpsInfo);
    connect(singleFileScanThread, &SingleScan::finished, singleFileScanThread, &QObject::deleteLater);
    singleFileScanThread->start();
}

//TODO Set up the scan start message for directory scan to notify qml.
void MainController::scanDirectory(){
    directoryScan = new DirectoryScan();
    connect(directoryScan, &DirectoryScan::scanStartx, this, &MainController::handleScanStart);
    connect(directoryScan, &DirectoryScan::scanCompletex, this, &MainController::relayScanDoneDir);
    connect(directoryScan, &DirectoryScan::infectedFilesx, this, &MainController::displayInfectedFiles);
    connect(directoryScan, &DirectoryScan::scannedFileNumD, this, &MainController::handleScanOpsInfo);
    connect(directoryScan, &DirectoryScan::finished, directoryScan, &QObject::deleteLater);
    //directoryScan->stopThread = false;
    directoryScan->start();
}

//Function to download signatures
void MainController::downloadSignatures(){
    //qDebug() <<"Attempting to download signatures......";
    updateThread = new QThread();
    updateController = new UpdateController();
    connect(updateController, &UpdateController::currentProgress, this, &MainController::updateProgressBar);
    //connect(updateController, &UpdateController::currentProgressFiles, this, &MainController::updateProgBarFileOps);
    //connect(updateController, &UpdateController::state, this, &MainController::updateStatus);
    //updateController->moveToThread(updateThread);
    connect(updateThread, &QThread::finished, updateController, &QObject::deleteLater);
    updateThread->start();
}

//Function to send progress bar download values to QML GUI
void MainController::updateProgressBar(int bytesRead, int totalBytes ){
    emit pBarActivity("Downloading...");
    totBytesVal = totalBytes;
    qDebug() << "The totalBytes value is: " << totalBytes;
    //qDebug() << totBytesVal;
    currentValue = bytesRead;
    //qDebug() << currentValue;
    emit totalBytesToQml(totalBytes);
    emit txtBytesReadToQml(txtBytestoQML);
    emit bytesReadToQml(bytesRead);
}

//Set message on screen based on operation
void MainController::handleScanStart(){
    //qDebug() << "Back in main control hndle scan start";
    emit sScanStarted();
}

void MainController::handleScanOpsInfo(QString fileNumData){
    //qDebug() << fileNumData;
    //qDebug() << "In handleScanOPs in Main.......... file count";
    //QThread::msleep(500);
    dirScanedFileCount = fileNumData;
    emit dNumFilesScanned(dirScanedFileCount);

}

//Function to relay the scan directory done message to the QML GUI
void MainController::relayScanDoneDir(){
    emit dScanDone();
}

//Function to relay the scan single directory done message to the QML GUI
void MainController::relayScanDoneSir(){
    emit sScanDone();
}

//Receive data from the thread and send it the the qml GUI
void MainController::displayInfectedFiles(QString files){
    //QThread::msleep(500);
     qDebug() << "In display infected files";
     fileCount++;
     qDebug() << fileCount;
     theInfectedFile = files;
     qDebug() << "Infected file info is: " << theInfectedFile;
     //Send the data to the GUI
     if(theInfectedFile == "0"){
         emit sInfectedFiles("No threats found.......");
     }else{
         emit sInfectedFiles(theInfectedFile);
     }
}

//Function to check for malicious URLs using the Google Safe Browsing API.
//On windows, openssl must be added from qtmaintenance tool. https://stackoverflow.com/questions/53805704/tls-initialization-failed-on-get-request
void MainController::checkUrl(QString userSuppliedUrl){

    urlToCheck = userSuppliedUrl;
    qDebug()<<"In check checkUrl() function.........";


    //Basically get the URL from user and put it in the JSON text to send to google. The JSON data must be converted to a byte array to send in the post rquest.
    //TO try: Make one liner JSON and replace text with the URL and convert to a byte array instead of saving to file first.
    //Set the file path for the text file containing the JSON data
    //This JSON file contains the google test site urls
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

    qDebug() << "The Google safe browse string URL containing your API key is: " << googleUrl;
    QNetworkAccessManager *mgr = new QNetworkAccessManager(this);

    //This is the google safe browse URL that includes your API key to send the test site info to.
    QUrl url = QUrl::fromUserInput(googleUrl);

    QNetworkRequest request(url);
    qDebug() << "The URL test site is: " << url.toString();

    if(url.isEmpty() == true){
        qDebug() << "The URL is empty..............";
    }

    //Set header for JSON as specified by Google.
    //POST https://safebrowsing.googleapis.com/v4/threatMatches:find?key=API_KEY HTTP/1.1
    //Content-Type: application/json
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    //request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));

    //This (GET request) can be used to test if there's a response from Google without using a JSON array.
    //QNetworkReply *reply = mgr->get(request);

    //The POST request requires two arguments. The first argument is a QUrl. The second argument is a QByteArray.
    //Google provides this as an example: POST https://safebrowsing.googleapis.com/v4/threatMatches:find?key=API_KEY HTTP/1.1 - is it clear what to include in our string? No. See below.
    //The string to provide to QUrl is "https://safebrowsing.googleapis.com/v4/threatMatches:find?key=API_KEY" Leave the HTTP/1.1 off and make sure to replace the "API_KEY" text with an API key
    QNetworkReply *reply = mgr->post(request, jsonByteArray);
    QObject::connect(reply, &QNetworkReply::finished, [=](){
        if(reply->error() == QNetworkReply::NoError){
            //QByteArray byteArrayGoogleReplyContents = reply->readAll();
            QString contents = QString::fromUtf8(reply->readAll());
            googleReplyData = contents.trimmed();
            QByteArray byteArrayGoogleReplyContents = contents.toLocal8Bit().trimmed();

            QJsonDocument json_doc = QJsonDocument::fromJson(byteArrayGoogleReplyContents);

            //Start with an object
            QJsonObject jsonObject = json_doc.object();

            //Next theres a matches array
            QJsonArray matchArray = jsonObject.value("matches").toArray();

            //Get the first value in the array and convert to object
            QJsonObject first = matchArray[0].toObject();

            //Read the values of the object
            QString threatType = first.value("threatType").toString();
            QString platformType  = first.value("platformType").toString();
            qDebug() << "The threaType is: " << threatType;
            qDebug() << "The platformType is: " << platformType;

            emit urlResultsToQml(" THREAT TYPE: " + threatType);
            emit urlResultsToQml(" PLATFORM TYPE: " + platformType);

            qDebug() << "Reply from Google is: " << contents;
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

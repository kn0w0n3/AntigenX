#include "directoryscan.h"

DirectoryScan::DirectoryScan(QThread *parent) : QThread(parent){
   lineNumberOfVirusFile = 0;
   numberOfHashesTested = 0;
   lineNumberOfFilePaths = 0;
   expectedNumFilesToScan = 0;
   infectedFiles = false;
   getRequiredFiles();
}

//compare each hash to the viruslist hashes. Report matches.
void DirectoryScan::run(){
    qDebug() << "In run() funtion directory scan........";
    emit scanStartx();
    foreach (const QString &hash, hashList){
        numberOfHashesTested++;
        //qDebug() << "Number of hashes tested...... " << numberOfHashesTested;
        emit scannedFileNumD(QString::number(numberOfHashesTested));
        msleep(1);
        foreach (const QString &str, virusList){
            //msleep(1);
            lineNumberOfVirusFile++;
            if(hash == str){
                foreach(const QString &p, pathForHashList){
                    lineNumberOfFilePaths++;
                    if(lineNumberOfFilePaths == lineNumberOfVirusFile){
                        emit infectedFilesx(p);
                        lineNumberOfFilePaths = 0;
                        exitVirusListLoop = true;
                        break;
                    }
                }
            }
            if(exitVirusListLoop == true){
                lineNumberOfVirusFile = 0;
                exitVirusListLoop = false;
                break;
            }
        }
    }
    if(infectedFiles == false){
        emit infectedFilesx("0");
    }
    //qDebug() << "emitting scan complete here";
    emit scanCompletex();
}

/*Prompt user to select directory. Hash all files and add each hash to the list.
 *A list for the original file names and paths are stored at the same time.
 *We keep track of which line number the file comparison is on.
 *If there is a match, we look up the filename and path by line number.
*/
void DirectoryScan::getRequiredFiles(){

    emit scanStartx();
    msleep(1);
    QString dir = QFileDialog::getExistingDirectory(Q_NULLPTR, tr("Select Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    msleep(1);//This keeps th edelect directory dialog from hanging open
    list << dir;

    if(dir.isEmpty()){
        return;
    }
    foreach (QString element, list){
        QDirIterator directory(element, QDirIterator::Subdirectories);

        while (directory.hasNext()){

                QString path = directory.filePath();
                pathForHashList << path;

                QFileInfo fi(element);
                QString fn = fi.fileName();
                filenameOfHash << fn;

                QFile inputFileFromDirs(path);
                if (inputFileFromDirs.open(QIODevice::ReadOnly)){
                    QByteArray fileData = inputFileFromDirs.readAll();
                    hashDataMd5 = QCryptographicHash::hash(fileData, QCryptographicHash::Md5).toHex();                    
                    //expectedNumFilesToScan++;
                    //QString tempXC = QString::number(expectedNumFilesToScan);
                    //qDebug() << "File num: " << tempXC << "| The path is: " << path;
                    hashList << hashDataMd5;  
                }
            directory.next();
        }
    }

    QFile inputFile("/home/voldem0rt/Desktop/AntigenX-main/viruslist.txt");
    if (inputFile.open(QIODevice::ReadOnly)){
        QTextStream in(&inputFile);
        while (!in.atEnd()){
            QString line = in.readLine();
            virusList << line;
        }
        inputFile.close();
    }
}

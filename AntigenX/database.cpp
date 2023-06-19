#include "database.h"

Database::Database(QObject *parent) : QObject(parent){

    //mainWinDB = QSqlDatabase::addDatabase("QSQLITE", "conn1");

mainWinDB.setDatabaseName("C:/Users/Voldem0rt/Documents/Qt_Projects/AntigenX/db/program_info.db");
    //qDebug() << "The available drivers are : " << mainWinDB.drivers();

    //For now, do an initial check to see if the connections are working.
    //if(mainWinDB.open()){
        //qDebug() << "Constructor:  mainWinDB Connected!!!......";
    //}
}

//Pull the info from the main win gui
void Database::getMainWinGuiInfo(QString mwStatusF, QString mwlastFullScanF, QString mwLastSmartScanF, QString mwLastSingleScanF, QString mwLastUpdateF, QString mwThreatsFoundF, QString mwCurrentThreatsF){
    /*
    mwStatus =  mwStatusF;
    mwlastFullScan = mwlastFullScanF;
    mwLastSmartScan = mwLastSmartScanF;
    mwLastSingleScan = mwLastSingleScanF;
    mwLastUpdate = mwLastUpdateF;
    mwThreatsFound = mwThreatsFoundF;
    mwCurrentThreats = mwCurrentThreatsF;
    */
}

//Get Main Window DB info
void Database::getMainWinDBInfo(){
    //billDB = QSqlDatabase::addDatabase("QSQLITE", "conn2-BillInfo");
    //billDB.setDatabaseName("C:/Users/Documents/Qt_Projects/Bill-Bot/database/bill_info.db");
    //QSqlDatabase mainWinDB =  QSqlDatabase::addDatabase("QSQLITE","conn1-MainWinInfo");


    if(!mainWinDB.open()){
        qDebug() << "Function: getMainWinDBInfo() Database Not Connected......";
    }



    qDebug() << "Pulling from database to populate Main Win info............";
    //qDebug() << "SQL error: "<< igetMainWinDBInfo.lastError().text() << endl;
    QSqlQuery x(QSqlDatabase::database("conn1-MainWinInfo"));
    x.prepare("SELECT mw-status, mw-last-full-scan, mw-last-smart-scan, mw-last-single-scan, mw-last-update, mw-threats-found, mw-current-threats FROM main-win-info WHERE id > 0");

   if (!x.exec()){
        qDebug() << "SQL error: "<< x.lastError().text() << Qt::endl;
    }
    qDebug() << "SQL error: "<< x.lastError().text() << Qt::endl;
    while(x.next()){
    qDebug() << "SQL error: "<< x.lastError().text() << Qt::endl;
        qDebug() << "In DB function................";
        mwStatus = x.value(0).toString();
        qDebug() << "mwStatus: " + mwStatus.trimmed();
        emit dbmwStatus2Qml(mwStatus.trimmed());
       }
}

void Database::setMainWinInfo2Db(){
    QSqlDatabase mainWinDB =  QSqlDatabase::addDatabase("QSQLITE");
    mainWinDB.setDatabaseName("C:/Users/Voldem0rt/Documents/Qt_Projects/AntigenX/db/program_info.db");
    if(!mainWinDB.open()){
        qDebug() << "Database Not Connected..........";
    }
    else{
        QSqlQuery query(QSqlDatabase::database("conn1-MainWinInfo"));
        query.exec("INSERT INTO main-win-info (mw-status, mw-last-full-scan, mw-last-smart-scan, mw-last-single-scan, mw-last-update, mw-threats-found, mw-current-threats)" "VALUES (?, ?, ?, ?, ?, ?, ?)");
        qDebug() << "Inserting info to database.......";
        query.bindValue(0, mwStatus);
        query.bindValue(1, mwlastFullScan);
        query.bindValue(2, mwLastSmartScan);
        query.bindValue(3, mwLastSingleScan);
        query.bindValue(4, mwLastUpdate);
        query.bindValue(5, mwThreatsFound);
        query.bindValue(6, mwCurrentThreats);
        query.exec();
    }
}


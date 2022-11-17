#include "database.h"

Database::Database(QObject *parent) : QObject(parent){

    //mainWinDB = QSqlDatabase::addDatabase("QSQLITE", "conn1");

mainWinDB.setDatabaseName("/home/voldem0rt/Desktop/AntigenX-main/db/program_info.db");
    //qDebug() << "The available drivers are : " << mainWinDB.drivers();

    //For now, do an initial check to see if the connections are working.
    //if(mainWinDB.open()){
        //qDebug() << "Constructor:  mainWinDB Connected!!!......";
    //}

    /*
    //Multiple connections were required to work with the different tables simultaneously.
    //Format for the query: QSqlQuery query(QSqlDatabase::database("conn2-BillInfo"));
    sEmailDB = QSqlDatabase::addDatabase("QSQLITE", "conn1_EmailInfo");
    sEmailDB.setDatabaseName("C:/Users/Documents/Qt_Projects/Bill-Bot/database/bill_info.db");

    billDB = QSqlDatabase::addDatabase("QSQLITE", "conn2-BillInfo");
    billDB.setDatabaseName("C:/Users/Documents/Qt_Projects/Bill-Bot/database/bill_info.db");

    populateDB = QSqlDatabase::addDatabase("QSQLITE", "conn3-popCReminders_");
    populateDB.setDatabaseName("C:/Users/Documents/Qt_Projects/Bill-Bot/database/bill_info.db");

    popEmailDB = QSqlDatabase::addDatabase("QSQLITE", "conn4-popSEmailBox");
    popEmailDB.setDatabaseName("C:/Users/Documents/Qt_Projects/Bill-Bot/database/bill_info.db");

    fEmailDB = QSqlDatabase::addDatabase("QSQLITE", "conn5-fEmailBox");
    fEmailDB.setDatabaseName("C:/Users/Documents/Qt_Projects/Bill-Bot/database/bill_info.db");



    //For now, do an initial check to see if the connections are working.
    if(!sEmailDB.open()){
        qDebug() << "Constructor:  sEmailDB Not Connected......";
    }
    else{
        qDebug() << "Constructor:  sEmailDB is Connected.......";
    }
    if(!billDB.open()){
        qDebug() << "Constructor: billDB Not Connected......";
    }
    else{
        qDebug() << "Constructor: billDB is Connected.......";
    }
    if(!populateDB.open()){
        qDebug() << "Constructor: populateDB Not Connected......";
    }
    else{
        qDebug() << "Constructor: populateDB is Connected.......";
    }
    if(!popEmailDB.open()){
        qDebug() << "Constructor: popEmailDB Not Connected......";
    }
    else{
        qDebug() << "Constructor: popEmailDB is Connected.......";
    }
    counter = 0;
    //getFirstDatabaseEntries();
    */
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
        qDebug() << "SQL error: "<< x.lastError().text() << endl;
    }
qDebug() << "SQL error: "<< x.lastError().text() << endl;
    while(x.next()){
qDebug() << "SQL error: "<< x.lastError().text() << endl;
        qDebug() << "In DB function................";
        mwStatus = x.value(0).toString();
        qDebug() << "mwStatus: " + mwStatus.trimmed();
        emit dbmwStatus2Qml(mwStatus.trimmed());
       }
/*
        mwlastFullScan = igetMainWinDBInfo.value(1).toString();
        qDebug() << "mwlastFullScan " + mwlastFullScan.trimmed();
        emit dbmwlastFullScan2Qml(mwlastFullScan.trimmed());

        mwLastSmartScan = igetMainWinDBInfo.value(2).toString();
        qDebug() << "mwLastSmartScan: " + mwLastSmartScan.trimmed();
        emit dbmwLastSmartScan2Qml(mwLastSmartScan.trimmed());

        mwLastSingleScan = igetMainWinDBInfo.value(3).toString();
        qDebug() << "mwLastSingleScan: " + mwLastSingleScan.trimmed();
        emit dbmwLastSingleScan2Qml(mwLastSingleScan.trimmed());

        mwLastUpdate = igetMainWinDBInfo.value(4).toString();
        qDebug() << "mwLastUpdate: " + mwLastUpdate.trimmed();
        emit dbmwLastUpdate2Qml(mwLastUpdate.trimmed());

        mwThreatsFound = igetMainWinDBInfo.value(5).toString();
        qDebug() << "mwThreatsFound: " + mwThreatsFound.trimmed();
        emit dbmwThreatsFound2Qml(mwThreatsFound.trimmed());

        mwCurrentThreats = igetMainWinDBInfo.value(6).toString();
        qDebug() << "mwCurrentThreats: " + mwCurrentThreats.trimmed();
        emit dbmwCurrentThreats2Qml(mwCurrentThreats.trimmed());
*/
    //}
    //emit fBillToQmlDone("Done");
}

void Database::setMainWinInfo2Db(){
    QSqlDatabase mainWinDB =  QSqlDatabase::addDatabase("QSQLITE");
    mainWinDB.setDatabaseName("/home/voldem0rt/Desktop/AntigenX-main/db/program_info.db");
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
/*
//Receive and store bill information from the QML form
void Database::receiveBillInfoFromQML(QString bName, QString dDate, QString dtNotify, QString aDue){
    billName = bName;
    dueDate = dDate;
    dateToNotify = dtNotify;
    amountDue = aDue;
    insertBillDbInfo();
}

//Insert sender email info to the database.
void Database::insertEmailToDb(){
    if(!sEmailDB.open()){
        qDebug() << "Function: Local Email Database Not Connected......";
    }
    else{
        qDebug() << "Function: Local Email Info Database is Connected.......";
        QSqlQuery insertEmailQuery(QSqlDatabase::database("conn1_EmailInfo"));
        insertEmailQuery.exec("INSERT INTO sender_email_info (username, password, server, port_number) " "VALUES (?, ?, ?, ?)");

        qDebug() << "Trying to insert email info to database.......";
        insertEmailQuery.bindValue(0, iUsername);
        insertEmailQuery.bindValue(1, iPassword);
        insertEmailQuery.bindValue(2, iServer);
        insertEmailQuery.bindValue(3, iPortNumber);
        insertEmailQuery.exec();
    }
}

//Insert reminder form info into the database.
void Database::insertBillDbInfo(){
    if(!billDB.open()){
        qDebug() << "Database Not Connected..........";
    }
    else{
        QSqlQuery query(QSqlDatabase::database("conn2-BillInfo"));
        query.exec("INSERT INTO bill_info_table (db_bill_name, db_due_date, db_date_to_notify, db_amount_due)" "VALUES (?, ?, ?, ?)");
        qDebug() << "Inserting info to database.......";
        query.bindValue(0, billName);
        query.bindValue(1, dueDate);
        query.bindValue(2, dateToNotify);
        query.bindValue(3, amountDue);
        query.exec();
    }
}

//Get the current saved reminders from the database and populate the main menu QML form.
void Database::populateCurrentReminders(){
    QSqlQuery popCReminders(QSqlDatabase::database("conn3-popCReminders_"));
    popCReminders.exec("SELECT db_bill_name, db_due_date, db_date_to_notify, db_amount_due FROM bill_info_table WHERE id > 0");
    qDebug() << "Pulling from database to populate current reminders............";
    while(popCReminders.next()){
        pBillName = popCReminders.value(0).toString();
        qDebug() << "billName: " + pBillName.trimmed();
        emit dbBillNameToQml(pBillName.trimmed() + "    |    ");

        pDueDate = popCReminders.value(1).toString();
        qDebug() << "dueDate: " + pDueDate.trimmed();
        emit dbDueDateToQml(pDueDate.trimmed() + "    |    ");

        pDateToNotify = popCReminders.value(2).toString();
        qDebug() << "Notify Date: " + pDateToNotify.trimmed();
        emit dbNotifyDateToQml(pDateToNotify.trimmed() + "    |    ");

        pAmountDue = popCReminders.value(3).toString();
        qDebug() << "Amount Due: " + pAmountDue.trimmed();
        emit dbAmountDueToQml(pAmountDue.trimmed());
    }
    emit fBillToQmlDone("Done");
}

void Database::populateSvdEmailBox(){

    //QSqlQuery popSEmailQuery(QSqlDatabase::database("conn4-popSEmailBox"));
    //popSEmailQuery.exec("SELECT username FROM sender_email_info WHERE id > 0");
    //qDebug() << "Pulling from database to populate email box............";
    //while(popSEmailQuery.next()){
        //counter++;
        //qDebug() << counter;
        //_emailAddress = popSEmailQuery.value(0).toString();
        //qDebug() << _emailAddress;
        //emit dbSvdEmailToQml(_emailAddress);
    //}

}
*/

/*
void Database::getFirstDatabaseEntries(){
    QSqlQuery fEmailQuery(QSqlDatabase::database("conn5-fEmailBox"));
    fEmailQuery.exec("SELECT username FROM sender_email_info WHERE id > 0");
    qDebug() << "Pulling from database to pget first entries............";
    while(fEmailQuery.next()){
        //if(counterTwo == 1){
            //qDebug() << "Done.. first emails.. emitted signal";
            //emit fEmailToQmlDone("done");
        //}
        //if(counterTwo > 1){
        //Still send the others for now. I don't think this funcction is needed now. Just delete the first duplicate entry
        counterTwo++;
        qDebug() << counterTwo;
        fEmailInDb = fEmailQuery.value(0).toString();
        qDebug() << "Femail: " + fEmailInDb;
        emit fEmailToQml(fEmailInDb);
       // }
        //counterTwo++;

    }
    emit fEmailToQmlDone("done");
}

//Receive and store data from the QML settings form. This is a sending email address that the user wants to save. Only Gmail is working for now.
void Database::receiveEmailInfoFromQML(QString uName, QString pWord){
    if(uName.isEmpty()){
        return;
        qDebug() << "Empty string in receiveEmailInfoToSave() function";
    }
    iUsername = uName;
    iPassword = pWord;
    insertEmailToDb();
}
*/

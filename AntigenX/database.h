#ifndef DATABASE_H
#define DATABASE_H

/*
Author: Jonathan Baird
Date: 16NOV2022
Purpose: Database for storing signatures, logs and other data
Contact: tr14rc3@gmail.com
*/

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QtSql>
#include <QSqlDatabase>
#include <QDebug>

class Database: public QObject{
    Q_OBJECT

public:
    explicit Database(QObject *parent = nullptr);

signals:
    void dbmwStatus2Qml(QString dbmwStatus2Qml_);
    void dbmwlastFullScan2Qml(QString dbmwlastFullScan2Qml_);
    void dbmwLastSmartScan2Qml(QString dbmwLastSmartScan2Qml_);
    void dbmwLastSingleScan2Qml(QString dbmwLastSingleScan2Qml_);
    void dbmwLastUpdate2Qml(QString dbmwLastUpdate2Qml_);
    void dbmwThreatsFound2Qml(QString dbmwThreatsFound2Qml_);
    void dbmwCurrentThreats2Qml(QString dbmwCurrentThreats2Qml_);

public slots:
    void getMainWinGuiInfo(QString mwStatusF, QString mwlastFullScanF, QString mwLastSmartScanF, QString mwLastSingleScanF, QString mwLastUpdateF, QString mwThreatsFoundF, QString mwCurrentThreatsF);
    void getMainWinDBInfo();
    void setMainWinInfo2Db();

private:
    //Variables to hold the incoming data from the main window table.
    QString mwStatus;
    QString mwlastFullScan;
    QString mwLastSmartScan;
    QString mwLastSingleScan;
    QString mwLastUpdate;
    QString mwThreatsFound;
    QString mwCurrentThreats;

    //Connections for working with different tables simultaneously.
    QSqlDatabase mainWinDB =  QSqlDatabase::addDatabase("QSQLITE","conn1-MainWinInfo");
    //Linux Path
    //QString mainWInDbPath = "/home/voldem0rt/Desktop/AntigenX-main/db/program_info.db";
    //Windows path
    QString mainWInDbPath = "C:/Users/Voldem0rt/Documents/Qt_Projects/AntigenX/db/program_info.db";

};

#endif // DATABASE_H

#ifndef DATABASE_H
#define DATABASE_H
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
    /*
    void sendMsgConfirmToQml2(QString);
    void dbBillNameToQml(QString billName_);
    void dbDueDateToQml(QString dueDate_);
    void dbNotifyDateToQml(QString notifyDate_);
    void dbAmountDueToQml(QString amountDue_);
    void dbSvdEmailToQml(QString savedEmail_);
    void fEmailToQml(QString fEmail_);
    void fEmailToQmlDone(QString fEmailDone_);
    void fBillToQmlDone(QString fBilllDone_);
    */
public slots:
    void getMainWinInfo(QString mwStatusF, QString mwlastFullScanF, QString mwLastSmartScanF, QString mwLastSingleScanF, QString mwLastUpdateF, QString mwThreatsFoundF, QString mwCurrentThreatsF);
    void dbInsertMainWIn();
    /*
    void receiveBillInfoFromQML(QString bName,QString dDate, QString dtNotify, QString aDue);
    void insertBillDbInfo();
    void receiveEmailInfoFromQML(QString uName, QString pWord);
    void insertEmailToDb();
    void populateCurrentReminders();
    void populateSvdEmailBox();
    void getFirstDatabaseEntries();
    */
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
    QSqlDatabase mainWinDB;

    /*
    //Connections for working with different tables simultaneously.
    QSqlDatabase billDB;
    QSqlDatabase sEmailDB;
    QSqlDatabase rEmailDB;
    QSqlDatabase populateDB;
    QSqlDatabase popEmailDB;
    QSqlDatabase fEmailDB;

    //Variables to hold the incoming data from the reminder form.
    QString billName;
    QString dueDate;
    QString dateToNotify;
    QString amountDue;

    //Variables to hold the incoming data from the database.
    QString pBillName;
    QString pDueDate;
    QString pDateToNotify;
    QString pAmountDue;

    //Variables to hold the incoming data for the email address to save to the database.
    QString iUsername;
    QString iPassword;
    QString iServer = "smtp.gmail.com";
    QString iPortNumber = "465";


    //Variable to hold the incoming saved sender email addresses to poulate the saved email box
    QString _emailAddress;

    int counter = 0;
    int counterTwo = 0;

    QString fEmailInDb;
    */
};

#endif // DATABASE_H

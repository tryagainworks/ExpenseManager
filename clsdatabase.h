#ifndef CLSDATABASE_H
#define CLSDATABASE_H

#include <QMainWindow>
#include <QMessageBox>
#include <QKeyEvent>
#include <QScroller>
#include <QSysInfo>
#include <QListWidget>
#include <QtSql/QtSql>
#include <QSqlQuery>
#include "clsglobal.h"

class clsDataBase
{
public:
    clsDataBase();
    void fnClasInti();
    void fnDBDisconnect();
private:
    void fnConnectDbForNonAndroid();
    void fnConnectDbForAndroid();
    QString strDatabaseName,strDbStorePath;
};

#endif // CLSDATABASE_H

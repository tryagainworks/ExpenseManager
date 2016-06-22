#include "clsdatabase.h"

clsDataBase::clsDataBase()
{
    fnClasInti();
}

void clsDataBase::fnDBDisconnect()
{
    if(clsGlobal::objDbCon.isOpen())
    {
        clsGlobal::objDbCon.close();
        clsGlobal::objRs.finish();
    }

    QDir ddir(strDbStorePath);
    if(ddir.exists())
    {
        QFile sfile(strDbStorePath + (QSysInfo::productType()=="android" ? "/" : "") + strDatabaseName);
        QString strFile = strDbStorePath + (QSysInfo::productType()=="android" ? "/" : "") + strDatabaseName + "_" + QDateTime::currentDateTime().toString("ddMMMyyyy_hhmmssAP") + ".backup";
        sfile.copy(strFile);
        QFile::setPermissions(strFile,QFile::WriteOwner | QFile::ReadOwner);
    }
}

void clsDataBase::fnClasInti()
{
    if(QSysInfo::productType()=="android")
    {
        strDatabaseName = "emdb";
        strDbStorePath="/sdcard/ExpenseManagerGitHub";
        fnConnectDbForAndroid();
    }
    else
    {
        strDatabaseName = "emdb";
        //strDbStorePath="D:\\QTApps\\ExpenseManagerGitHub\\";
        strDbStorePath="/home/linuxmintuser02/MyApps/QTApps_Windows/GitHub/ExpenseManagerGitHub/";
        fnConnectDbForNonAndroid();
    }
}

void clsDataBase::fnConnectDbForAndroid()
{
    clsGlobal::objDbCon = QSqlDatabase::addDatabase("QSQLITE");
    QFile sfile("assets:\\" + strDatabaseName);

    QDir ddir(strDbStorePath);
    if(!ddir.exists())
    {
        ddir.mkdir(strDbStorePath);
    }
    QFile dfile(strDbStorePath + "/" + strDatabaseName);
    if (!dfile.exists())
    {
        sfile.copy(strDbStorePath + "/" + strDatabaseName);
        QFile::setPermissions(strDbStorePath + "/" + strDatabaseName,QFile::WriteOwner | QFile::ReadOwner);
    }
    clsGlobal::objDbCon.setDatabaseName(strDbStorePath + "/" + strDatabaseName);
    if (!clsGlobal::objDbCon.open())
    {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "This example needs SQLite support. Please read "
                                       "the Qt SQL driver documentation for information how "
                                       "to build it.\n\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
        return;
    }
    else
    {
        clsGlobal::objRs = {QSqlQuery(clsGlobal::objDbCon)};
        //qd.close();
        //QMessageBox::information(0, qApp->tr("Database Opened Successfully"),qApp->tr("Database Opened Successfully"),QMessageBox::Ok);
    }
}

void clsDataBase::fnConnectDbForNonAndroid()
{
    clsGlobal::objDbCon = QSqlDatabase::addDatabase("QSQLITE");
    clsGlobal::objDbCon.setDatabaseName(strDbStorePath + strDatabaseName);
    if (!clsGlobal::objDbCon.open())
    {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection.\n"
                                       "This example needs SQLite support. Please read "
                                       "the Qt SQL driver documentation for information how "
                                       "to build it.\n\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
        return;
    }
    else
    {
        clsGlobal::objRs = {QSqlQuery(clsGlobal::objDbCon)};
        //qd.close();
        //QMessageBox::information(0, qApp->tr("Database Opened Successfully"),qApp->tr("Database Opened Successfully"),QMessageBox::Ok);
    }
}

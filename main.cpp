#include <QApplication>
#include "clsglobal.h"
#include "clsdatabase.h"
#include <QSysInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/new/prefix1/All.png"));
    QString strStyleSheet="";
    if(QSysInfo::productType()=="android")
    {
        strStyleSheet.append("* {font: 20pt \"Comic Sans MS\";}");
    }
    strStyleSheet.append("QPushButton {font : bold; color: Black;border-image: url(:/new/prefix1/button.png) 3 10 3 10;border-top: 3px transparent;border-bottom: 3px transparent;border-right: 10px transparent;border-left: 10px transparent;}");
    strStyleSheet.append("QPushButton:disabled {font : bold; color: darkgray;border-image: url(:/new/prefix1/button_disable.png) 3 10 3 10;border-top: 3px transparent;border-bottom: 3px transparent;border-right: 10px transparent;border-left: 10px transparent;}");

    strStyleSheet.append("QTableWidget {background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(198, 198, 148, 255), stop:1 rgba(255, 255, 255, 255));selection-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(255, 222, 182, 255), stop:0.55 rgba(235, 148, 61, 255), stop:0.98 rgba(0, 0, 0, 255), stop:1 rgba(0, 0, 0, 0));}");

    strStyleSheet.append("QLineEdit {border:2px solid gray;border-radius: 10px; padding :0 8px;background-color: rgb(215, 255, 208); selection-background-color:darkgray;}");
    strStyleSheet.append("QComboBox {border:2px solid gray;border-radius: 10px; padding :0 8px;background-color: rgb(210, 164, 255); selection-background-color:darkgray}");
    strStyleSheet.append("QDateEdit {border:2px solid gray;border-radius: 10px; padding :0 8px;background-color: rgb(255, 178, 235); selection-background-color:darkgray}");
    strStyleSheet.append("QListWidget {border:2px solid gray;border-radius: 10px; padding :0 8px;background-color: rgb(255, 236, 178); selection-background-color:darkgray}");

    qApp->setStyleSheet(strStyleSheet);


    clsDataBase objDB;
    objDB.fnClasInti();
    clsGlobal::fnHandleWindows(GUI::STARTUP,GUI_INVOKE_PURPOSE::NOTHING);
    //clsGlobal::mWnd = new frmStartUpNew();
    //clsGlobal::mWnd->show();

    return a.exec();
}

#include "frmsettings.h"
#include "ui_frmsettings.h"

frmsettings::frmsettings(QWidget *parent, GUI_INVOKE_PURPOSE intPurpose, QVector<QString> VecStr) :
    QMainWindow(parent),
    ui(new Ui::frmsettings)
{
    ui->setupUi(this);
    QScroller::grabGesture(ui->scrlArea, QScroller::TouchGesture);
    show();
}

frmsettings::~frmsettings()
{
    delete ui;
}

void frmsettings::keyReleaseEvent(QKeyEvent *QK)
{
    bool blnEventHappened=false;
    if((QK->key() == Qt::Key_Back) && QSysInfo::productType()=="android")
    {
        blnEventHappened=true;
    }
    else if(QK->key() == Qt::Key_Escape && QSysInfo::productType()!="android")
    {
        blnEventHappened=true;
    }

    if(blnEventHappened)
    {
        clsGlobal::fnHandleWindows(GUI::STARTUP,GUI_INVOKE_PURPOSE::NOTHING);
    }
}

void frmsettings::fnInvokeFor(GUI_INVOKE_PURPOSE *intPurpose, QVector<QString> *strLst)
{

}

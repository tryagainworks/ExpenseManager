#include "frmstartupnew.h"
#include "ui_frmstartupnew.h"

frmStartUpNew::frmStartUpNew(QWidget *parent, GUI_INVOKE_PURPOSE intPurpose, QVector<QString> VecStr) :
    QMainWindow(parent),
    ui(new Ui::frmStartUpNew)
{
    ui->setupUi(this);
    /*smooth scroll*/
    QScroller::grabGesture(ui->scrlArea, QScroller::TouchGesture);
    show();
    fnInvokeFor(&intPurpose, &VecStr);
}

frmStartUpNew::~frmStartUpNew()
{
    delete ui;
}

void frmStartUpNew::fnInvokeFor(GUI_INVOKE_PURPOSE *intPurpose, QVector<QString> *strLst)
{

}

void frmStartUpNew::on_cmdEntry_2_clicked()
{
    //closing this windows and showing the required window
    clsGlobal::fnHandleWindows(GUI::TRAN,GUI_INVOKE_PURPOSE::NOTHING);
}

void frmStartUpNew::on_cmdSummaryReport_2_clicked()
{
    //closing this windows and showing the required window
    QVector<QString> strLst;
    strLst.push_back("Summary Report");
    clsGlobal::fnHandleWindows(GUI::REPT,GUI_INVOKE_PURPOSE::NOTHING,strLst);
}

void frmStartUpNew::on_cmdDetailReport_2_clicked()
{
    QVector<QString> strLst;
    strLst.push_back("Detail Report");

    clsGlobal::fnHandleWindows(GUI::REPT,GUI_INVOKE_PURPOSE::NOTHING,strLst);
}

void frmStartUpNew::on_cmdMasterEntry_clicked()
{
    clsGlobal::fnHandleWindows(GUI::MAST,GUI_INVOKE_PURPOSE::NOTHING);
}

void frmStartUpNew::on_cmdExit_clicked()
{
    clsGlobal::fnHandleWindows(GUI::NOTHING,GUI_INVOKE_PURPOSE::NOTHING);
}

void frmStartUpNew::keyReleaseEvent(QKeyEvent *QK)
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
        clsGlobal::fnHandleWindows(GUI::NOTHING,GUI_INVOKE_PURPOSE::NOTHING);
    }
}

void frmStartUpNew::on_cmdSettings_clicked()
{
    clsGlobal::fnHandleWindows(GUI::SETTINGS,GUI_INVOKE_PURPOSE::NOTHING);
}

void frmStartUpNew::on_cmdLogout_clicked()
{
    clsGlobal::fnHandleWindows(GUI::LOGIN,GUI_INVOKE_PURPOSE::NOTHING);
}

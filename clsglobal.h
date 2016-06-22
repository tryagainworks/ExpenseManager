#ifndef CLSGLOBAL_H
#define CLSGLOBAL_H

#include <QMainWindow>
#include "frmstartupnew.h"
#include "frmsavemaster.h"
#include "frmsavetrannew.h"
#include "frmreport.h"
#include "frmlogin.h"
#include "frmsettings.h"
#include "clsdatabase.h"

enum class GUI : int
{
    NOTHING = 1,LOGIN=2,STARTUP=3, MAST=4, TRAN=5, REPT=6, SETTINGS=7
};

enum class GUI_INVOKE_PURPOSE : int
{
    NOTHING=1,TODAY_ENTRY=2, TRAN_EDIT=3
};

class clsFilterData
{
public:
    int intMastTblId, intTranTblId, intItemTypeID;
    QString strItemName, strItemDesc, strAnyDescOfTran;

    clsFilterData(int _intMastTblId=0, int _intTranTblId=0, QString _strItemName="", QString _strItemDesc="", int _intItemType=0, QString _strAnyDescOfTran="")
    {
        intMastTblId = _intMastTblId;
        intTranTblId = _intTranTblId;
        strItemName = _strItemName;
        strItemDesc = _strItemDesc;
        intItemTypeID  = _intItemType;
        strAnyDescOfTran = _strAnyDescOfTran;
    }
};

class clsGlobal
{
public:
    clsGlobal();
    //static clsGlobal* self();

    static QSqlDatabase objDbCon;
    static QSqlQuery objRs;
    static QMainWindow *mWnd;

    static QMainWindow* fnHandleWindows(GUI intWhichGUIToShow, GUI_INVOKE_PURPOSE intPurpose = GUI_INVOKE_PURPOSE::NOTHING, QVector<QString> VecStr=QVector<QString>::fromList(QStringList("")));
private:
    //static clsGlobal *objGlb;
};

#endif // CLSGLOBAL_H

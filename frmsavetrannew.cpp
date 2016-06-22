#include "frmsavetrannew.h"
#include "ui_frmsavetrannew.h"

frmSaveTranNew::frmSaveTranNew(QWidget *parent, GUI_INVOKE_PURPOSE intPurpose, QVector<QString> VecStr) :
    QMainWindow(parent),
    ui(new Ui::frmSaveTranNew)
{
    ui->setupUi(this);
    fnAppInit();
    show();
    fnInvokeFor(&intPurpose, &VecStr);
}

void frmSaveTranNew::fnAppInit()
{
    QScroller::grabGesture(ui->scrlLstBoxTran, QScroller::TouchGesture);
    QScroller::grabGesture(ui->scrlLstBoxTran2, QScroller::TouchGesture);
    QScroller::grabGesture(ui->lstChooseItemTran, QScroller::TouchGesture);
    QScroller::grabGesture(ui->lstExistingDataTran, QScroller::TouchGesture);
    ui->dtPurchaseDate->setDateTime(QDateTime::currentDateTime());
    ui->txtChooseItem->setFocus();
}

void frmSaveTranNew::fnInvokeFor(GUI_INVOKE_PURPOSE* intPurpose, QVector<QString>* strLst)
{
    switch(*intPurpose)
    {
    case GUI_INVOKE_PURPOSE::TRAN_EDIT:
        fnFromReport(&(strLst->at(0)),&(strLst->at(1)),&(strLst->at(2)),strLst->at(3).toInt(),strLst->at(4).toInt(),strLst->at(5),QDate::fromString(strLst->at(6),"dd-MMM-yyyy"),&(strLst->at(7)));
        break;
    }
}

void frmSaveTranNew::fnValueReset()
{
    ui->txtQty->setText("0");
    ui->txtAmt->setText("0");
    ui->txtWeight->setText("0");
    objVecSelectedItems.clear();
    objVecAllItems.clear();
    ui->lstChooseItemTran->clear();
    ui->txtChooseItem->clear();
    ui->lstExistingDataTran->clear();
    ui->txtAnyDescription->clear();
    ui->txtChooseItem->setFocus();
    ui->cmdSaveTran->setText("Save New Transaction Data");
    blnIsNewRecord=true;
    ui->lblTotalAddedItems->setText("Selected Item(s)");
    ui->lblTotalMatchFoundTran->setText("");
}

frmSaveTranNew::~frmSaveTranNew()
{
    delete ui;
}

void frmSaveTranNew::on_txtChooseItem_textEdited(const QString &arg1)
{
    fnFilterData( ui->txtChooseItem->text(), ui->lstExistingDataTran, ui->lblTotalMatchFoundTran);
}

void frmSaveTranNew::on_lstExistingDataTran_itemDoubleClicked(QListWidgetItem *item)
{
    fnAddToSelectedList();
}

void frmSaveTranNew::fnAddToSelectedList()
{
    objVecSelectedItems.push_back(objVecAllItems.at(ui->lstExistingDataTran->currentRow()));
    ui->lstChooseItemTran->addItem(objVecAllItems.at(ui->lstExistingDataTran->currentRow()).strItemName);

    objVecAllItems.removeAt(ui->lstExistingDataTran->currentRow());
    ui->lstExistingDataTran->takeItem(ui->lstExistingDataTran->currentRow());
    ui->lblTotalAddedItems->setText(QString::number(ui->lstChooseItemTran->count()) + " Item(s) Added");
}

void frmSaveTranNew::on_lstChooseItemTran_itemDoubleClicked(QListWidgetItem *item)
{
    objVecAllItems.push_back(objVecSelectedItems.at(ui->lstChooseItemTran->currentRow()));
    ui->lstExistingDataTran->addItem(objVecSelectedItems.at(ui->lstChooseItemTran->currentRow()).strItemName);

    objVecSelectedItems.removeAt(ui->lstChooseItemTran->currentRow());
    ui->lstChooseItemTran->takeItem(ui->lstChooseItemTran->currentRow());
    ui->lblTotalAddedItems->setText(QString::number(ui->lstChooseItemTran->count()) + " Item(s) Added");

}

void frmSaveTranNew::fnFilterData(QString strCondition, QListWidget* lstBox, QLabel* lbl)
{

    if(strCondition.trimmed()=="")
    {
        objVecAllItems.clear();
        lstBox->clear();
        return;
    }

    QString str="";

    str ="";
    str.append("select * from tbl_item_master where item_name like '%" );
    str.append(strCondition);
    str.append("%'");
    if(clsGlobal::objRs.exec(str))
    {
        str="";
        int jCount=0;
        lstBox->clear();
        objVecAllItems.clear();
        while(clsGlobal::objRs.next())
        {
            jCount++;
            lstBox->addItem(/*QString::number(jCount) + ") " +*/ clsGlobal::objRs.value("item_name").toString());
            clsFilterData c(clsGlobal::objRs.value("tbl_id").toInt(),0, clsGlobal::objRs.value("item_name").toString(),"");
            objVecAllItems.append(c);
        }
        lbl->setText(QString::number(jCount) + " Existing Item(s) Found");
    }
    else
    {
        QMessageBox::critical(0, qApp->tr("Query Error"), qApp->tr("Query Error on Table View"),QMessageBox::Cancel);
    }

    clsGlobal::objRs.clear();
}

void frmSaveTranNew::fnSaveNewRecord()
{
    int intItemId=0;
    QString strMulitItemDetails="",strQuery="";
    if(objVecSelectedItems.count()==1)
    {
        intItemId = objVecSelectedItems.at(0).intMastTblId;
    }
    else if(objVecSelectedItems.count()>1)
    {
        intItemId = 0 ;//Multiple items id
        for(int i=0; i<objVecSelectedItems.count(); i++)
        {
            strMulitItemDetails.append("["+QString::number(objVecSelectedItems.at(i).intMastTblId)+"]"+objVecSelectedItems.at(i).strItemName+"!~!");
        }
    }
    if(clsGlobal::objRs.exec("select ifnull(max(tbl_id),0) + 1 as \"new_id\"  from tbl_item_transaction"))
    {
        if(clsGlobal::objRs.next())
        {
            intTblIdTran = clsGlobal::objRs.value("new_id").toInt();
        }
    }
    else
    {
        QMessageBox::critical(0, qApp->tr("Query Error"), qApp->tr("Query Error on Table View"),QMessageBox::Cancel);
        return;
    }
    strQuery="insert into tbl_item_transaction (tbl_id, item_id, purchase_date, amount, qty, weight, multi_item_details, any_desc) values (" + QString::number(intTblIdTran) + "," + QString::number(intItemId) + ",'" + ui->dtPurchaseDate->dateTime().toString("yyyy-MM-dd HH:mm:ss") + "'," + ui->txtAmt->text() + "," + ui->txtQty->text() + ","+ ui->txtWeight->text() + ",'" + strMulitItemDetails +"','" + ui->txtAnyDescription->text() + "')";
    std::cerr<<strQuery.toStdString() << std::endl;
    if(clsGlobal::objRs.exec(strQuery))
    {
        QMessageBox::information(0, qApp->tr("Data Saved."), qApp->tr("Data Saved."),QMessageBox::Ok);
        fnValueReset();
    }
    else
    {
        std::cerr<<clsGlobal::objRs.lastError().text().toStdString() << std::endl;
        QMessageBox::critical(0, qApp->tr("Data Not Saved."), qApp->tr("Data Not Saved."),QMessageBox::Cancel);
    }
    clsGlobal::objRs.clear();
}

void frmSaveTranNew::on_cmdSaveTran_clicked()
{
    if(ui->lstChooseItemTran->count()==0)
    {
        QMessageBox::critical(0, qApp->tr("Save Error"), qApp->tr("Choose Item and proceed"),QMessageBox::Cancel);
        return;
    }

    if( ui->txtAmt->text().trimmed().toFloat()==0.0)
    {
        QMessageBox::critical(0, qApp->tr("Save Error"), qApp->tr("Amout field is mandatory"),QMessageBox::Cancel);
        return;
    }

    if( ui->txtQty->text().trimmed().toFloat()==0.0)
    {
        ui->txtQty->setText("0.0");
    }

    if( ui->txtWeight->text().trimmed().toFloat()==0.0)
    {
        ui->txtWeight->setText("0.0");
    }
    if(blnIsNewRecord)
    {
        fnSaveNewRecord();
    }
    else
    {
        fnSaveEditedRecord();
    }
}

void frmSaveTranNew::keyReleaseEvent(QKeyEvent *QK)
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

void frmSaveTranNew::on_cmdReportForTheDay_clicked()
{
    clsGlobal::fnHandleWindows(GUI::REPT,GUI_INVOKE_PURPOSE::TODAY_ENTRY);
}

void frmSaveTranNew::fnFromReport(const QString* strAmt, const QString* strQty, const QString* strWeight, int _intTblIdMast, int _intTblIdTran, QString strItems, QDate dtPurchaseDate, const QString* strAnyDesc)
{
    //"[12]Muttai!~![10]Milagai!~!"
    blnIsNewRecord=false;
    ui->cmdSaveTran->setText("Update Transaction Data");
    intTblIdTran = _intTblIdTran;
    intTblIdMast = _intTblIdMast;

    ui->txtQty->setText(*strQty);
    ui->txtAmt->setText(*strAmt);
    ui->txtWeight->setText(*strWeight);
    ui->dtPurchaseDate->setDate(dtPurchaseDate);
    ui->txtAnyDescription->setText(*strAnyDesc);

    if(intTblIdMast==0)
    {
        if(strItems.trimmed()!="")
        {
            QStringList strLst = strItems.split("!~!");
            for(QString str : strLst)
            {
                str =str.trimmed();
                if(str!="")
                {
                    int intIndex = str.indexOf("]");
                    QString strValue = str.mid(intIndex+1, str.indexOf("!~!")-intIndex+1);
                    clsFilterData c(str.mid(1, intIndex-1).toInt(),0,strValue,"");
                    objVecSelectedItems.push_back(c);
                    ui->lstChooseItemTran->addItem(strValue);
                }
            }
        }
    }
    else
    {
        clsFilterData c(intTblIdMast,0,strItems,"");
        objVecSelectedItems.push_back(c);
        ui->lstChooseItemTran->addItem(strItems);
    }
}

void frmSaveTranNew::fnSaveEditedRecord()
{
    int intItemId=0;
    QString strMulitItemDetails="",strQuery="";
    if(objVecSelectedItems.count()==1)
    {
        intItemId = objVecSelectedItems.at(0).intMastTblId;
    }
    else if(objVecSelectedItems.count()>1)
    {
        intItemId = 0 ;//Multiple items id
        for(int i=0; i<objVecSelectedItems.count(); i++)
        {
            strMulitItemDetails.append("["+QString::number(objVecSelectedItems.at(i).intMastTblId)+"]"+objVecSelectedItems.at(i).strItemName+"!~!");
        }
    }

    strQuery="update tbl_item_transaction set item_id = " + QString::number(intItemId) + ", ";
    strQuery.append("amount = " + ui->txtAmt->text() + ", ");
    strQuery.append("qty = " + ui->txtQty->text() + ", ");
    strQuery.append("weight = " + ui->txtWeight->text() + ", ");
    strQuery.append("multi_item_details = '" + strMulitItemDetails + "', ");
    strQuery.append("any_desc = '" + ui->txtAnyDescription->text() + "', ");
    strQuery.append("purchase_date = '" + ui->dtPurchaseDate->dateTime().toString("yyyy-MM-dd HH:mm:ss") + "', ");
    strQuery.append("updated_on = date(CURRENT_TIMESTAMP, 'localtime') ");
    strQuery.append("where tbl_id = " + QString::number(intTblIdTran));

    std::cerr<<strQuery.toStdString() << std::endl;
    if(clsGlobal::objRs.exec(strQuery))
    {
        QMessageBox::information(0, qApp->tr("Data Update"), qApp->tr("Data Updated"),QMessageBox::Ok);
        fnValueReset();
    }
    else
    {
        std::cerr<<clsGlobal::objRs.lastError().text().toStdString() << std::endl;
        QMessageBox::critical(0, qApp->tr("Data Not Updated"), qApp->tr("Data Not Updated"),QMessageBox::Cancel);
    }
    clsGlobal::objRs.clear();
}

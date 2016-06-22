#ifndef FRMSAVETRANNEW_H
#define FRMSAVETRANNEW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QKeyEvent>
#include <QScroller>
#include <QSysInfo>
#include <QListWidgetItem>
#include "clsglobal.h"

namespace Ui
{
class frmSaveTranNew;
}

//forward declaration
class clsFilterData;
enum class GUI_INVOKE_PURPOSE : int;

class frmSaveTranNew : public QMainWindow
{
    Q_OBJECT

public:
    //explicit frmSaveTranNew(QWidget *parent = 0, GUI_INVOKE_PURPOSE intPurpose=(GUI_INVOKE_PURPOSE)0, QVector<QString> VecStr=QVector<QString>::fromList(QStringList("")));
    explicit frmSaveTranNew(QWidget *parent, GUI_INVOKE_PURPOSE intPurpose, QVector<QString> VecStr);
    ~frmSaveTranNew();

private slots:

    void on_txtChooseItem_textEdited(const QString &arg1);

    void on_lstExistingDataTran_itemDoubleClicked(QListWidgetItem *item);

    void on_lstChooseItemTran_itemDoubleClicked(QListWidgetItem *item);

    void on_cmdSaveTran_clicked();

    void on_cmdReportForTheDay_clicked();

private:
    Ui::frmSaveTranNew *ui;
    void keyReleaseEvent(QKeyEvent *QK);
    //QHash<int, QString> objHashAllItems;
    //QHash<int, QString> objHashSelectedItems;
    QVector<clsFilterData> objVecSelectedItems;
    QVector<clsFilterData> objVecAllItems;

    void fnFilterData(QString strCondition, QListWidget *lstBox, QLabel *lbl);
    void fnAddToSelectedList();
    void fnValueReset();
    //void fnFormItemString();
    void fnAppInit();
    void fnSaveNewRecord();
    void fnSaveEditedRecord();
    bool blnIsNewRecord=true;
    int intTblIdTran=-1, intTblIdMast=-1;
    void fnInvokeFor(GUI_INVOKE_PURPOSE *intPurpose, QVector<QString> *strLst);
    void fnFromReport(const QString *strAmt, const QString *strQty, const QString *strWeight, int _intTblId, int _intTblIdTran, QString strItems, QDate dtPurchaseDate, const QString *strAnyDesc);
};

#endif // FRMSAVETRANNEW_H

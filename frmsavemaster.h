#ifndef FRMSAVEMASTER_H
#define FRMSAVEMASTER_H

#include <QMainWindow>
#include <QMessageBox>
#include <QKeyEvent>
#include <QScroller>
#include <QSysInfo>
#include <iostream>
#include <QVector>
#include "clsglobal.h"

namespace Ui
{
class frmSaveMaster;
}

//forward declaration
class clsFilterData;
enum class GUI_INVOKE_PURPOSE;

class frmSaveMaster : public QMainWindow
{
    Q_OBJECT

public:
    explicit frmSaveMaster(QWidget *parent = 0, GUI_INVOKE_PURPOSE intPurpose=(GUI_INVOKE_PURPOSE)0, QVector<QString> VecStr=QVector<QString>::fromList(QStringList("")));
    ~frmSaveMaster();

private slots:
    void on_cmdSaveMaster_clicked();

    void on_txtItemMast_textEdited(const QString &arg1);

    void on_lstExistingData_itemDoubleClicked(QListWidgetItem *item);

    void on_lstExistingData_clicked(const QModelIndex &index);

private:
    Ui::frmSaveMaster *ui;
    void keyReleaseEvent(QKeyEvent *QK);
    void fnAppInit();
    void fnFillTableData(QString strCondition, QListWidget *lstBox, QLabel *lbl);
    void fnResetValues();
    QVector<clsFilterData> objVecAllItems;
    QHash<int,int> objHashItemTypeByTypeId, objHashItemTypeByIndex;
    void fnSelectDataForEdit();
    int intEditItemId=-1;
    bool blnIsNew=true;
    void fnSaveNewData();
    void fnSaveExistingData();
    void fnInvokeFor(GUI_INVOKE_PURPOSE *intPurpose = NULL, QVector<QString> *strLst = NULL);
    void fnLoadItemTypes();
};

#endif // FRMSAVEMASTER_H

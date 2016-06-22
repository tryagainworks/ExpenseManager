#ifndef FRMSTARTUPNEW_H
#define FRMSTARTUPNEW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QKeyEvent>
#include <QScroller>
#include <QSysInfo>
#include <QListWidget>
#include "clsglobal.h"

namespace Ui
{
class frmStartUpNew;
}

//forward declaration
enum class GUI_INVOKE_PURPOSE;

class frmStartUpNew : public QMainWindow
{
    Q_OBJECT

public:
    explicit frmStartUpNew(QWidget *parent = 0, GUI_INVOKE_PURPOSE intPurpose=(GUI_INVOKE_PURPOSE)0, QVector<QString> VecStr=QVector<QString>::fromList(QStringList("")));
    ~frmStartUpNew();

private slots:
    void on_cmdEntry_2_clicked();

    void on_cmdSummaryReport_2_clicked();

    void on_cmdDetailReport_2_clicked();

    void on_cmdMasterEntry_clicked();

    void on_cmdExit_clicked();

    void on_cmdSettings_clicked();

    void on_cmdLogout_clicked();

private:
    Ui::frmStartUpNew *ui;
    void keyReleaseEvent(QKeyEvent *QK);
    void fnFillTableData(QString strCondition, QListWidget *lstBox, QLabel *lbl);
    void fnAddToSelectedList();
    void fnGoToEntry();
    void fnViewTranDataByDate();
    void fnGoBackToChooseItems();
    void fnInvokeFor(GUI_INVOKE_PURPOSE *intPurpose = NULL, QVector<QString> *strLst = NULL);
};

#endif // FRMSTARTUPNEW_H

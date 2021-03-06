#ifndef FRMREPORT_H
#define FRMREPORT_H

#include <QMainWindow>
#include <QMessageBox>
#include <QKeyEvent>
#include <QScroller>
#include <QSysInfo>
#include <QVector>
#include "clsglobal.h"

namespace Ui
{
class frmReport;
}
//forward declaration
enum class GUI_INVOKE_PURPOSE;

class frmReport : public QMainWindow
{
    Q_OBJECT

public:
    explicit frmReport(QWidget *parent = 0, GUI_INVOKE_PURPOSE intPurpose=(GUI_INVOKE_PURPOSE)0, QVector<QString> VecStr=QVector<QString>::fromList(QStringList("")));
    ~frmReport();

    void fnInitValues(QString strRptType);
    void fnFromTransaction();

private slots:
    void on_optByAddedDate_clicked();

    void on_optByPurchaseDate_clicked();

    void on_dtTranView_userDateChanged(const QDate &date);

    void on_cmdShowReport_clicked();

    void on_cbo1Day_highlighted(const QString &arg1);

    void on_cbo5Days_highlighted(int index);

    void on_cbo1Week_highlighted(int index);

    void on_cbo1Month_highlighted(int index);

    void on_cbo1Year_highlighted(int index);

    void on_cmdEditRecord_clicked();

private:
    Ui::frmReport *ui;
    void keyReleaseEvent(QKeyEvent *QK);
    void fnAppInti();
    void fnViewTranDataByDate();
    void fnShowFilters();
    bool blnFromTransaction=false;
    QVector<clsFilterData> objVecAllItems;
    void fnInvokeFor(GUI_INVOKE_PURPOSE *intPurpose = NULL, QVector<QString> *strLst = NULL);
};

#endif // FRMREPORT_H

#ifndef FRMLOGIN_H
#define FRMLOGIN_H

#include <QMainWindow>
#include "clsglobal.h"

namespace Ui
{
class frmLogin;
}

//forward declaration
enum class GUI_INVOKE_PURPOSE;

class frmLogin : public QMainWindow
{
    Q_OBJECT

public:
    explicit frmLogin(QWidget *parent = 0,GUI_INVOKE_PURPOSE intPurpose=(GUI_INVOKE_PURPOSE)0, QVector<QString> VecStr=QVector<QString>::fromList(QStringList("")));
    ~frmLogin();

private slots:
    void on_cmdGo_clicked();

    void on_txtPwd1_textEdited(const QString &arg1);

private:
    Ui::frmLogin *ui;
    void keyReleaseEvent(QKeyEvent *QK);
    void fnDoLogin();
    void fnInvokeFor(GUI_INVOKE_PURPOSE *intPurpose = NULL, QVector<QString> *strLst = NULL);
};

#endif // FRMLOGIN_H

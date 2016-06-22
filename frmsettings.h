#ifndef FRMSETTINGS_H
#define FRMSETTINGS_H

#include <QMainWindow>
#include "clsglobal.h"

namespace Ui
{
class frmsettings;
}

//forward declaration
enum class GUI_INVOKE_PURPOSE;

class frmsettings : public QMainWindow
{
    Q_OBJECT

public:
    explicit frmsettings(QWidget *parent = 0,GUI_INVOKE_PURPOSE intPurpose=(GUI_INVOKE_PURPOSE)0, QVector<QString> VecStr=QVector<QString>::fromList(QStringList("")));
    ~frmsettings();

private:
    Ui::frmsettings *ui;
    void keyReleaseEvent(QKeyEvent *QK);
    void fnInvokeFor(GUI_INVOKE_PURPOSE *intPurpose = NULL, QVector<QString> *strLst = NULL);
};

#endif // FRMSETTINGS_H

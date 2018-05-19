#ifndef GETRULEDIALOG_H
#define GETRULEDIALOG_H

#include <QDialog>
#include <string>

namespace Ui {
class GetRuleDialog;
}

class GetRuleDialog : public QDialog
{
Q_OBJECT

public:
explicit GetRuleDialog(QWidget *parent = 0);
~GetRuleDialog();
std::string GetRuleFromDialog();

private:
Ui::GetRuleDialog *ui;
};

#endif // GETRULEDIALOG_H

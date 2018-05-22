#ifndef GETRULEDIALOG_H
#define GETRULEDIALOG_H

#include <QDialog>
#include <string>

namespace Ui {
class GetRuleDialog;
}
/*!
 * \brief The GetRuleDialog class
 *
 * Dialog class for retriving game rule from user.
 */
class GetRuleDialog : public QDialog
{
Q_OBJECT

public:
/*!
 * \brief GetRuleDialog constructor.
 * \param parent - pointer to arent object.
 */
explicit GetRuleDialog(QWidget *parent = 0);
~GetRuleDialog();
/*!
 * \brief Method returns user rule from dialog.
 * \return user rule in string format.
 */
std::string GetRuleFromDialog();

private:
Ui::GetRuleDialog *ui;
};

#endif // GETRULEDIALOG_H

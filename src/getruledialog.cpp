#include "getruledialog.h"
#include "ui_getruledialog.h"

GetRuleDialog::GetRuleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetRuleDialog)
{
    ui->setupUi(this);
}

GetRuleDialog::~GetRuleDialog()
{
    delete ui;
}

std::string GetRuleDialog::GetRuleFromDialog()
{
    return this->ui->line_edit_rule->text().toStdString();
}



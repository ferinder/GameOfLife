#include "getruledialog.h"
#include "ui_getruledialog.h"

GetRuleDialog::GetRuleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetRuleDialog)
{
    ui->setupUi(this);
    QRegExpValidator * v = new QRegExpValidator(QRegExp("[1-9]{1,9}/{1,1}[1-9]{1,9}"));
    ui->line_edit_rule->setValidator(v);
}

GetRuleDialog::~GetRuleDialog()
{
    delete ui;
}

std::string GetRuleDialog::GetRuleFromDialog()
{
    return this->ui->line_edit_rule->text().toStdString();
}



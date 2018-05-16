#include "rulesdialog.h"
#include "ui_rulesdialog.h"

RulesDialog::RulesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RulesDialog)
{
    ui->setupUi(this);
    populateList(this->ui->list_rules);
}

void RulesDialog::populateList(QListWidget *view)
{
    view->clear();
    std::ifstream file("rules");
    if(file.is_open())
    {
        std::string line;
        while(std::getline(file, line))
        {
            new QListWidgetItem(QString(line.c_str()),view);
        }
    }
    else qDebug() << "File opening error";
    file.close();
}

RulesDialog::~RulesDialog()
{
    delete ui;
}

std::string RulesDialog::GetRule()
{
    return ui->list_rules->currentItem()->text().toStdString();
}

void RulesDialog::on_btn_add_clicked()
{
    GetRuleDialog dlg(this);
    if(dlg.exec() == QDialog::Accepted)
    {
        std::ofstream file("rules", std::ios_base::app);
        if(file.is_open())
        {
            file << '\n' <<dlg.GetRuleFromDialog();
        }
        file.close();
        populateList(this->ui->list_rules);
    }
}

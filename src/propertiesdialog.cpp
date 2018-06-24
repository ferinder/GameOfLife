#include "propertiesdialog.h"
#include "ui_propertiesdialog.h"

PropertiesDialog::PropertiesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PropertiesDialog)
{
    ui->setupUi(this);
    ui->spin_sim_time->setMaximum(2000);
    ui->spin_sim_time->setMinimum(100);
    ui->spin_sim_time->setValue(500);
}

PropertiesDialog::~PropertiesDialog()
{
    delete ui;
}

int PropertiesDialog::GetSimulationTime()
{
    return this->ui->spin_sim_time->value();
}

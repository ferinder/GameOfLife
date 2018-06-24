#include "propertiesdialog.h"
#include "ui_propertiesdialog.h"

PropertiesDialog::PropertiesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PropertiesDialog)
{
    ui->setupUi(this);
    ui->spin_sim_time->setMaximum(2000);
    ui->spin_sim_time->setMinimum(100);
    ui->cBox_wraping->addItem("Nie");
    ui->cBox_wraping->addItem("Tak");

    GameSettings *settings = GameSettings::GetInstance();
    ui->spin_sim_time->setValue(settings->GetSimulationInterval());

    if(settings->GetBoardWraping())
        ui->cBox_wraping->setCurrentIndex(1);
    else
        ui->cBox_wraping->setCurrentIndex(0);
}

PropertiesDialog::~PropertiesDialog()
{
    delete ui;
}

int PropertiesDialog::GetSimulationTime()
{
    return this->ui->spin_sim_time->value();
}

bool PropertiesDialog::GetBoardWrapingSetting()
{
    if(this->ui->cBox_wraping->currentIndex() == 0)
        return false;
    else
        return true;
}

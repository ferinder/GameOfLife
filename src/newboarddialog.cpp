#include "newboarddialog.h"
#include "ui_newboarddialog.h"

NewBoardDialog::NewBoardDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewBoardDialog)
{
    ui->setupUi(this);
    ui->sizeX->setMinimum(0);
    ui->sizeX->setMaximum(200);
    ui->sizeY->setMinimum(0);
    ui->sizeY->setMaximum(150);
    ui->cBoxColorRule->addItem("Default");
    ui->cBoxColorRule->addItem("Immigration");
    ui->cBoxColorRule->addItem("QuadLife");
}

NewBoardDialog::~NewBoardDialog()
{
    delete ui;
}

int NewBoardDialog::GetSizeX()
{
    return ui->sizeX->value();
}

int NewBoardDialog::GetSizeY()
{
    return ui->sizeY->value();
}

int NewBoardDialog::GetColorRule()
{
    int colorRule = ui->cBoxColorRule->currentIndex();
    switch (colorRule) {
    case 0:
        return ColorRule::Default;
        break;
    case 1:
        return ColorRule::Immigration;
        break;
    case 2:
        return ColorRule::QuadLife;
        break;
    default:
        break;
    }
    return -1;
}

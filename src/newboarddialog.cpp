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
    ui->sizeY->setMaximum(200);
}

NewBoardDialog::~NewBoardDialog()
{
    delete ui;
}

int NewBoardDialog::GetSizeXFromDialog()
{
    return ui->sizeX->value();
}

int NewBoardDialog::GetSizeYFromDialog()
{
    return ui->sizeY->value();
}
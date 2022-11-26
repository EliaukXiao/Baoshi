#include "CNameDlg.h"
#include "ui_CNameDlg.h"
#include"CBejeweledDlg.h"


CNameDlg::CNameDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CNameDlg)
{
    ui->setupUi(this);
}

CNameDlg::~CNameDlg()
{
    delete ui;
}

void CNameDlg::on_pushButton_clicked()
{
    name = ui->lineEdit->text();
    this->close();
}

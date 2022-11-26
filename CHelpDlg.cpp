#include "CHelpDlg.h"
#include "ui_CHelpDlg.h"

CHelpDlg::CHelpDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CHelpDlg)
{
    ui->setupUi(this);
}

CHelpDlg::~CHelpDlg()
{
    delete ui;
}

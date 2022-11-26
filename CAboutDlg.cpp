#include "CAboutDlg.h"
#include "ui_CAboutDlg.h"

CAboutDlg::CAboutDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CAboutDlg)
{
    ui->setupUi(this);
}

CAboutDlg::~CAboutDlg()
{
    delete ui;
}

#include "CMenuDlg.h"
#include "ui_CMenuDlg.h"
#include"CGameDlg.h"
#include<CMusicPlayer.h>
CMenuDlg::CMenuDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CMenuDlg)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
}

CMenuDlg::~CMenuDlg()
{
    delete ui;
}

void CMenuDlg::on_pushButton_clicked()//主菜单
{
    emit openzhucaidansignal();
    this->close();
}

void CMenuDlg::on_pushButton_shezhiyouxi_clicked()
{
    if(SetInitFlag == false){
    SetDlg = new CSetDlag;
    SetDlg->setWindowTitle("设置");
    SetInitFlag = true;
    }
connect(SetDlg,SIGNAL(change1signal2()),this,SLOT(change11()));
connect(SetDlg,SIGNAL(change2signal2()),this,SLOT(change12()));
connect(SetDlg,SIGNAL(change3signal2()),this,SLOT(change13()));
    SetDlg->show();
}

void CMenuDlg::on_pushButton_fanhuiyouxi_clicked()
{
    emit sendsignal();
    this->close();

}


void CMenuDlg::on_pushButtochongxinyouxin__clicked()
{

    emit sendsignal1();
    this->close();

}

void CMenuDlg::closeEvent(QCloseEvent *event)
{
    emit sendsignal();
    this->close();
}

void CMenuDlg::on_pushButton_tuichuyouxi_clicked()
{
    emit sendquitsignal();
        emit change2signal();
    this->close();
}

CSetDlag* CMenuDlg::getSet(){
    if(SetInitFlag == false){
    SetDlg = new CSetDlag;
    SetDlg->setWindowTitle("设置");
    SetInitFlag = true;
    }
    return SetDlg;
}

void  CMenuDlg::change11(){
    emit change1signal();
}

void  CMenuDlg::change12(){
    emit change2signal();
}

void  CMenuDlg::change13(){
    emit change3signal();
}


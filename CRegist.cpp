#include "CRegist.h"
#include "ui_CRegist.h"
#include"QMessageBox"
#include "Login.h"
CRegist::CRegist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CRegist)
{
    ui->setupUi(this);
    CRank = CRankLogic::getInstance();
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->lineEdit_3->setEchoMode(QLineEdit::Password);
}

CRegist::~CRegist()
{
    delete ui;
}

void CRegist::on_pushButton_clicked()
{
    if(ui->lineEdit->text()==""){
        QMessageBox msgBox;
        msgBox.setWindowTitle("注意");
        msgBox.setText("用户名不能为空！");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Ok){
        }
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        return;
    }
    if(ui->lineEdit_2->text()==""){
        QMessageBox msgBox;
        msgBox.setWindowTitle("注意");
        msgBox.setText("密码不能为空！");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Ok){
        }
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        return;
    }
    if(ui->lineEdit_2->text()!=ui->lineEdit_3->text()){
        QMessageBox msgBox;
        msgBox.setWindowTitle("注意");
        msgBox.setText("两次密码不同！");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Ok){
        }
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        return;
    }

   //这里写注册的操作
    if(CRank.Inqure(ui->lineEdit->text())){
        QMessageBox msgBox;
        msgBox.setWindowTitle("注意");
        msgBox.setText("该用户名已被注册");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Ok){
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            ui->lineEdit_3->clear();
        }
    }
    else if(ui->lineEdit->text()!=""){
        CRank.Insert(ui->lineEdit->text(),0,0,ui->lineEdit_2->text());
        qDebug()<<"r:"<<ui->lineEdit->text();
        qDebug()<<"r:"<<ui->lineEdit_2->text();
        QMessageBox msgBox;
        msgBox.setWindowTitle("注意");
        msgBox.setText("注册成功");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Ok){
            Login w;
            w.setWindowTitle("登录");
            w.show();
        }
        this->close();
    }
}

void CRegist::on_pushButton_2_clicked()
{
    this->close();
}

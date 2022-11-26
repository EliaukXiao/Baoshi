#include "Login.h"
#include "ui_Login.h"
#include<QInputDialog>
#include"QMessageBox"
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    CRank = CRankLogic::getInstance();
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    QPalette palette;
    QPixmap pixmap("..\\BSMZproject\\sucai\\background2.bmp");
    palette.setBrush(QPalette::Window,QBrush(pixmap));
    this->setPalette(palette);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{

    if(CRank.Inqure(ui->lineEdit->text())){//查找该玩家
        if(CRank.password==ui->lineEdit_2->text()){//检验密码
            BejeweledDlg = new CBejeweledDlg(ui->lineEdit->text());
            BejeweledDlg->setAutoFillBackground(true);
            QPalette palette;
            QPixmap pixmap("..\\BSMZproject\\sucai\\登录界面2.bmp");
            palette.setBrush(QPalette::Window, QBrush(pixmap));
            BejeweledDlg->setPalette(palette);
            this->close();
            BejeweledDlg->show();
        }
        else{
            QMessageBox msgBox;
            msgBox.setWindowTitle("注意");
            msgBox.setText("密码错误！");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            int ret = msgBox.exec();
            if(ret == QMessageBox::Ok){
               ui->lineEdit_2->clear();
            }
        }
    }
    else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("注意");
        msgBox.setText("用户不存在！");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Ok){
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
        }
    }
}

void Login::on_pushButton_2_clicked()
{
    Regist = new CRegist;
    Regist->setWindowTitle("注册");
    Regist->setWindowModality(Qt::ApplicationModal);
    Regist->show();

}

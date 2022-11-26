#include "CGameDlg.h"
#include "ui_CGameDlg.h"
#include"QProgressBar"
#include"QTimer"
#include <QMovie>
#include<QMessageBox>
#include <QDebug>
#include<QStyleOption>
#include<QVBoxLayout>
#include<QInputDialog>

CGameDlg::CGameDlg(int model,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CGameDlg)
{
    ui->setupUi(this);
    ui->pushButton_daojv1->setToolTip("消除所有与所选宝石同行同列的宝石");
    ui->pushButton_daojv1_2->setToolTip("消除所选宝石周围八格的宝石");
    ui->pushButton_daojv1_3->setToolTip("消除所有与所选宝石相同的宝石");
    this->model = model;
    CRank = CRankLogic::getInstance();
    isFirst=true;
    ui->progressBar->setValue(100);
    temp =100;
    qtimer1 = new QTimer(this);
    qtimer1->start(1000);
    connect(qtimer1, SIGNAL(timeout()), this, SLOT(on_time_out1()));
    if(MenuInitFlag == false) {
        MenuDlg = new CMenuDlg();
        MenuDlg->setWindowTitle("菜单");
        MenuInitFlag = true;
    }
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++)
            flag[i][j] =0;
    }
    MenuDlg->getSet()->getMusicPlayer()->bgm(1,"../BSMZproject/music/背景音乐.mp3");
    MenuDlg->getSet()->getMusicPlayer()->bgmstop();
    Init();
    QPalette palette;
    QPixmap pixmap("..\\BSMZproject\\sucai\\background.bmp");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    this->setPalette(palette);
    ui->pushButton_daojv1->setEnabled(false);
    ui->pushButton_daojv1_2->setEnabled(false);
    ui->pushButton_daojv1_3->setEnabled(false);
}

CGameDlg::~CGameDlg()
{
    delete ui;
}

bool CGameDlg::eventFilter(QObject *target, QEvent *e){
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            if(target == pb[i][j]){
                if(e->type()==QEvent::MouseButtonPress){
                    nowbaoshi = map[i][j];
                    if(daojv1Num!=0)
                    ui->pushButton_daojv1->setEnabled(true);
                    if(daojv2Num!=0)
                    ui->pushButton_daojv1_2->setEnabled(true);
                    if(daojv3Num!=0)
                    ui->pushButton_daojv1_3->setEnabled(true);

                    ui->pushButton_tishi->setEnabled(false);
                    if(isFirst){
                        pb[tempx1][tempy1]->setStyleSheet("background:transparent;");
                        tempx = i;
                        tempy = j;
                        isFirst=false;
                        pb[i][j]->setStyleSheet("border:1px solid green;");
                    }
                    else{
                        pb[tempx][tempy]->setStyleSheet("background:transparent;");
                        tempx1 = i;
                        tempy1 = j;
                        pb[i][j]->setStyleSheet("border:1px solid green;");
                        if(logic->change(i,j,tempx,tempy,map)){
                            ui->pushButton_daojv1->setEnabled(false);
                            ui->pushButton_daojv1_2->setEnabled(false);
                            ui->pushButton_daojv1_3->setEnabled(false);
                            while(logic->CanEmilinate(map)){
                                int tempcount=0;
                                tempcount=logic->Emilinate(map,sorce);//消除
                                if(tempcount>=4&&tempcount<5){
                                    daojv2Num++;
                                    if(daojv2Num>3)
                                        daojv2Num=3;
                                    ui->label_5->setText("剩余:"+QString::number(daojv2Num));
                                    getMenu()->getSet()->getMusicPlayer()->disapperSound1();
                                }
                                if(tempcount>=5&&tempcount<6){
                                    daojv1Num++;
                                    if(daojv1Num>3)
                                        daojv1Num=3;
                                    ui->label_4->setText("剩余:"+QString::number(daojv1Num));
                                    getMenu()->getSet()->getMusicPlayer()->disapperSound2();


                                }
                                if(tempcount>=6){
                                    daojv3Num++;
                                    if(daojv3Num>3)
                                        daojv3Num=3;
                                    ui->label_6->setText("剩余:"+QString::number(daojv3Num));
                                    getMenu()->getSet()->getMusicPlayer()->disapperSound3();
                                }
                                if(tempcount<5)
                                getMenu()->getSet()->getMusicPlayer()->disapperSound();
                                UPDATE1();
                                while(logic->MoveDown(map))//下移
                                UPDATE();
                                logic->replenish(map);//补充
                                UPDATE();
                            }
                            if(!logic->isLive(map)){
                                QMessageBox msgBox;
                                msgBox.setText("注意！");
                                msgBox.setInformativeText("无子可消，将对地图进行刷新！");
                                msgBox.setStandardButtons(QMessageBox::Ok);
                                msgBox.setDefaultButton(QMessageBox::Ok);
                                logic->BulidMap(map);
                                UPDATE();
                            }
                        }

                        isFirst=true;
                    }
                    if(tishicishu>0)
                    ui->pushButton_tishi->setEnabled(true);
                }
            }
        }
    }
    return false;
}
void CGameDlg::UPDATE1(){

    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            movie[i][j]->stop();
        }
    }

    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            if(changebaoshiflag==1)
                changebaoshi(i,j,map[i][j]);
            else if(changebaoshiflag==2)
                changebaoshi2(i,j,map[i][j]);
            else if(changebaoshiflag==3)
            changebaoshi3(i,j,map[i][j]);
            if(map[i][j]==0){//此处添加gif动画效果
                la[i][j]->setVisible(true);
                movie[i][j]->start();
            }
            pb[i][j]->setStyleSheet("background:transparent;");
        }
    }
    if(tishicishu<=0)
    ui->pushButton_tishi->setEnabled(false);
    this->update();
    qApp->processEvents();
    t.start();
    ui->label_2->setText(QString::number(sorce)+mubiao);
    while(t.elapsed()<50);

}

void CGameDlg::UPDATE(){

    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            la[i][j]->setVisible(false);
            movie[i][j]->stop();
        }
    }
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            if(changebaoshiflag==1)
                changebaoshi(i,j,map[i][j]);
            else if(changebaoshiflag==2)
                changebaoshi2(i,j,map[i][j]);
            else if(changebaoshiflag==3)
            changebaoshi3(i,j,map[i][j]);
            pb[i][j]->setStyleSheet("background:transparent;");
        }
    }
    if(tishicishu<=0)
    ui->pushButton_tishi->setEnabled(false);
    this->update();
    qApp->processEvents();
    t.start();
    ui->label_2->setText(QString::number(sorce)+mubiao);
    while(t.elapsed()<50);
}
void CGameDlg::on_time_out1()
{
     ui->label_3->setText(name);
    temp=temp-speed;
      ui->progressBar->setValue(temp);
      if(temp == 0 && model==1)
      {
          MenuDlg->getSet()->getMusicPlayer()->defeatSound();
          qtimer1->stop();
          UPDATE();
          QMessageBox msgBox;
          msgBox.setWindowTitle("结束！");
          msgBox.setText("游戏结束！");
          msgBox.setInformativeText("你的积分是："+QString::number(sorce));
          msgBox.setStandardButtons(QMessageBox::Ok);
          msgBox.setDefaultButton(QMessageBox::Ok);
          int ret = msgBox.exec();
          if(ret == QMessageBox::Ok){

          }
          qtimer1->stop();
          CRank.Modif(temp,sorce,name);
          this->close();
          openzhucaidan();
      }
      if(temp == 0 &&model==2&&guanqia==1&&sorce>=200){
          QMessageBox msgBox;
          msgBox.setWindowTitle("WIN");
          msgBox.setText("恭喜！");
          msgBox.setInformativeText("即将进入下一关！");
          msgBox.setStandardButtons(QMessageBox::Ok);
          msgBox.setDefaultButton(QMessageBox::Ok);
          int ret = msgBox.exec();
          if(ret == QMessageBox::Ok){
          }
          guanqia=2;
          Init();
          for(int i=0;i<num;i++){
              for(int j=0;j<num;j++){
                  pb[i][j]->setVisible(true);
              }
          }
      }
      if(temp == 0 &&model==2&&guanqia==1&&sorce<200){
          QMessageBox msgBox;
          msgBox.setWindowTitle("FAIL");
          msgBox.setText("游戏结束！");
          msgBox.setInformativeText("你的积分是："+QString::number(sorce));
          msgBox.setStandardButtons(QMessageBox::Ok);
          msgBox.setDefaultButton(QMessageBox::Ok);
          int ret = msgBox.exec();
          if(ret == QMessageBox::Ok){

          }
          qtimer1->stop();
          this->close();
          openzhucaidan();

      }
      if(temp == 0 &&model==2&&guanqia==2&&sorce>=500){
          QMessageBox msgBox;
          msgBox.setWindowTitle("WIN");
          msgBox.setText("恭喜！");
          msgBox.setInformativeText("即将进入下一关！");
          msgBox.setStandardButtons(QMessageBox::Ok);
          msgBox.setDefaultButton(QMessageBox::Ok);
          int ret = msgBox.exec();
          if(ret == QMessageBox::Ok){
          }
          guanqia=3;
          Init();
          for(int i=0;i<num;i++){
              for(int j=0;j<num;j++){
                  pb[i][j]->setVisible(true);
              }
          }
      }
      if(temp == 0 &&model==2&&guanqia==2&&sorce<500){
          QMessageBox msgBox;
          msgBox.setWindowTitle("FAIL");
          msgBox.setText("游戏结束！");
          msgBox.setInformativeText("你的积分是："+QString::number(sorce));
          msgBox.setStandardButtons(QMessageBox::Ok);
          msgBox.setDefaultButton(QMessageBox::Ok);
          int ret = msgBox.exec();
          if(ret == QMessageBox::Ok){

          }
          qtimer1->stop();
          this->close();
          openzhucaidan();
      }



      if(temp == 0 &&model==2&&guanqia==3&&sorce>=1000){
          QMessageBox msgBox;
          msgBox.setWindowTitle("WIN");
          msgBox.setText("恭喜！");
          msgBox.setInformativeText("即将进入下一关！");
          msgBox.setStandardButtons(QMessageBox::Ok);
          msgBox.setDefaultButton(QMessageBox::Ok);
          int ret = msgBox.exec();
          if(ret == QMessageBox::Ok){
          }
          guanqia=4;
          Init();
          for(int i=0;i<num;i++){
              for(int j=0;j<num;j++){
                  pb[i][j]->setVisible(true);
              }
          }
      }
      if(temp == 0 &&model==2&&guanqia==3&&sorce<1000){
          QMessageBox msgBox;
          msgBox.setWindowTitle("FAIL");
          msgBox.setText("游戏结束！");
          msgBox.setInformativeText("你的积分是："+QString::number(sorce));
          msgBox.setStandardButtons(QMessageBox::Ok);
          msgBox.setDefaultButton(QMessageBox::Ok);
          int ret = msgBox.exec();
          if(ret == QMessageBox::Ok){

          }
          qtimer1->stop();
          this->close();
          openzhucaidan();
      }
      if(temp == 0 &&model==2&&guanqia==4&&sorce>=2000){
          QMessageBox msgBox;
          msgBox.setWindowTitle("WIN");
          msgBox.setText("恭喜！");
          msgBox.setInformativeText("即将进入下一关！");
          msgBox.setStandardButtons(QMessageBox::Ok);
          msgBox.setDefaultButton(QMessageBox::Ok);
          int ret = msgBox.exec();
          if(ret == QMessageBox::Ok){
          }
          guanqia=5;
          Init();
          for(int i=0;i<num;i++){
              for(int j=0;j<num;j++){
                  pb[i][j]->setVisible(true);
              }
          }
      }
      if(temp == 0 &&model==2&&guanqia==4&&sorce<2000){
          QMessageBox msgBox;
          msgBox.setWindowTitle("FAIL");
          msgBox.setText("游戏结束！");
          msgBox.setInformativeText("你的积分是："+QString::number(sorce));
          msgBox.setStandardButtons(QMessageBox::Ok);
          msgBox.setDefaultButton(QMessageBox::Ok);
          int ret = msgBox.exec();
          if(ret == QMessageBox::Ok){
          }
          qtimer1->stop();
          this->close();
          openzhucaidan();
      }


      if(temp == 0 &&model==2&&guanqia==5&&sorce>4000){
          QMessageBox msgBox;
          msgBox.setWindowTitle("WIN");
          msgBox.setText("恭喜！");
          msgBox.setInformativeText(" 已通过所有关卡！");
          msgBox.setStandardButtons(QMessageBox::Ok);
          msgBox.setDefaultButton(QMessageBox::Ok);
          int ret = msgBox.exec();
          if(ret == QMessageBox::Ok){
          }
          qtimer1->stop();
          this->close();
      }
      if(temp == 0 &&model==2&&guanqia==5&&sorce<4000){
          QMessageBox msgBox;
          msgBox.setWindowTitle("FAIL");
          msgBox.setText("游戏结束！");
          msgBox.setInformativeText("你的积分是："+QString::number(sorce));
          msgBox.setStandardButtons(QMessageBox::Ok);
          msgBox.setDefaultButton(QMessageBox::Ok);
          int ret = msgBox.exec();
          if(ret == QMessageBox::Ok){

          }
          qtimer1->stop();
          this->close();
          openzhucaidan();
      }
}



void CGameDlg::on_pushButton_caidan_clicked()
{
    if(MenuInitFlag == false) {
    MenuDlg = new CMenuDlg();
    MenuDlg->setWindowTitle("菜单");
    MenuInitFlag = true;
    }
    connect(MenuDlg,SIGNAL(sendsignal()),this,SLOT(starttimer()));
    connect(MenuDlg,SIGNAL(sendsignal1()),this,SLOT(restart()));
    connect(MenuDlg,SIGNAL(sendquitsignal()),this,SLOT(quit()));
    connect(MenuDlg,SIGNAL(openzhucaidansignal()),this,SLOT(openzhucaidan()));
    connect(MenuDlg,SIGNAL(change1signal()),this,SLOT(change1()));
    connect(MenuDlg,SIGNAL(change2signal()),this,SLOT(change2()));
    connect(MenuDlg,SIGNAL(change3signal()),this,SLOT(change3()));
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            pb[i][j]->setVisible(false);
        }
    }
    ui->pushButton_daojv1->setEnabled(false);
    ui->pushButton_daojv1_2->setEnabled(false);
    ui->pushButton_daojv1_3->setEnabled(false);
    ui->pushButton_tishi->setEnabled(false);
    ui->pushButton_zanting->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    MenuDlg->show();
    qtimer1->stop();

}

void CGameDlg::on_pushButton_zanting_clicked()
{
    qtimer1->stop();
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++)
            pb[i][j]->setEnabled(false);
    }
    ui->pushButton_tishi->setEnabled(false);
    ui->pushButton_caidan->setEnabled(false);
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            pb[i][j]->setVisible(false);
        }
    }
    ui->pushButton_daojv1->setEnabled(false);
    ui->pushButton_daojv1_2->setEnabled(false);
    ui->pushButton_daojv1_3->setEnabled(false);
    ui->pushButton_tishi->setEnabled(false);
    ui->pushButton_zanting->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("暂停");
    msgBox.setText("继续吗?");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Ok){
        qtimer1->start();
        for(int i=0;i<num;i++){
            for(int j=0;j<num;j++)
                pb[i][j]->setEnabled(true);
        }
        ui->pushButton_tishi->setEnabled(true);
        ui->pushButton_caidan->setEnabled(true);
        for(int i=0;i<num;i++){
            for(int j=0;j<num;j++){
                pb[i][j]->setVisible(true);
            }
        }
        ui->pushButton_daojv1->setEnabled(true);
        ui->pushButton_daojv1_2->setEnabled(true);
        ui->pushButton_daojv1_3->setEnabled(true);
        ui->pushButton_tishi->setEnabled(true);
        ui->pushButton_zanting->setEnabled(true);
        ui->pushButton_5->setEnabled(true);

    }

}

void CGameDlg::on_pushButton_tishi_clicked()
{

    if(tishicishu<=0)
    ui->pushButton_tishi->setEnabled(false);
    else{
        tishicishu--;
        ui->pushButton_tishi->setText("提示"+QString::number(tishicishu));
        int a,b,c,d;
        logic->Hint(a,b,c,d,map);
        pb[a][b]->setStyleSheet("border:1px solid red;");
        pb[c][d]->setStyleSheet("border:1px solid red;");
    }
    sorce= sorce -20;
    ui->label_2->setText(QString::number(sorce)+mubiao);

    this->update();
    qApp->processEvents();
}
void CGameDlg::changebaoshi(int x,int y,int kind){
    QImage imgbaoshi[8];
    imgbaoshi[1].load("..\\BSMZproject\\sucai\\2.png");
    imgbaoshi[2].load("..\\BSMZproject\\sucai\\3.png");
    imgbaoshi[3].load("..\\BSMZproject\\sucai\\4.png");
    imgbaoshi[4].load("..\\BSMZproject\\sucai\\5.png");
    imgbaoshi[5].load("..\\BSMZproject\\sucai\\6.png");
    imgbaoshi[6].load("..\\BSMZproject\\sucai\\7.png");
    imgbaoshi[7].load("..\\BSMZproject\\sucai\\8.png");
    pb[x][y]->setIcon(QPixmap::fromImage(imgbaoshi[kind]));
}

void CGameDlg::changebaoshi2(int x,int y,int kind){
    QImage imgbaoshi[8];
    imgbaoshi[1].load("..\\BSMZproject\\sucai2\\2.png");
    imgbaoshi[2].load("..\\BSMZproject\\sucai2\\3.png");
    imgbaoshi[3].load("..\\BSMZproject\\sucai2\\4.png");
    imgbaoshi[4].load("..\\BSMZproject\\sucai2\\5.png");
    imgbaoshi[5].load("..\\BSMZproject\\sucai2\\6.png");
    imgbaoshi[6].load("..\\BSMZproject\\sucai2\\7.png");
    imgbaoshi[7].load("..\\BSMZproject\\sucai2\\8.png");
    pb[x][y]->setIcon(QPixmap::fromImage(imgbaoshi[kind]));
}

void CGameDlg::changebaoshi3(int x,int y,int kind){
    QImage imgbaoshi[8];
    imgbaoshi[1].load("..\\BSMZproject\\sucai3\\2.png");
    imgbaoshi[2].load("..\\BSMZproject\\sucai3\\3.png");
    imgbaoshi[3].load("..\\BSMZproject\\sucai3\\4.png");
    imgbaoshi[4].load("..\\BSMZproject\\sucai3\\5.png");
    imgbaoshi[5].load("..\\BSMZproject\\sucai3\\6.png");
    imgbaoshi[6].load("..\\BSMZproject\\sucai3\\7.png");
    imgbaoshi[7].load("..\\BSMZproject\\sucai3\\8.png");
    pb[x][y]->setIcon(QPixmap::fromImage(imgbaoshi[kind]));
}

void CGameDlg::starttimer(){
    qtimer1->start();
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            pb[i][j]->setVisible(true);
        }
    }
    if(daojv1Num!=0)
        ui->pushButton_daojv1->setEnabled(true);
    if(daojv2Num!=0)
        ui->pushButton_daojv1_2->setEnabled(true);
    if(daojv3Num!=0)
        ui->pushButton_daojv1_3->setEnabled(true);
    ui->pushButton_tishi->setEnabled(true);
    ui->pushButton_zanting->setEnabled(true);
    ui->pushButton_5->setEnabled(true);
}

void CGameDlg::restart(){
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            pb[i][j]->setVisible(false);
        }
    }
    logic->BulidMap(map);
    tishicishu =3;
    ui->pushButton_tishi->setEnabled(true);
    ui->pushButton_tishi->setText("提示"+QString::number(tishicishu));
    temp =100;
    qtimer1->start();
    sorce =0;
    UPDATE();
}

void CGameDlg::quit(){
    this->close();
}

void CGameDlg::openzhucaidan(){
    speed=0;
    emit openzhucaidansignal();
    MenuDlg->getSet()->getMusicPlayer()->bgmstop();
    this->close();
}

void CGameDlg::stoptimer(){
    qtimer1->stop();
}

void CGameDlg::starttimer1(){
    qtimer1->start();
}

CMenuDlg* CGameDlg::getMenu(){
    if(MenuInitFlag == false) {
    MenuDlg = new CMenuDlg();
    MenuDlg->setWindowTitle("菜单");
    MenuInitFlag = true;
    }
    return MenuDlg;
}

void CGameDlg::change1(){
    changebaoshiflag =1;
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
                changebaoshi(i,j,map[i][j]);
        }
    }
    QPalette palette;
    QPixmap pixmap("..\\BSMZproject\\sucai\\background.bmp");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    this->setPalette(palette);
    UPDATE();
}


void CGameDlg::change2(){
    changebaoshiflag =2;
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
                changebaoshi2(i,j,map[i][j]);
        }
    }
    QPalette palette;
    QPixmap pixmap("..\\BSMZproject\\sucai2\\background.bmp");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    this->setPalette(palette);
    UPDATE();
}

void CGameDlg::change3(){
    changebaoshiflag =3;
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            changebaoshi3(i,j,map[i][j]);
        }
    }
    QPalette palette;
    QPixmap pixmap("..\\BSMZproject\\sucai3\\background.bmp");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    this->setPalette(palette);
    UPDATE();
}


void CGameDlg::on_pushButton_clicked()
{
    MenuDlg->getSet()->getMusicPlayer()->yinlainglow();

}

void CGameDlg::on_pushButton_2_clicked()
{
    MenuDlg->getSet()->getMusicPlayer()->yinlianghigh();
}

void CGameDlg::on_pushButton_3_clicked()
{
    if(jingyinflag==0){
        jingyinflag = 1;
        MenuDlg->getSet()->getMusicPlayer()->jingyin();}
    else if(jingyinflag==1){
        jingyinflag=0;
        MenuDlg->getSet()->getMusicPlayer()->huifushengyin();
    }
}

void CGameDlg::on_pushButton_4_clicked()
{
    MenuDlg->getSet()->getMusicPlayer()->huifushengyin();
}

void CGameDlg::setname(QString a){
    name = a;
}

void CGameDlg::on_pushButton_5_clicked()
{
    logic->BulidMap(map);
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            if(changebaoshiflag==1)
                changebaoshi(i,j,map[i][j]);
            else if(changebaoshiflag==2)
                changebaoshi2(i,j,map[i][j]);
            else if(changebaoshiflag==3)
            changebaoshi3(i,j,map[i][j]);
            pb[i][j]->setStyleSheet("background:transparent;");
        }
    }
    sorce = sorce -100;
    if(sorce<0)
        sorce =0;
    ui->label_2->setText(QString::number(sorce)+mubiao);

}

void CGameDlg::Init(){
    if(model==1){
        speed =1;
        num = 8;
        mubiao ="";
    }
    if(model==2&&guanqia==1){
        num =6;
        speed =4;
        mubiao ="/200";
    }
    if(model==2&&guanqia==2){
        num =7;
        speed =4;
        mubiao ="/500";
    }
    if(model==2&&guanqia==3){
        num =8;
        speed =4;
        mubiao ="/1000";
    }
    if(model==2&&guanqia==4){
        num =8;
        speed =5;
        mubiao ="/2000";
    }
    if(model==2&&guanqia==5){
        num =8;
        speed =10;
        mubiao ="/4000";
    }
    map = new int* [num];
    for(int i=0;i<num;i++)
    map[i]=new int[num];
    logic =new CGameLogic(num,num,7);
    logic->BulidMap(map);
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            if(flag[i][j]==0){
            la[i][j] = new QLabel(this);
            la[i][j]->setText("aaa");
            la[i][j]->setFixedSize(50,50);
            la[i][j]->setGeometry(10+55*j,55*i,50,50);
            movie[i][j] = new QMovie("..\\BSMZproject\\music\\gif\\xinxin.gif");
            la[i][j]->setMovie(movie[i][j]);
            pb[i][j] = new QPushButton(this);
            pb[i][j]->setText("");
            if(changebaoshiflag==1)
                changebaoshi(i,j,map[i][j]);
            else if(changebaoshiflag==2)
                changebaoshi2(i,j,map[i][j]);
            else if(changebaoshiflag==3)
            changebaoshi3(i,j,map[i][j]);
            pb[i][j]->setIconSize(QSize(50,50));
            pb[i][j]->setGeometry(10+55*j,55*i,50,50);
            pb[i][j]->installEventFilter(this);
            pb[i][j]->setFlat(true);
            pb[i][j]->setStyleSheet("background:transparent;");
            flag[i][j]=1;
        }
        }
    }
    QFont ft;
    ft.setPointSize(20);
    ui->label_2->setFont(ft);
    ui->label_3->setFont(ft);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    ui->label_2->setPalette(pa);
    ui->label_3->setPalette(pa);
    ui->pushButton_tishi->setText("提示"+QString::number(tishicishu));
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            if(changebaoshiflag==1)
                changebaoshi(i,j,map[i][j]);
            else if(changebaoshiflag==2)
                changebaoshi2(i,j,map[i][j]);
            else if(changebaoshiflag==3)
            changebaoshi3(i,j,map[i][j]);
        }
     }
    temp=100;
    isFirst = true;
    ui->label_2->setText(QString::number(sorce)+mubiao);
}


void CGameDlg::on_pushButton_daojv1_clicked()
{
    getMenu()->getSet()->getMusicPlayer()->disapperSound4();
    for(int i=0;i<num;i++){
        map[tempx][i] =0;
    }
    for(int i=0;i<num;i++){
        map[i][tempy] =0;
    }
    sorce = sorce+150;
    ui->label_2->setText(QString::number(sorce));
    UPDATE1();
    while(logic->MoveDown(map))//下移
    UPDATE();
    logic->replenish(map);//补充
    UPDATE();
    while(logic->CanEmilinate(map)){
        logic->Emilinate(map,sorce);//消除
        UPDATE1();
        while(logic->MoveDown(map))//下移
            UPDATE();
        logic->replenish(map);//补充
        UPDATE();
    }
    pb[tempx][tempy]->setStyleSheet("background:transparent;");
    isFirst = true;
    daojv1Num--;
    ui->label_4->setText("剩余："+QString::number(daojv1Num));
    if(daojv1Num==0){
        ui->pushButton_daojv1->setEnabled(false);
    }
    ui->pushButton_daojv1->setEnabled(false);
    ui->pushButton_daojv1_2->setEnabled(false);
    ui->pushButton_daojv1_3->setEnabled(false);
}

void CGameDlg::on_pushButton_daojv1_2_clicked()
{
    getMenu()->getSet()->getMusicPlayer()->disapperSound5();
    int count =0;
    for(int i=tempx-1;i<tempx+2;i++){
        for(int j=tempy-1;j<tempy+2;j++){
            if(logic->Exist(i,j)){
                map[i][j] =0;
                count++;
            }
        }
    }
    sorce = sorce+count*10;
    UPDATE1();
    while(logic->MoveDown(map))//下移
        UPDATE();
    logic->replenish(map);//补充
    UPDATE();
    ui->label_2->setText(QString::number(sorce));
    while(logic->CanEmilinate(map)){
        logic->Emilinate(map,sorce);//消除
        UPDATE1();
        while(logic->MoveDown(map))//下移
            UPDATE();
        logic->replenish(map);//补充
        UPDATE();
    }
    pb[tempx][tempy]->setStyleSheet("background:transparent;");
    isFirst = true;
    daojv2Num--;
    ui->label_5->setText("剩余："+QString::number(daojv2Num));
    if(daojv2Num==0){
        ui->pushButton_daojv1_2->setEnabled(false);
    }
    ui->pushButton_daojv1->setEnabled(false);
    ui->pushButton_daojv1_2->setEnabled(false);
    ui->pushButton_daojv1_3->setEnabled(false);

}

void CGameDlg::on_pushButton_daojv1_3_clicked()
{
    getMenu()->getSet()->getMusicPlayer()->disapperSound6();
    int count =0;
    for (int i=0;i<num;i++) {
        for(int j=0;j<num;j++){
            if(map[i][j]==nowbaoshi){
                map[i][j]=0;
                count++;
            }
        }
    }
    sorce = sorce+count*10;
    UPDATE1();
    while(logic->MoveDown(map))//下移
    UPDATE();
    logic->replenish(map);//补充
    UPDATE();
    ui->label_2->setText(QString::number(sorce));
    while(logic->CanEmilinate(map)){
        logic->Emilinate(map,sorce);//消除
        UPDATE1();
        while(logic->MoveDown(map))//下移
        UPDATE();
        logic->replenish(map);//补充
        UPDATE();
    }
     pb[tempx][tempy]->setStyleSheet("background:transparent;");
     isFirst = true;
     daojv3Num--;
     ui->label_6->setText("剩余："+QString::number(daojv3Num));
     if(daojv3Num==0){
         ui->pushButton_daojv1_3->setEnabled(false);
     }
     ui->pushButton_daojv1->setEnabled(false);
     ui->pushButton_daojv1_2->setEnabled(false);
     ui->pushButton_daojv1_3->setEnabled(false);


}

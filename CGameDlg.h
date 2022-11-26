#ifndef CGAMEDLG_H
#define CGAMEDLG_H

#include <QWidget>
#include<CMenuDlg.h>
#include<QPushButton>
#include<QProgressBar>
#include<QTimer>
#include<QLabel>
#include "CGameLogic.h"
#include <QElapsedTimer>
#include "CSetDlag.h"
#include "CRankLogic.h"
namespace Ui {
class CGameDlg;
}

class CMenuDlg;
class CGameDlg : public QWidget
{
    Q_OBJECT

public:
    explicit CGameDlg(int i,QWidget *parent = nullptr);
    ~CGameDlg();
    CMenuDlg *MenuDlg;
    void changebaoshi(int x,int y,int kind);
    void changebaoshi2(int x,int y,int kind);
    void changebaoshi3(int x,int y,int kind);
//    void stoptimer();
    void stoptimer();
    void starttimer1();
    CMenuDlg* getMenu();
    void setname(QString a);
    void Init();
private slots:
    void change1();
    void change2();
    void change3();
    void on_pushButton_caidan_clicked();

    void on_pushButton_zanting_clicked();

    void on_pushButton_tishi_clicked();

    void on_time_out1();
    void UPDATE();
    void UPDATE1();
    void starttimer();
    void restart();
    void quit();
    void openzhucaidan();



    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_daojv1_clicked();

    void on_pushButton_daojv1_2_clicked();

    void on_pushButton_daojv1_3_clicked();

protected:
    bool eventFilter(QObject *target,QEvent *e);
private:
  Ui::CGameDlg *ui;
    QProgressBar *progressBar;
    QTimer *qtimer1;
    int temp;
    int tempx=0;
    int tempy=0;
    QPushButton *pb[8][8];
    QLabel *la[8][8];
    int **map;
    CGameLogic *logic;
    bool isFirst;
    int sorce=0;
    QElapsedTimer t;
    int tishicishu = 3;
    bool MenuInitFlag = false;
    QMovie *movie[8][8];
    int changebaoshiflag = 1;
    CRankLogic CRank;
    QString name = "";
    int tempx1=0;
    int tempy1=0;
    int guanqia =1;
    int num;
    int model;
    int speed;
    int flag[8][8];
    QString mubiao;
    int jingyinflag =0;
    int daojv1Num=1;
    int daojv2Num=1;
    int daojv3Num=1;
    int nowbaoshi;

signals:
    void openzhucaidansignal();
};

#endif // CGAMEDLG_H

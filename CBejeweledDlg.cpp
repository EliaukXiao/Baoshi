#include "CBejeweledDlg.h"
#include "ui_CBejeweledDlg.h"
#include"QInputDialog"

CBejeweledDlg::CBejeweledDlg(QString name,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->name = name;
        GameDlg2 = new CGameDlg(2);
        GameDlg2->setWindowTitle("宝石迷阵（ 闯关模式）");
        GameDlg2->stoptimer();
        GameDlg = new CGameDlg(1);
        GameDlg->setWindowTitle("宝石迷阵（普通模式）");
        GameDlg->stoptimer();
}


CBejeweledDlg::~CBejeweledDlg()
{
    delete ui;
}


void CBejeweledDlg::on_pushButton_clicked()//开始
{
    GameDlg->starttimer1();
    GameDlg->setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap("..\\BSMZproject\\sucai\\background.bmp");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    GameDlg->setPalette(palette);
    GameDlg->show();
    GameDlg->getMenu()->getSet()->getMusicPlayer()->bgmstart();
    GameDlg->setname(name);
    connect(GameDlg,SIGNAL(openzhucaidansignal()),this,SLOT(open()));
    this->hide();
}


void CBejeweledDlg::on_pushButton_paihangbang_clicked()
{
    RankDlg = new CRankDlg;
    RankDlg->setWindowTitle("排行榜");
    RankDlg->setWindowModality(Qt::ApplicationModal);
    RankDlg->show();

}

void CBejeweledDlg::on_pushButton_bangzhu_clicked()
{
    HelpDlg = new CHelpDlg;
    HelpDlg->setWindowTitle("帮助");
    HelpDlg->setWindowModality(Qt::ApplicationModal);
    HelpDlg->show();

}

void CBejeweledDlg::on_pushButton_guanyu_clicked()
{
    AboutDlg = new CAboutDlg;
    AboutDlg->setWindowTitle("关于");
    AboutDlg->setWindowModality(Qt::ApplicationModal);
    AboutDlg->show();
}

void CBejeweledDlg::open(){
    this->show();
    GameDlg = new CGameDlg(1);
    GameDlg->setWindowTitle("宝石迷阵");
    GameDlg->stoptimer();
    GameDlg2 = new CGameDlg(2);
    GameDlg2->setWindowTitle("宝石迷阵");
    GameDlg2->stoptimer();

}

void CBejeweledDlg::on_pushButton_paihangbang_2_clicked()
{
    GameDlg->getMenu()->getSet()->show();
}

void CBejeweledDlg::on_pushButton_2_clicked()
{
    GameDlg2->starttimer1();
    GameDlg2->setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap("..\\BSMZproject\\sucai\\background.bmp");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    GameDlg2->setPalette(palette);
    GameDlg2->show();
    GameDlg2->getMenu()->getSet()->getMusicPlayer()->bgmstart();
    connect(GameDlg2,SIGNAL(openzhucaidansignal()),this,SLOT(open()));
    this->hide();
}

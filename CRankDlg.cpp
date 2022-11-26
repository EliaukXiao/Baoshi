#include "CRankDlg.h"
#include "ui_CRankDlg.h"
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
CRankDlg::CRankDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CRankDlg)
{
    ui->setupUi(this);
    if (!QSqlDatabase::drivers().contains("QSQLITE")){
            QMessageBox::critical(this, "Unable to load database", "This demo needs the SQLITE driver");
        }
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    crank = CRankLogic::getInstance();
    time=new int[10];
    score=new int[10];
    name = new QString[10];
    init();
    fill();
}

CRankDlg::~CRankDlg()
{
    delete ui;
}
void CRankDlg::init(){
    for(int i=0;i<10;i++){
        time[i]=0;
        score[i]=0;
        name[i]="";
    }
}

void CRankDlg::fill(){
    crank.getAll(name,time,score);
    for(int i = 0;i<10;i++)
    {
        if(name[i]!=""&&score[i]!=0){
            ui->tableWidget->setItem(i+1,0,new QTableWidgetItem(QString::number(i+1)));
            ui->tableWidget->setItem(i+1,1,new QTableWidgetItem(name[i]));
            ui->tableWidget->setItem(i+1,2,new QTableWidgetItem(QString::number(time[i])+"s"));
            ui->tableWidget->setItem(i+1,3,new QTableWidgetItem(QString::number(score[i])));
            ui->tableWidget->item(i+1,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            ui->tableWidget->item(i+1,1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            ui->tableWidget->item(i+1,2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            ui->tableWidget->item(i+1,3)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
        else{
            ui->tableWidget->setItem(i+1,0,new QTableWidgetItem("-"));
            ui->tableWidget->setItem(i+1,1,new QTableWidgetItem("-"));
            ui->tableWidget->setItem(i+1,2,new QTableWidgetItem("-"));
            ui->tableWidget->setItem(i+1,3,new QTableWidgetItem("-"));
            ui->tableWidget->item(i+1,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            ui->tableWidget->item(i+1,1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            ui->tableWidget->item(i+1,2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            ui->tableWidget->item(i+1,3)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }
}

void CRankDlg::on_pushButton_clicked()
{
    crank.clear();
    init();
    fill();
    qApp->processEvents();
}

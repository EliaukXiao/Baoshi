#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <CGameDlg.h>
#include <CNameDlg.h>
#include <CRankDlg.h>
#include <CHelpDlg.h>
#include<CAboutDlg.h>
#include<CSetDlag.h>
//#include<CShopDlg.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class CBejeweledDlg : public QWidget
{
    Q_OBJECT

public:

    CBejeweledDlg(QString name,QWidget *parent = nullptr);
    ~CBejeweledDlg();
    CGameDlg *GameDlg;
    CGameDlg *GameDlg2;
    CNameDlg *NameDlg;
    CRankDlg *RankDlg;
    CHelpDlg *HelpDlg;
    CAboutDlg *AboutDlg;
    CSetDlag *SetDlag;


private slots:
    void on_pushButton_clicked();

    void on_pushButton_paihangbang_clicked();

    void on_pushButton_bangzhu_clicked();

    void on_pushButton_guanyu_clicked();

    void open();


    void on_pushButton_paihangbang_2_clicked();

    void on_pushButton_2_clicked();

    //void on_pushButton_3_clicked();

private:
    Ui::Widget *ui;
    QString name;
};
#endif // WIDGET_H

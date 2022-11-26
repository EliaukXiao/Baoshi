#ifndef CMENUDLG_H
#define CMENUDLG_H

#include <QWidget>
#include <CSetDlag.h>
#include <QTimer>
#include <QCloseEvent>
//#include<CBejeweledDlg.h>
namespace Ui {
class CMenuDlg;
}
class CSetDlag;
class CMenuDlg : public QWidget
{
    Q_OBJECT

public:
    explicit CMenuDlg(QWidget *parent = nullptr);
    ~CMenuDlg();
    CSetDlag *SetDlg;
    CSetDlag *getSet();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_shezhiyouxi_clicked();

    void on_pushButton_fanhuiyouxi_clicked();

    void on_pushButtochongxinyouxin__clicked();

    void on_pushButton_tuichuyouxi_clicked();

    void change11();
    void change12();
    void change13();

protected:
     void closeEvent(QCloseEvent *event);


signals:
    void sendsignal();
    void sendsignal1();
    void sendquitsignal();
    void openzhucaidansignal();
    void change1signal();
    void change2signal();
    void change3signal();

private:
    Ui::CMenuDlg *ui;
    bool SetInitFlag =false;
//    CBejeweledDlg *BejeweledDlg;
};

#endif // CMENUDLG_H

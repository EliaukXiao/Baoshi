#ifndef CRANKDLG_H
#define CRANKDLG_H

#include <QWidget>
#include "CRankLogic.h"
namespace Ui {
class CRankDlg;
}

class CRankDlg : public QWidget
{
    Q_OBJECT

public:
    explicit CRankDlg(QWidget *parent = nullptr);
    ~CRankDlg();
    void fill();
    void init();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CRankDlg *ui;
    CRankLogic crank;
    int *rank;
    int *time;
    int *score;
    QString *name;
};

#endif // CRANKDLG_H

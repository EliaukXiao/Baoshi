#ifndef CREGIST_H
#define CREGIST_H

#include <QWidget>
#include "CRankLogic.h"

namespace Ui {
class CRegist;
}

class CRegist : public QWidget
{
    Q_OBJECT

public:
    explicit CRegist(QWidget *parent = nullptr);
    ~CRegist();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::CRegist *ui;
    CRankLogic CRank;
};

#endif // CREGIST_H

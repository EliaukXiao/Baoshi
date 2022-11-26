#ifndef CNAMEDLG_H
#define CNAMEDLG_H

#include <QWidget>

namespace Ui {
class CNameDlg;
}

class CNameDlg : public QWidget
{
    Q_OBJECT

public:
    explicit CNameDlg(QWidget *parent = nullptr);
    ~CNameDlg();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CNameDlg *ui;
    QString name;

};

#endif // CNAMEDLG_H

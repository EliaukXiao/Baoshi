#ifndef CHELPDLG_H
#define CHELPDLG_H

#include <QWidget>

namespace Ui {
class CHelpDlg;
}

class CHelpDlg : public QWidget
{
    Q_OBJECT

public:
    explicit CHelpDlg(QWidget *parent = nullptr);
    ~CHelpDlg();

private:
    Ui::CHelpDlg *ui;
};

#endif // CHELPDLG_H

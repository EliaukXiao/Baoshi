#ifndef CABOUTDLG_H
#define CABOUTDLG_H

#include <QWidget>

namespace Ui {
class CAboutDlg;
}

class CAboutDlg : public QWidget
{
    Q_OBJECT

public:
    explicit CAboutDlg(QWidget *parent = nullptr);
    ~CAboutDlg();

private:
    Ui::CAboutDlg *ui;
};

#endif // CABOUTDLG_H

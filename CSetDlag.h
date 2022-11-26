#ifndef CSETDLAG_H
#define CSETDLAG_H
#include <CMusicPlayer.h>
#include <QWidget>
#include <QFileDialog>
#include <QFileInfo>
#include <QImage>
#include <QPainter>
#include <QAbstractButton>



class CGameDlg;
namespace Ui {
class CSetDlag;
}

class CSetDlag : public QWidget
{
    Q_OBJECT

public:
    explicit CSetDlag(QWidget *parent = nullptr);
    ~CSetDlag();
    CMusicPlayer *cmusicplayer;
    QString OpenFilePath;
    CMusicPlayer *getMusicPlayer();
    void OpenMusic();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_beijingtupian_clicked();

    void on_pushButton_zhutiQueding_clicked();

    void on_pushButton_baoshitupian_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_tupianMoren_clicked();

    void on_radioButton_musicMoren_clicked();

    void on_radioButton_musicChange_clicked();

    void on_pushButton_yanma_clicked();

    void on_pushButton_zhutiQuxiao_clicked();

    void on_buttonBox_clicked(QAbstractButton *button);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_pushButton_openMp3File_clicked();

private:
    Ui::CSetDlag *ui;
    void OpenImg(QWidget*);
    CGameDlg *Gamedlg;
    QImage imgbaoshi[8];
    bool MusicInitFlag = false;

signals:
    void change1signal2();
    void change2signal2();
    void change3signal2();
};

#endif // CSETDLAG_H

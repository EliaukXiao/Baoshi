#include "CSetDlag.h"
#include "ui_CSetDlag.h"
#include <CGameDlg.h>
CSetDlag::CSetDlag(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CSetDlag)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    if(ui->radioButton_musicMoren->isChecked()){
        ui->lineEdit_musicPath->setEnabled(false);
        ui->pushButton_openMp3File->setEnabled(false);
    }
    if(MusicInitFlag ==false){
    cmusicplayer = new CMusicPlayer;
    MusicInitFlag =true;
    }

    QImage* img=new QImage;
    img->load("..\\BSMZproject\\sucai\\2.png");
    ui->label->setPixmap(QPixmap::fromImage(*img));
    img->load("..\\BSMZproject\\sucai2\\2.png");
    ui->label_2->setPixmap(QPixmap::fromImage(*img));
    img->load("..\\BSMZproject\\sucai3\\2.png");
    ui->label_3->setPixmap(QPixmap::fromImage(*img));
    ui->radioButton->setChecked(true);

}

CSetDlag::~CSetDlag()
{
    delete ui;
}


void CSetDlag::OpenImg(QWidget* mainDlg)
{
    QString OpenFile, OpenFilePath;
    QImage image;
    //打开文件夹中的图片文件
    OpenFile = QFileDialog::getOpenFileName(this,
                                              "Please choose an image file",
                                              "",
                                              "Image Files(*.jpg *.png *.bmp *.pgm *.pbm);;All(*.*)");
    mainDlg->setAutoFillBackground(true);
    QPixmap pixmap;
    if( OpenFile != "" )
    {
        if( image.load(OpenFile) )
        {
            pixmap = QPixmap::fromImage(image).scaled(mainDlg->size());
            QPalette palette;
            palette.setBrush(QPalette::Window, QBrush(pixmap));
            mainDlg->setPalette(palette);
            mainDlg->update();

        }
    }

    //显示所示图片的路径
    QFileInfo OpenFileInfo;
    OpenFileInfo = QFileInfo(OpenFile);
    OpenFilePath = OpenFileInfo.filePath();

}
//打开音乐文件
void CSetDlag::OpenMusic()
{
    QString OpenFile;

    //打开文件夹中的音乐文件
    OpenFile = QFileDialog::getOpenFileName(this,
                                              "Please choose an mp3 file",
                                              "",
                                              "Image Files(*.mp3);;All(*.*)");

    //显示音乐的路径
    QFileInfo OpenFileInfo;
    OpenFileInfo = QFileInfo(OpenFile);
    OpenFilePath = OpenFileInfo.filePath();
    ui->lineEdit_musicPath->setText(OpenFilePath);
    //musicList.bgm(OpenFilePath);

}

//更换背景图片按钮
void CSetDlag::on_pushButton_beijingtupian_clicked()
{
   OpenImg(Gamedlg);
}

//确定按钮
void CSetDlag::on_pushButton_zhutiQueding_clicked()
{
    //Gamedlg->show();
    if(ui->radioButton->isChecked()){
        emit change1signal2();
    }
    else if(ui->radioButton_2->isChecked()){
        emit change2signal2();
    }
    else if(ui->radioButton_3->isChecked()){
        emit change3signal2();
    }
    this->close();
}

//打开宝石图片文件 浏览按钮
void CSetDlag::on_pushButton_baoshitupian_clicked()
{
    OpenImg(Gamedlg);
}

//打开音乐文件按钮
void CSetDlag::on_pushButton_clicked()
{
//    OpenMusic(Gamedlg);
}

//图片默认按钮点击
void CSetDlag::on_radioButton_tupianMoren_clicked()
{

}
//图片自定义按钮点击
void CSetDlag::on_radioButton_2_clicked()
{
}


//背景音乐默认按钮
void CSetDlag::on_radioButton_musicMoren_clicked()
{
    ui->lineEdit_musicPath->setEnabled(false);
    ui->pushButton_openMp3File->setEnabled(false);
}

//背景音乐自定义按钮
void CSetDlag::on_radioButton_musicChange_clicked()
{
    ui->lineEdit_musicPath->setEnabled(true);
    ui->pushButton_openMp3File->setEnabled(true);
}

//掩码图片点击
void CSetDlag::on_pushButton_yanma_clicked()
{
    OpenImg(Gamedlg);
}
//图片取消点击按钮
void CSetDlag::on_pushButton_zhutiQuxiao_clicked()
{
    this->close();
}

void CSetDlag::on_buttonBox_clicked(QAbstractButton *button)
{
}

CMusicPlayer* CSetDlag::getMusicPlayer(){
    if(MusicInitFlag ==false){
        cmusicplayer = new CMusicPlayer;
        MusicInitFlag =true;
    }
    return cmusicplayer;
}


void CSetDlag::on_buttonBox_accepted()
{
    if(ui->radioButton_musicMoren->isChecked())
        cmusicplayer->bgm(1, OpenFilePath);  //点击确定之后开始播放音乐
    else if(ui->radioButton_musicChange->isChecked())
        cmusicplayer->bgm(2, OpenFilePath);
    this->close();
}

void CSetDlag::on_buttonBox_rejected()
{
    this->close();
}

void CSetDlag::on_pushButton_openMp3File_clicked()
{
    OpenMusic();
}

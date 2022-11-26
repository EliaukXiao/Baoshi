#include "CMusicplayer.h"
#include<QMessageBox>
#include<QFileDialog>
#include<QMessageBox>
CMusicPlayer::CMusicPlayer()
{
}

void CMusicPlayer::bgm(int type, QString OpenFilePath)
{
    QMediaPlaylist *gameList = new QMediaPlaylist;//创建播放列
    if(type==1) //设置为默认音乐
        gameList->addMedia(QUrl("../BSMZproject/music/背景音乐.mp3"));//添加音乐
    else{
             gameList->addMedia(QUrl(OpenFilePath));
        }

    gameList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);//循环播放
    QObject::connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player->setPlaylist(gameList);
    player->setVolume(yinliang);
    player->play();
}


void CMusicPlayer::disapperSound()
{
    QMediaPlayer *player1 = new QMediaPlayer;
    QObject::connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player1->setMedia(QUrl::fromLocalFile("../BSMZproject/music/消子音效.mp3"));     //添加音乐路径
    player1->setVolume(yinliang);
    player1->play();
}

void CMusicPlayer::disapperSound1()
{
    QMediaPlayer *player1 = new QMediaPlayer;
    QObject::connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player1->setMedia(QUrl::fromLocalFile("../BSMZproject/music/great.mp3"));     //添加音乐路径
    player1->setVolume(yinliang);
    player1->play();


}

void CMusicPlayer::disapperSound2()
{
    QMediaPlayer *player1 = new QMediaPlayer;
    QObject::connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player1->setMedia(QUrl::fromLocalFile("../BSMZproject/music/excellent.mp3"));     //添加音乐路径
    player1->setVolume(yinliang);
    player1->play();


}

void CMusicPlayer::disapperSound3()
{
    QMediaPlayer *player1 = new QMediaPlayer;
    QObject::connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player1->setMedia(QUrl::fromLocalFile("../BSMZproject/music/不敢相信.mp3"));     //添加音乐路径
    player1->setVolume(yinliang);
    player1->play();
}

void CMusicPlayer::disapperSound4()
{
    QMediaPlayer *player1 = new QMediaPlayer;
    QObject::connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player1->setMedia(QUrl::fromLocalFile("../BSMZproject/music/十字音效.mp3"));     //添加音乐路径
    player1->setVolume(yinliang);
    player1->play();
}
void CMusicPlayer::disapperSound5()
{
    QMediaPlayer *player1 = new QMediaPlayer;
    QObject::connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player1->setMedia(QUrl::fromLocalFile("../BSMZproject/music/炸弹音效.mp3"));     //添加音乐路径
    player1->setVolume(yinliang);
    player1->play();
}
void CMusicPlayer::disapperSound6()
{
    QMediaPlayer *player1 = new QMediaPlayer;
    QObject::connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player1->setMedia(QUrl::fromLocalFile("../BSMZproject/music/魔法鸟音效.mp3"));     //添加音乐路径
    player1->setVolume(yinliang);
    player1->play();
}


void CMusicPlayer::viectorySound()
{
    player->stop();
    QMediaPlayer *player1 = new QMediaPlayer;
    connect(player1, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player1->setMedia(QUrl::fromLocalFile(""));     //添加音乐路径
    player1->setVolume(yinliang);
    player1->play();
}

void CMusicPlayer::defeatSound()
{
    player->stop();
    QMediaPlayer *player1 = new QMediaPlayer;
    connect(player1, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player1->setMedia(QUrl::fromLocalFile("../BSMZproject/music/游戏失败音效.mp3"));     //添加音乐路径
    player1->setVolume(yinliang);
    player1->play();

}

void CMusicPlayer::yinlainglow(){
    yinliang = yinliang-2;
        player->setVolume(yinliang);
}

void CMusicPlayer::yinlianghigh(){
    yinliang = yinliang+2;
        player->setVolume(yinliang);
}

void CMusicPlayer::jingyin(){
    temp = yinliang;
    yinliang = 0;
        player->setVolume(yinliang);
}

void CMusicPlayer::huifushengyin(){
    yinliang = temp;
        player->setVolume(yinliang);
}

void CMusicPlayer::bgmstart(){
    player->play();
}

void CMusicPlayer::bgmstop(){
    player->stop();
}

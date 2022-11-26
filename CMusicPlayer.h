#ifndef CMUSICPLAYER_H
#define CMUSICPLAYER_H
//#include "CConfig.h"
#include "QtMultimedia/qmediaplayer.h"
#include "QtMultimedia/qmediaplaylist.h"
class CMusicPlayer:QObject
{
public:
    CMusicPlayer();
    void bgm(int type,QString OpenFilePath);      //背景音乐
    void beginSound();       //游戏开始音乐
    void disapperSound();    //消子音乐
    void disapperSound1();
    void disapperSound2();
    void disapperSound3();
    void disapperSound4();
    void disapperSound5();
    void disapperSound6();
    void moveSound();        //移动音乐
    void viectorySound();    //胜利音乐
    void defeatSound();      //失败音乐
    void yinlainglow();
    void yinlianghigh();
    void jingyin();
    void huifushengyin();
    void bgmstart();
    void bgmstop();


private:
        QMediaPlayer *player = new QMediaPlayer;
        int yinliang =30;
        int temp = 30;

};

#endif // CMUSICPLAYER_H

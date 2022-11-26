#include "crankdao.h"
#include "iostream"

CRankDao::CRankDao()
{
    player.strName = "";
    player.nTime = 123;
    player.nGrade = 16456;
    topPlayer[10] = player;

    readTop();
}

void swap(RANKINFO *a, RANKINFO *b) {
    RANKINFO temp;
    temp = *b;
    *b = *a;
    *a = temp;
}

void CRankDao::readTop(){
    QString path = "C:/Users/MACHENIKE/Desktop/Rank.txt";
    QFile file(path);
    QTextStream stream(&file);
    if(file.open(QIODevice::ReadOnly)) {
        for (int i = 0; i < 10; i++) {
            stream>>topPlayer[i].strName;
            stream>>topPlayer[i].nTime;
            stream>>topPlayer[i].nGrade;
            stream>>topPlayer[i].nRank;
        }
    }
}

void CRankDao::saveTop(){
    bool flag = 1;
    for (int i = 0; flag; i++) {
        flag = 0;
        for (int j = 11-1; j>=i+1; j--) {
            if(topPlayer[j].integral > topPlayer[j-1].integral) {
                swap(&topPlayer[j], &topPlayer[j-1]);
                flag = 1;
            }
        }
    }

    QString path = "C:/Users/MACHENIKE/Desktop/Rank.txt";
    QFile file(path);
    QTextStream out(&file);
    for(int i = 0; i < 10; i++) {
        topPlayer[i].nRank = i+1;
        out<<topPlayer[i].nRank<<" "<<topPlayer[i].playerName<<" "<<topPlayer[i].timeLast<<" "<<topPlayer[i].integral<<endl;
    }
}

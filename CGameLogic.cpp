#include "CGameLogic.h"
#include <QTime>
#include <QDebug>
bool CGameLogic::Exist(int x,int y){
    if(x>=0&&x<row&&y>=0&&y<column){
        return true;
    }
    return false;
}
void CGameLogic::swap(int i,int j,int x,int y,int **Map){
    int temp = Map[i][j];
    Map[i][j]=Map[x][y];
    Map[x][y]=temp;
}
bool CGameLogic::isLine(int x,int y,int **Map){
    if(Exist(x,y+2)){//横向成线
        if(Map[x][y]==Map[x][y+1]&&Map[x][y]==Map[x][y+2]){
            return true;
        }
    }
    if(Exist(x,y+1)&&Exist(x,y-1)){//横向成线
        if(Map[x][y]==Map[x][y+1]&&Map[x][y]==Map[x][y-1]){
            return true;
        }
    }
    if(Exist(x,y-2)){//横向成线
        if(Map[x][y]==Map[x][y-1]&&Map[x][y]==Map[x][y-2]){
            return true;
        }
    }
    if(Exist(x+2,y)){//纵向成线
        if(Map[x][y]==Map[x+1][y]&&Map[x][y]==Map[x+2][y]){
            return true;
        }
    }
    if(Exist(x+1,y)&&Exist(x-1,y)){//纵向成线
        if(Map[x][y]==Map[x+1][y]&&Map[x][y]==Map[x-1][y]){
            return true;
        }
    }
    if(Exist(x-2,y)){//纵向成线
        if(Map[x][y]==Map[x-1][y]&&Map[x][y]==Map[x-2][y]){
            return true;
        }
    }
    return false;//未成线
}
bool CGameLogic::isAdjacent(int x,int y,int i,int j){
    if(x==i){
        if(y-j==1||j-y==1){
            return true;
        }
    }
    if(y==j){
        if(i-x==1||x-i==1){
            return true;
        }
    }
    return false;
}
bool CGameLogic::Try(int i,int j,int x,int y,int **Map){
    if(Exist(i+x,j+y)){
        swap(i,j,i+x,j+y,Map);
        if(isLine(i,j,Map)){
            swap(i,j,i+x,j+y,Map);
            return true;
        }
        swap(i,j,i+x,j+y,Map);
    }
    return false;
}

void CGameLogic::BulidMap(int **Map){
    qsrand(time(NULL));
    do{
        for(int i=0;i<row;i++){
            for(int j=0;j<column;j++){
                Map[i][j]=qrand() % kind+1;
            }
        }
    }while(CanEmilinate(Map)||!isLive(Map));

}
bool CGameLogic::change(int i,int j,int x,int y,int **Map){
    if(isAdjacent(i,j,x,y)){
        swap(i,j,x,y,Map);
        if(isLine(i,j,Map)||isLine(x,y,Map)){
            return true;
        }
        else{
           swap(i,j,x,y,Map);
           return false;
        }
    }
    return false;
}
bool CGameLogic::isLive(int **Map){
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            x1=i;
            y1=j;
            if(Try(i,j,1,0,Map)){
                x2=i+1;
                y2=j;
                return true;
            }
            if(Try(i,j,-1,0,Map)){
                x2=i-1;
                y2=j;
                return true;
            }
            if(Try(i,j,0,1,Map)){
                x2=i;
                y2=j+1;
                return true;
            }
            if(Try(i,j,0,-1,Map)){
               x2=i;
               y2=j-1;
               return true;
            }
        }
    }
    return false;
}
bool CGameLogic::CanEmilinate(int **Map){
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            if(isLine(i,j,Map)){
                return true;
            }
        }
    }
    return false;
}
int CGameLogic::Emilinate(int **Map,int &score){
    bool line[row][column];
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
           line[i][j]=false;
        }
    }
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            if(Exist(i,j+2)){//横向成线 标记
                if(Map[i][j]==Map[i][j+1]&&Map[i][j]==Map[i][j+2]){
                    line[i][j]=true;
                    line[i][j+1]=true;
                    line[i][j+2]=true;
                }
            }
            if(Exist(i+2,j)){//纵向成线 标记
                if(Map[i][j]==Map[i+1][j]&&Map[i][j]==Map[i+2][j]){
                    line[i][j]=true;
                    line[i+1][j]=true;
                    line[i+2][j]=true;
                }
            }
        }
    }
    int count=0;
    for(int i=0;i<row;i++){//消除
        for(int j=0;j<column;j++){
            if(line[i][j]){
                Map[i][j]=0;
                count++;
            }
        }
    }
    score+=count*10+count*count;
    return  count;
}
bool CGameLogic::MoveDown(int **Map){
    bool change = false;
    for(int i=0;i<row;i++){
        for(int j=column-1;j>=0;j--){
            if(Map[j][i]!=0){
                int temp =j;
                if(Exist(temp+1,i)&&Map[temp+1][i]==0){
                    swap(temp,i,temp+1,i,Map);
                    //temp++;
                   change = true;
                }
            }
        }
    }
    return change;
}
void CGameLogic::replenish(int **Map){
    qsrand(time(NULL));
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            if(Map[i][j]==0){
                Map[i][j]=qrand() % kind+1;
            }
        }
    }
}
void CGameLogic::Hint(int &x,int &y,int &a,int &b,int **Map){
    isLive(Map);
    x=x1;
    y=y1;
    a=x2;
    b=y2;
}



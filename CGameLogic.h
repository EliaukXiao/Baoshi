#ifndef CGAMELOGIC_H
#define CGAMELOGIC_H
#include <ctime>
class CGameLogic{
    int x1,y1,x2,y2;
    int row=0;
    int column=0;
    int kind=3;
public:
    bool isLine(int x,int y,int **Map);//是否成线
    void swap(int i,int j,int x,int y,int **Map);//交换
    bool isAdjacent(int x,int y,int i,int j);//判断是否邻接
    bool Exist(int x,int y);//判断是否越界
    bool Try(int i,int j,int x,int y,int **Map);//判断该子是否可消
    bool CanEmilinate(int **Map);//全图是否可消
    bool MoveDown(int **Map);//下移
    void replenish(int **Map);//随机补充
    int Emilinate(int **Map,int &score);//消子操作+分数计算
public:
    CGameLogic(int row,int column,int kind){//指定大小
        this->row=row;
        this->column=column;
        this->kind=kind;
    }
    bool isLive(int **Map);//地图是否为“死”地图
    void BulidMap(int **Map);//随机地图生成[8][8]
    bool change(int i,int j,int x,int y,int **Map);//交换判断
    void Hint(int &x,int &y,int &a,int &b,int **Map);//提示,得到交换后可以消子的两个相邻坐标
};

#endif // CGAMELOGIC_H

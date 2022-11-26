#ifndef CRANKLOGIC_H
#define CRANKLOGIC_H
#include <QString>
#include <QSqlDatabase>
#include <QApplication>
#include <QSqlQuery>
class CRankLogic{
public:
    int rank;
    QString name;
    int time;
    int score;
    QString password;
    QSqlDatabase db;
public:
    CRankLogic();
    ~CRankLogic();
    static CRankLogic& getInstance() {
            static CRankLogic instance;
            return instance;
        }
    friend class CGameDlg;
    void AddDatabase();
    void Insert(QString name,int time,int score,QString password);//插入
    void Delete(QString name);//删除
    void Modif(int time,int score,QString name);//修改
    bool Inqure(QString name);//查询
    void getAll(QString *name,int *time ,int *score);
    void clear();
};

#endif // CRANKLOGIC_H

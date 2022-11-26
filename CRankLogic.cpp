#include "CRankLogic.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQueryModel>
CRankLogic::CRankLogic(){
    rank = 0;
    time = 0;
    score = 0;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QApplication::applicationDirPath()+"/scooters.dat");    //如果本目录下没有该文件,则会在本目录下生成,否则连接该文件
     if (!db.open()) {

        qDebug()<<"error"<<db.lastError().text();
     }
     QSqlQuery query(db);
     //判断表是否存在
     if(!query.exec("select count(*) from sqlite_master where type = 'table' name= RankList")){
         query.exec("CREATE TABLE RankList ("
                            "name varchar(40),"
                            "time int,"
                            "score int,"
                            "password varchar(40))");
     }
}
CRankLogic::~CRankLogic(){
    db.close();
}
void CRankLogic::Insert(QString name,int time,int score,QString password){
    QSqlQuery query(db);
    QString str;   
        str = QString("insert into RankList(name,time,score,password) values('%1','%2','%3','%4')")
                .arg(name).arg(time).arg(score).arg(password);
        query.exec(str);

}
void CRankLogic::Delete(QString name){
    QSqlQuery query(db);
    QString str = QString("delete from RankList where name = '%1'").arg(name);
    query.exec(str);
}
void CRankLogic::Modif(int time,int score,QString updateName){//将名字为updateName的数据修改
    QSqlQuery query(db);
    Inqure(updateName);
    qDebug()<<this->score;
    if(this->score < score){
        QString str = QString("update Ranklist set time = '%1',score = '%2' where name = '%3'")
            .arg(time).arg(score).arg(updateName);
        query.exec(str);
    }
}
bool CRankLogic::Inqure(QString name){
    QSqlQuery query(db);
    QString str = QString("select *from RankList where name = '%1'").arg(name);
    query.exec(str);
    this->name="";
    while(query.next()){
        this->name=query.value(0).toString();
        this->time=query.value(1).toInt();
        this->score=query.value(2).toInt();
        this->password=query.value(3).toString();
    }
    if(this->name == ""){
        return false;
    }
    return true;
}
void CRankLogic::getAll(QString *name,int *time ,int *score){
     QSqlQuery query(db);
     query.exec("select * from RankList ORDER BY score DESC,time DESC");
    int i=0;
    while(query.next())
    {
        name[i]=query.value(0).toString();
        time[i]=query.value(1).toInt();
        score[i]=query.value(2).toInt();
        i++;
        if(i>=10)
            break;
    }
}

void CRankLogic::clear(){
    QSqlQuery query(db);
    query.exec("delete from RankList");
}

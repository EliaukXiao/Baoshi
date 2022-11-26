#ifndef CRANKDAO_H
#define CRANKDAO_H
#include "Global.h"

class CRankDao
{
public:
    CRankDao();
    RANKINFO player;
    RANKINFO topPlayer[11];

    void readTop();
    void saveTop();
};

#endif // CRANKDAO_H

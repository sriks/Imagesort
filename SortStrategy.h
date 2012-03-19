#ifndef SORTSTRATEGY_H
#define SORTSTRATEGY_H
#include <QList>

typedef QList<ulong> ImageIdList;
class SortStrategy
{
public:
    SortStrategy();
    virtual ~SortStrategy();

public:
    virtual ImageIdList sort(ImageIdList input)=0;
};

#endif // SORTSTRATEGY_H

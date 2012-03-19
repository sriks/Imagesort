#ifndef QSORT_H
#define QSORT_H
#include "SortStrategy.h"

// Uses qSort() for sorting
class QSort : public SortStrategy
{
public:
    QSort();
    // from SortStrategy
    ImageIdList sort(ImageIdList input);
};

#endif // QSORT_H

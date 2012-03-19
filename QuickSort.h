#ifndef QUICKSORT_H
#define QUICKSORT_H
#include "SortStrategy.h"

// standard c++ quick sort
class QuickSort : public SortStrategy
{
public:
    QuickSort();
    ImageIdList sort(ImageIdList input);
};

#endif // QUICKSORT_H

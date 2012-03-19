#include <QDebug>
#include <algorithm>
#include "QuickSort.h"

QuickSort::QuickSort() {}

ImageIdList QuickSort::sort(ImageIdList input) {
    qDebug()<<Q_FUNC_INFO;
    ImageIdList ip = input;
    // standard c++ quick sort
    std::sort(input.begin(),input.end());
    return ip;
}

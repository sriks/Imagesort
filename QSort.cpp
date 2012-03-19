#include <QDebug>
#include "QSort.h"

QSort::QSort() {}

ImageIdList QSort::sort(ImageIdList input) {
    qDebug()<<Q_FUNC_INFO;
    ImageIdList ip = input;
    qSort(ip.begin(),ip.end());
    return ip;
}

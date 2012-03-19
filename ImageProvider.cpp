
/*!
  \class ImageProvider
  \brief This class acts as the image provider for qml.
  **/

#include <QMap>
#include <QDebug>
#include <QImage>
#include <QRgb>
#include <QColor>
#include "ImageProvider.h"
#include "QSort.h"
#include "QuickSort.h"
#define DEBUG_SAVE_IMAGES

const int ROWS = 3;
const int COLUMNS = 4;
const QString QSORT ("qsort");
const QString QUICKSORT("quicksort");

class ImageProviderPrivate {
public:
    int rows;
    int columns;
    int imgWidth;
    int imgHeight;
    int blockWidth;
    int blockHeight;
    QString imgSrc;
    SortStrategy* selectedSort;
    ImageIdList sortedKeys;
    QMap<ulong,QImage> imageBlocks; // key is color sampling value
                                    // Since we use a map the keys are already sorted :)
    ImageProviderPrivate():selectedSort(NULL) {
        rows = 3;
        columns = 4;
    }
    ~ImageProviderPrivate() {
        if(selectedSort)
            delete selectedSort;
    }
    void reset() {
        imageBlocks.clear();
        sortedKeys.clear();
        imgSrc.clear();
    }
};

ImageProvider::ImageProvider(QObject *parent) :
    QObject(parent),
    QDeclarativeImageProvider(QDeclarativeImageProvider::Image) {
    d = new ImageProviderPrivate;
    this->setAlgorithm(QSORT);

}

ImageProvider::~ImageProvider() {
    delete d;
}

QImage ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize) {
    // TODO: Memory consumption can be further improved by not storing the images,
    // but extracting the intrested part from source here itself
    int index = id.toInt();
    // look for index in sorted keys and return image from blocks
    int key = d->sortedKeys.at(index);
    return d->imageBlocks.value(key);
}

/*!
  Sets image source to be sorted.
  **/
void ImageProvider::setImageSource(QString src) {
    QImage img(src);
    if(img.isNull()) {
        qWarning()<<Q_FUNC_INFO<<"Invalid image:"<<src;
        return;
    }

    d->reset();
    d->imgSrc = src;

    // break image into blocks
    d->imgWidth = img.width();
    d->imgHeight = img.height();
    d->blockWidth = d->imgWidth/d->columns;
    d->blockHeight = d->imgHeight/d->rows;

    for(int row=0;row<d->rows;++row) {
        for(int col=0;col<d->columns;++col) {
            int x = d->blockWidth*col;
            int y = d->blockHeight*row;
            QImage block(img.copy(x,y,d->blockWidth,d->blockHeight));
            if(block.isNull()) {
                qDebug()<<Q_FUNC_INFO<<"Block at "<<x<<","<<y<<" is invalid";
                continue;
            }

            // get color sample for block
            int colorSample = 0;
            for(int i=0;i<d->blockHeight;++i) {
                QRgb* line = (QRgb*)block.constScanLine(i);
                if(NULL == line)
                    continue;
                for(int j=0;j<d->blockWidth;++j) {
                    line += j;
                    if(line)
                      colorSample += QColor(*line).red();
                }
                colorSample = colorSample/d->blockWidth; // avg the sample
            }
            d->imageBlocks.insertMulti(colorSample,block);

#if defined(DEBUG_SAVE_IMAGES)
            // test
            //qDebug()<<Q_FUNC_INFO<<x<<","<<y<<" block is NULL:"<<block.isNull();
            QString fn = QString().setNum(x) + "-" + QString().setNum(y);
            if(!block.isNull()) {
                block.save(fn,"PNG",100);
            }
            // test
#endif
        }
    }
}

/*!
  Returns image source
  **/
QString ImageProvider::imageSource() const {
    return d->imgSrc;
}

int ImageProvider::imageWidth() const {
    return d->imgWidth;
}

int ImageProvider::imageHeight() const {
    return d->imgHeight;
}

/*!
  Returns block width
  **/
int ImageProvider::blockWidth() const {
    return d->blockWidth;
}

/*!
  Returns block height
  **/
int ImageProvider::blockHeight() const {
    return d->blockHeight;
}

/*!
  Returns block count
  **/
int ImageProvider::blocksCount() const {
    return d->imageBlocks.size();
}

/*!
  Sets sorting algorithm \a algo
  **/
void ImageProvider::setAlgorithm(QString algo) {
    if(d->selectedSort)
        delete d->selectedSort;
    if(QSORT == algo)
        d->selectedSort = new QSort;
    else if(QUICKSORT == algo)
        d->selectedSort = new QuickSort;
}

/*!
  Sorts image with the specified algo.
  **/
void ImageProvider::sort() {
    if(d->selectedSort) {
        d->sortedKeys = d->selectedSort->sort(d->imageBlocks.keys());
        emit imageSorted();
    }
}

/*!
  Returns predefined number of rows
  **/
int ImageProvider::rows() const {
    return d->rows;
}

/*!
  Returns predefined number of columns
  **/
int ImageProvider::columns() const {
    return d->columns;
}

// eof

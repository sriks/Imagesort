#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QDeclarativeImageProvider>
#include <QImage>

class ImageProviderPrivate;
class ImageProvider : public QObject,
                      public QDeclarativeImageProvider
{
    Q_OBJECT
public:
    explicit ImageProvider(QObject *parent = 0);
    ~ImageProvider();
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
signals:
    void imageSorted();
public slots:
    int rows() const;
    int columns() const;
    void setImageSource(QString src);
    QString imageSource() const;
    int imageWidth() const;
    int imageHeight() const;
    int blockWidth() const;
    int blockHeight() const;
    int blocksCount() const;
    void setAlgorithm(QString algo);
    void sort();
private:
    ImageProviderPrivate* d;
};

#endif // IMAGEPROVIDER_H

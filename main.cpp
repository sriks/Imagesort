#include <QtGui/QApplication>
#include <QtDeclarative>
#include "qmlapplicationviewer.h"
#include "ImageProvider.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    ImageProvider engine;
    QmlApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("imageengine",(QObject*)&engine);
    viewer.engine()->addImageProvider(QLatin1String("sortedimages"),&engine);
    viewer.setMainQmlFile(QLatin1String("qml/Imagesort/main.qml"));
    viewer.showExpanded();
    return app->exec();
}

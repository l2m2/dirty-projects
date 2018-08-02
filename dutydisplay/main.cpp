#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "dutymodel.h"
#include "filedownloader.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    DutyModel model;

    FileDownloader downloader;

    QQmlApplicationEngine engine;
#ifdef QT_DEBUG
    engine.rootContext()->setContextProperty("debug", true);
#else
    engine.rootContext()->setContextProperty("debug", false);
#endif
    engine.rootContext()->setContextProperty("dutyModel", &model);
    engine.rootContext()->setContextProperty("downloader", &downloader);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

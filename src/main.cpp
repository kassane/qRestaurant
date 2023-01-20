#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qqml.h>
#include <restaurant.hpp>

int main(int argc, char *argv[])
{
#if QT_VERSION >= 0x50601
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    Restaurant rest;

    QQmlApplicationEngine engine;
    qmlRegisterType<Restaurant>("qt.restaurant", 1, 0, "Restaurant");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "cnetworker.h"
#include "QDebug"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qmlRegisterSingletonType<CNetWorker>("Qt.IM.Network", 1, 0, "NetApi", [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        CNetWorker *example = new CNetWorker();
        return example;
    });


    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/DialogLogin.qml")));
    if (engine.rootObjects().isEmpty()){
        return -1;
    }

    return app.exec();
}




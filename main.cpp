#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include <QFileInfo>
#include "databasemanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    DatabaseManager dbManager;

    engine.rootContext()->setContextProperty("dbManager", &dbManager);

    // Get application directory path
    QString appDirPath = QCoreApplication::applicationDirPath();

    // Construct QML file path with multiple fallback strategies
    QStringList possiblePaths = {
        appDirPath + "/Main.qml",
        appDirPath + "/../Main.qml",
        QDir::currentPath() + "/Main.qml",
        QDir::currentPath() + "/../Main.qml",
        QFileInfo(__FILE__).absolutePath() + "/Main.qml"
    };

    QUrl url;
    for (const QString& path : possiblePaths) {
        QFileInfo fileInfo(path);
        if (fileInfo.exists()) {
            url = QUrl::fromLocalFile(fileInfo.absoluteFilePath());
            break;
        }
    }

    if (url.isEmpty()) {
        qDebug() << "Could not find Main.qml in any expected locations";
        return -1;
    }

    qDebug() << "Loading QML from:" << url.toString();

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [&url](QObject* object, const QUrl& objUrl) {
        if (!object && url == objUrl) {
            qDebug() << "Failed to load QML file!";
            QCoreApplication::exit(-1);
        }
    }, Qt::QueuedConnection);

    engine.load(url);

    if (engine.rootObjects().isEmpty()) {
        qDebug() << "Failed to load QML file. Error!!";
        return -1;
    }

    return app.exec();
}

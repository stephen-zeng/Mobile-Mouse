/*
Author: Stephen Zeng 曾浩正
Mail: stephenzeng@goforit.top
*/

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QList>
#include <QtQml>
#include <QVariant>
#include <QPermissions>
#include <QIcon>

// #include <stdlib.h>
#include "getserver.h"
#include "beserver.h"

#if defined(Q_OS_IOS) || defined(Q_OS_ANDROID)
#include "getsensor.h"
#endif


// #include "animalabstractlistmodel.h"

int main(int argc, char *argv[])
{

    // system("/opt/homebrew/bin/cliclick");
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    auto permissionStatus = app.checkPermission(QBluetoothPermission{});
    //! [Check Bluetooth Permission]

    //! [Request Bluetooth Permission]
    if (permissionStatus == Qt::PermissionStatus::Undetermined) {
        qInfo("Requesting Bluetooth permission ...");
        app.requestPermission(QBluetoothPermission{}, [&permissionStatus](const QPermission &permission){
            qApp->exit();
            permissionStatus = permission.status();
        });
        // Now, wait for permission request to resolve.
        app.exec();
    }
    //! [Request Bluetooth Permission]

    if (permissionStatus == Qt::PermissionStatus::Denied) {
        // Either explicitly denied by a user, or Bluetooth is off.
        qWarning("This application cannot use Bluetooth, the permission was denied");
        return -1;
    }


#if defined(Q_OS_IOS) || defined(Q_OS_ANDROID)
    GetSensor getSensorInstance(&app);
    engine.rootContext()->setContextProperty("getSensor", &getSensorInstance);
#endif
    BeServer beServerInstance(&app);
    GetServer getServerInstance(&app);

    engine.rootContext()->setContextProperty("getServer", &getServerInstance);
    engine.rootContext()->setContextProperty("beServer", &beServerInstance);

    const QUrl url(QStringLiteral("qrc:/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    app.setWindowIcon(QIcon(":/icons/win_icon.ico"));

    return app.exec();
}

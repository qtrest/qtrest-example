#include <QApplication>
#include <QQmlApplicationEngine>
#include <mobile/adctl/adctl.h>
#include "api/apimanager.h"
#include "api/models/couponmodel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //AdCtl
    QApplication::setApplicationName("Skid.KZ");
    QApplication::setApplicationVersion("1.0");
    qmlRegisterType<AdCtl>("ru.forsk.adctl", 1, 0, "AdCtl");

    //models
    qmlRegisterType<CouponModel>("ru.forsk.coupons", 1, 0, "CouponModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

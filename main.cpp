#include <QApplication>
#include <QQmlApplicationEngine>
#include <mobile/adctl/adctl.h>
#include "api/apimanager.h"
#include "api/models/couponmodel.h"
#include <QtAwesome.h>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString languageCode = QLocale::system().name();
    if (languageCode.contains("_")) {
        languageCode = languageCode.split("_").at(0);
    }
    QString fileName = "skidkz_" + languageCode;

    QTranslator qtTranslator;
    if ( qtTranslator.load(fileName, ":/i18n/") ){
        qDebug() << "Translation file loaded" << fileName;
    } else {
        qDebug() << "Translation file not loaded:" << fileName;
        qDebug() << "Language " << languageCode << " not supported yet";
    }
    app.installTranslator(&qtTranslator);

    //AdCtl
    QApplication::setApplicationName("Skid.KZ");
    QApplication::setApplicationVersion("1.0");
    qmlRegisterType<AdCtl>("ru.forsk.adctl", 1, 0, "AdCtl");

    //Font Awesome
    QtAwesome* awesome = new QtAwesome( qApp );
    awesome->initFontAwesome();

    qDebug() << awesome->iconLink( "beer" );

    //models
    qmlRegisterType<CouponModel>("ru.forsk.coupons", 1, 0, "CouponModel");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("awesome", awesome);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

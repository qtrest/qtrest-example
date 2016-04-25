#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "api/models/couponmodel.h"
#include "QtAwesomeAndroid.h"
#include <QTranslator>
#include <QSettings>

#include "jsonrestlistmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication::setApplicationName("Skid.KZ");
    QGuiApplication::setApplicationVersion("1.0");
    QGuiApplication::setOrganizationName("Forsk.Ru");
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    //i18n
    QString languageCode = QLocale::system().name();
    if (languageCode.contains("_")) {
        languageCode = languageCode.split("_").at(0);
    }
    QString fileName = "skidkz_" + languageCode;

    QTranslator qtTranslator;
    if ( !qtTranslator.load(fileName, ":/i18n/") ){
        qDebug() << "Translation file not loaded:" << fileName;
        qDebug() << "Language " << languageCode << " not supported yet";
    }
    app.installTranslator(&qtTranslator);

    //Font Awesome
    QtAwesomeAndroid* awesome = new QtAwesomeAndroid( qApp );
    awesome->setDefaultOption( "color", QColor(255,255,255) );
    awesome->initFontAwesome();

    //api and models
    SkidKZApi::declareQML();
    CouponModel::declareQML();
    JsonRestListModel::declareQML();

    //settings
    QSettings settings;
    qputenv("QT_LABS_CONTROLS_STYLE", settings.value("style").toByteArray());

    QQmlApplicationEngine engine;
    QPM_INIT(engine)
    engine.rootContext()->setContextProperty("awesome", awesome);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

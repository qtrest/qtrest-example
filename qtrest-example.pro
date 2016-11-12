TEMPLATE = app

QT += quick
QT += widgets

CONFIG += c++11


SOURCES += main.cpp \
    api/models/couponmodel.cpp \
    api/skidkzapi.cpp

HEADERS += \
    api/models/couponmodel.h \
    api/skidkzapi.h

RESOURCES += qml/qml.qrc \
             assets/assets.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

#Translations
lupdate_only {
    SOURCES += $$PWD/qml/*.qml \
    $$PWD/qml/activities/*.qml \
    $$PWD/qml/includes/*.qml \
    $$PWD/qml/models/*.qml
}

TRANSLATIONS += assets/i18n/skidkz_ru.ts

# Default rules for deployment.
include(deployment.pri)

#Font Awesome
include(3rd/QtAwesome/QtAwesome/QtAwesome.pri)

#AdCtl: Google Analytics, AdMob, StartAD.mobi, Qt-REST
include(3rd/qtrest/com_github_kafeg_qtrest.pri)

DISTFILES += \
    QtMicroRestFramework.qmodel

#INCLUDEPATH += $$PWD/vendor/com/github/kafeg/qtrest/src/ \
#                $$PWD/vendor/com/github/kafeg/qtrest/src/models/

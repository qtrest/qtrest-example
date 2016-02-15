TEMPLATE = app

QT += quick

CONFIG += c++11

SOURCES += main.cpp \
    api/models/couponmodel.cpp \
    api/models/jsonrestlistmodel.cpp \
    api/models/baserestlistmodel.cpp \
    api/models/detailsmodel.cpp \
    api/apibase.cpp \
    api/api.cpp \
    api/models/xmlrestlistmodel.cpp

HEADERS += \
    api/usingleton.h \
    api/models/couponmodel.h \
    api/models/jsonrestlistmodel.h \
    api/models/baserestlistmodel.h \
    api/models/detailsmodel.h \
    api/apibase.h \
    api/api.h \
    api/models/xmlrestlistmodel.h

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
include(3rd/awesome/QtAwesome/QtAwesome.pri)

#AdCtl: Google Analytics, AdMob, StartAD.mobi
ANDROID_PACKAGE_SOURCE_DIR = $$PWD/mobile/android
include(mobile/adctl/AdCtl.pri)
android {
  OTHER_FILES += $$PWD/mobile/android/AndroidManifest.xml
}

DISTFILES += \
    mobile/android/AndroidManifest.xml \
    mobile/android/gradle/wrapper/gradle-wrapper.jar \
    mobile/android/gradlew \
    mobile/android/res/values/libs.xml \
    mobile/android/build.gradle \
    mobile/android/gradle/wrapper/gradle-wrapper.properties \
    mobile/android/gradlew.bat \
    qml/controls/Button.qml \
    qml/controls/Loader.qml \
    qml/controls/Text.qml \
    qml/controls/Variables.qml \
    QtMicroRestFramework.qmodel

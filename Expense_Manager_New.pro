#-------------------------------------------------
#
# Project created by QtCreator 2015-12-12T13:40:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Expense_Manager
TEMPLATE = app

SOURCES += main.cpp\
    frmsavemaster.cpp \
    frmreport.cpp \
    clsglobal.cpp \
    frmsavetrannew.cpp \
    frmstartupnew.cpp \
    clsdatabase.cpp \
    frmlogin.cpp \
    frmsettings.cpp

HEADERS  += \
    frmsavemaster.h \
    frmreport.h \
    clsglobal.h \
    frmsavetrannew.h \
    frmstartupnew.h \
    clsdatabase.h \
    frmlogin.h \
    frmsettings.h

FORMS    += \
    frmsavemaster.ui \
    frmreport.ui \
    frmsavetrannew.ui \
    frmstartupnew.ui \
    frmlogin.ui \
    frmsettings.ui

CONFIG += c++11

QT += sql

deployment.files += emdb
deployment.path = /assets
INSTALLS += deployment

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

RESOURCES += \
    image.qrc

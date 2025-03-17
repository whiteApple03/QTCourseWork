QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    eraser.cpp \
    fieldcontroller.cpp \
    fieldscene.cpp \
    inputfieldsize.cpp \
    main.cpp \
    mainwindow.cpp \
    pencil.cpp \
    pixelartdatabasemanager.cpp \
    pixelitem.cpp \
    toolconfiguration.cpp \
    toolforfieldinteractive.cpp

HEADERS += \
    eraser.h \
    fieldcontroller.h \
    fieldscene.h \
    fieldview.h \
    inputfieldsize.h \
    mainwindow.h \
    pencil.h \
    pixelartdatabasemanager.h \
    pixelitem.h \
    toolconfiguration.h \
    toolforfieldinteractive.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore

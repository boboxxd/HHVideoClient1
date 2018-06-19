#-------------------------------------------------
#
# Project created by QtCreator 2018-05-17T10:56:53
#
#-------------------------------------------------

QT       += core gui opengl sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HHVideoClient1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    hikvisonwapper.cpp \
    ptzbutton.cpp \
    videowidget.cpp \
    ptzwidget.cpp \
    devicelistwidget.cpp \
    sqlhandle.cpp \
    alarmmsgview.cpp \
    alarmmsgmodel.cpp \
    previewwidget.cpp \
    imagelistwidget.cpp \
    mainlayout.cpp \
    config.cpp

HEADERS += \
        widget.h \
    hikvisonwapper.h \
    ptzbutton.h \
    videowidget.h \
    ptzwidget.h \
    devicelistwidget.h \
    sqlhandle.h \
    common.h \
    alarmmsgview.h \
    alarmmsgmodel.h \
    previewwidget.h \
    imagelistwidget.h \
    mainlayout.h \
    config.h

FORMS += \
        widget.ui \
    ptzwidget.ui \
    devicelistwidget.ui
unix:!macx: LIBS += -L$$PWD/lib/ -lSuperRender \
-lAudioRender \
-lHCCore \
-lhcnetsdk \
-lhpr \
-lPlayCtrl \

unix:!macx: LIBS += -L$$PWD/lib/HCNetSDKCom \
-lanalyzedata \
-lHCAlarm \
-lHCCoreDevCfg \
-lHCDisplay \
-lHCGeneralCfgMgr \
-lHCIndustry \
-lHCPlayBack \
-lHCPreview \
-lHCVoiceTalk \
-liconv2 \
-lStreamTransClient \
-lSystemTransform \

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

RESOURCES += \
    icon.qrc

RC_FILE += icon.rc

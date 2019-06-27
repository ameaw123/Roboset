#-------------------------------------------------
#
# Project created by QtCreator 2017-04-14T13:49:57
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SeerTCPTest
TEMPLATE = app


SOURCES += main.cpp\
        SCTcpToolWidget.cpp \
    SCStatusTcp.cpp

HEADERS  += SCTcpToolWidget.h \
    SCStatusTcp.h \
    SCHeadData.h \
    HCNetSDK.h

FORMS    += SCTcpToolWidget.ui

RC_FILE = ICO.rc

LIBS    +="C:/Users/LHM/Desktop/Qt demo/haikangweishi/HCCore.lib"
LIBS    +="C:/Users/LHM/Desktop/Qt demo/haikangweishi/HCNetSDK.lib"
LIBS    +="C:/Users/LHM/Desktop/Qt demo/haikangweishi/HCNetSDKCom/HCAlarm.lib"
LIBS    +="C:/Users/LHM/Desktop/Qt demo/haikangweishi/HCNetSDKCom/HCGeneralCfgMgr.lib"
LIBS    +="C:/Users/LHM/Desktop/Qt demo/haikangweishi/HCNetSDKCom/HCPreview.lib"
LIBS    +="C:/Users/LHM/Desktop/Qt demo/haikangweishi/PlayCtrl.lib"

DISTFILES +=

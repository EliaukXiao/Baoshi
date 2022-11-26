QT       += core gui
QT       += sql
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CAboutDlg.cpp \
    CGameDlg.cpp \
    CGameLogic.cpp \
    CHelpDlg.cpp \
    CMenuDlg.cpp \
    CNameDlg.cpp \
    CRankDlg.cpp \
    CRankLogic.cpp \
    CRegist.cpp \
    CSetDlag.cpp \
    Login.cpp \
    main.cpp \
    CBejeweledDlg.cpp \
    CMusicPlayer.cpp

HEADERS += \
    CAboutDlg.h \
    CBejeweledDlg.h \
    CGameDlg.h \
    CGameLogic.h \
    CHelpDlg.h \
    CMenuDlg.h \
    CNameDlg.h \
    CRankDlg.h \
    CRankLogic.h \
    CRegist.h \
    CSetDlag.h \
    Login.h \
    global.h \
    CMusicPlayer.h

FORMS += \
    CAboutDlg.ui \
    CBejeweledDlg.ui \
    CGameDlg.ui \
    CHelpDlg.ui \
    CMenuDlg.ui \
    CNameDlg.ui \
    CRankDlg.ui \
    CRegist.ui \
    CSetDlag.ui \
    Login.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    sucai/1.bmp \
    sucai/2.bmp \
    sucai/3.bmp \
    sucai/4.bmp \
    sucai/5.bmp \
    sucai/6.bmp \
    sucai/7.bmp \
    sucai/8.bmp \
    sucai/9.bmp \
    sucai/background1.bmp \
    sucai/background2.bmp

RESOURCES += \
    image.qrc

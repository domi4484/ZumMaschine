#-------------------------------------------------
#
# Project DrawingsMirror
#
# (C) 2016 Damiano Lombardi
#
#-------------------------------------------------

TEMPLATE  = app

TARGET    = DrawingsMirror

QT       += core gui widgets

CONFIG   += debug

linux-g++-64:                                 PLATFORM = "linux-g++-64"
else:linux-g++:                               PLATFORM = "linux-g++-32"
else:linux-arm*:                              PLATFORM = "linux-arm"
else:win32 {
   contains      (QMAKE_TARGET.arch, x86_64): PLATFORM = "win64"
   else:contains (QMAKE_TARGET.arch, x86)     PLATFORM = "win32-msvc"
   else:                                      PLATFORM = "win32-mingw"
}
isEmpty (PLATFORM):   error (PLATFORM is undefined.)

INCLUDEPATH *= "$$_PRO_FILE_PWD_/"
DESTDIR = "$$_PRO_FILE_PWD_/../bin"
# Installation on the target
target.path = "$$_PRO_FILE_PWD_/../bin"
INSTALLS *= target

SOURCES += main.cpp\
           MainWindow.cpp \
    Settings.cpp \
    Settings_Gui.cpp \
    TreeWidgetItem.cpp \
    Part.cpp \
    Material.cpp \
    Exception.cpp

HEADERS  += MainWindow.h \
    Settings.h \
    Settings_Gui.h \
    TreeWidgetItem.h \
    Part.h \
    Material.h \
    Exception.h

FORMS    += MainWindow.ui \
    Settings_Gui.ui

RESOURCES += \
    Resources/Resources.qrc

DISTFILES += \
    ../bin/Werkstoffen/Stahl.material.json


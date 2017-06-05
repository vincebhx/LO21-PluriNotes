#-------------------------------------------------
#
# Project created by QtCreator 2017-06-04T23:17:39
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets designer

macx {
    QMAKE_MAC_SDK = macosx10.12
    INCLUDEPATH += /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.12.sdk/usr/include
    QMAKE_LFLAGS = -std=c++11 -framework opengl
}

TARGET = PluriNotes
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    src/main.cpp \
    ui/mainwindow.cpp \
    src/note/note.cpp \
    src/note/article.cpp \
    src/note/tache.cpp \
    src/note/media.cpp \
    src/note/versionindex.cpp \
    src/note/notesmanager.cpp \
    src/relation/relation.cpp \
    src/relation/couple.cpp \
    src/dbmanager.cpp

HEADERS  += \
    ui/mainwindow.h \
    src/exception.h \
    src/note/note.h \
    src/note/article.h \
    src/note/tache.h \
    src/note/media.h \
    src/note/versionindex.h \
    src/note/notesmanager.h \
    src/relation/relation.h \
    src/relation/couple.h \
    src/dbmanager.h

FORMS    += \
    ui/mainwindow.ui

 target.path = $$[QT_INSTALL_PLUGINS]/designer
 INSTALLS += target

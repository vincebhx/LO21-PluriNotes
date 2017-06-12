QT += core gui widgets xml sql
macx {
    QMAKE_MAC_SDK = macosx10.12
    INCLUDEPATH += /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.12.sdk/usr/include
}
QMAKE_CXXFLAGS = -std=c++11

HEADERS += \
    gui/mainwindow.h \
    gui/dialog.h \
    src/exception.h \
    src/relation/couple.h \
    src/relation/relation.h \
    src/relation/relationsmanager.h \
    src/note/article.h \
    src/note/media.h \
    src/note/note.h \
    src/note/notesmanager.h \
    src/note/tache.h \
    src/note/versionindex.h \
    src/dbmanager.h \
    gui/mediator.h

SOURCES += \
    gui/NoteSelector.cpp \
    gui/mainwindow.cpp \
    gui/dialog.cpp \
    src/main.cpp \
    src/relation/couple.cpp \
    src/relation/relation.cpp \
    src/relation/relationsmanager.cpp \
    src/note/article.cpp \
    src/note/media.cpp \
    src/note/note.cpp \
    src/note/notesmanager.cpp \
    src/note/tache.cpp \
    src/note/versionindex.cpp \
    src/dbmanager.cpp \
    gui/mediator.cpp

DISTFILES += \
    README.md \
    notes.db

FORMS += \
    gui/mainwindow.ui \
    gui/dialog.ui

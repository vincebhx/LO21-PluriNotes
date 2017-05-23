QT += core gui widgets xml
macx {
    QMAKE_MAC_SDK = macosx10.12
    INCLUDEPATH += /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.12.sdk/usr/include
    QMAKE_LFLAGS = -std=c++11 -framework opengl
}
QMAKE_CXXFLAGS = -Wall -Wextra -std=c++11 -pedantic -Werror

HEADERS += \
    src/Date.h \
    src/Note.h \
    src/NotesManager.h \
    src/Relation.h \
    gui/NoteViewer.h \
    src/Couple.h \
    gui/MainWindow.h

SOURCES += \
    src/Application.cpp \
    src/Date.cpp \
    src/Note.cpp \
    src/NotesManager.cpp \
    src/Relation.cpp \
    gui/NoteViewer.cpp \
    src/Couple.cpp \
    gui/MainWindow.cpp

DISTFILES += \
    README.md

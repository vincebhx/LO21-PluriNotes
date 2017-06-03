QT += core gui widgets xml sql
macx {
    QMAKE_MAC_SDK = macosx10.12
    INCLUDEPATH += /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.12.sdk/usr/include
    QMAKE_LFLAGS = -std=c++11 -framework opengl
    target_db.path = $$[OUT_PWD]/PluriNotes.app/Contents/MacOS/
    target_db.files = $$[_PRO_FILE_PWD_]/notes.db
    INSTALLS += target_db
}
QMAKE_CXXFLAGS = -std=c++11

HEADERS += \
    src/Date.h \
    src/Note.h \
    src/NotesManager.h \
    src/Relation.h \
    gui/NoteViewer.h \
    src/Couple.h \
    gui/MainWindow.h \
    src/Version.h \
    src/NoteException.h \
    src/DbManager.h \
    gui/NoteSelector.h

SOURCES += \
    src/Application.cpp \
    src/Date.cpp \
    src/Note.cpp \
    src/NotesManager.cpp \
    src/Relation.cpp \
    gui/NoteViewer.cpp \
    src/Couple.cpp \
    gui/MainWindow.cpp \
    src/Version.cpp \
    src/DbManager.cpp \
    gui/NoteSelector.cpp

DISTFILES += \
    README.md \
    notes.db

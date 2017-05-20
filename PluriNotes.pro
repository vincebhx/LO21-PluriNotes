QT += widgets
QT += xml
macx {
    QMAKE_MAC_SDK = macosx10.12
    INCLUDEPATH += /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.12.sdk/usr/include
}
QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

HEADERS += \
    src/Date.h \
    src/Note.h \
    src/NotesManager.h \
    src/Relation.h

SOURCES += \
    src/Application.cpp \
    src/Date.cpp \
    src/Note.cpp \
    src/NotesManager.cpp \
    src/Relation.cpp

DISTFILES += \
    README.md

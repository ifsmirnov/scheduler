SOURCES += \
    main.cpp \
    src/regularevent.cpp \
    src/irregularevent.cpp \
    src/event.cpp \
    src/day.cpp

HEADERS += \
    src/regularevent.hpp \
    src/irregularevent.hpp \
    src/event.hpp \
    src/day.hpp

INCLUDEPATH += DEPENDPATH

QMAKE_CXXFLAGS += -std=c++0x

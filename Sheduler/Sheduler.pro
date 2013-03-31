SOURCES += \
    main.cpp \
    src/regularevent.cpp \
    src/irregularevent.cpp \
    src/event.cpp \
    src/day.cpp \
    gui/daywidget.cpp \
    gui/weekwidget.cpp \
    src/calendar.cpp

HEADERS += \
    src/regularevent.hpp \
    src/irregularevent.hpp \
    src/event.hpp \
    src/day.hpp \
    gui/daywidget.hpp \
    gui/weekwidget.hpp \
    src/calendar.hpp

INCLUDEPATH += DEPENDPATH

QMAKE_CXXFLAGS += -std=c++0x

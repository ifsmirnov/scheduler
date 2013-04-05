SOURCES += \
    main.cpp \
    src/regularevent.cpp \
    src/irregularevent.cpp \
    src/event.cpp \
    src/day.cpp \
    gui/daywidget.cpp \
    gui/weekwidget.cpp \
    src/dailyschedule.cpp \
    src/calendar/calendar.cpp \
    src/calendar/yearcontainer.cpp \
    src/calendar/monthcontainer.cpp \
    src/calendar/container.cpp \
    src/calendar/globalcontainer.cpp \
    gui/addeventdialog.cpp

HEADERS += \
    src/regularevent.hpp \
    src/irregularevent.hpp \
    src/event.hpp \
    src/day.hpp \
    gui/daywidget.hpp \
    gui/weekwidget.hpp \
    src/dailyschedule.hpp \
    src/calendar/calendar.hpp \
    src/calendar/yearcontainer.hpp \
    src/calendar/monthcontainer.hpp \
    src/calendar/container.hpp \
    src/calendar/globalcontainer.hpp \
    gui/addeventdialog.hpp

INCLUDEPATH += DEPENDPATH

QMAKE_CXXFLAGS += -std=c++0x

QT += xml

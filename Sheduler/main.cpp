#include <QApplication>
#include <QPalette>

#include <iostream>
#include <stdexcept>

#include <QDate>

#include <src/event.hpp>
#include <src/regularevent.hpp>
#include <src/irregularevent.hpp>
#include <src/calendar/calendar.hpp>
#include <src/day.hpp>
#include <gui/addeventdialog.hpp>
#include <gui/daywidget.hpp>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QPalette pal = app.palette();

    pal.setColor(QPalette::Window, QColor(Qt::green).lighter());
    app.setPalette(pal);

    Calendar calendar;
    QDate begin(2001, 03, 14);
    QDate end(2002, 06, 10);

    DailyScheduleSPtr schedule(new DailySchedule);

    for (QDate t = begin; t <= end; t = t.addDays(1)) {
        calendar.setSchedule(t, schedule);
    }

    std::cerr << calendar.getDaysInRange(QDate(2001, 02, 01), QDate(2002, 03, 13)).size() << std::endl;

    return 0;
}

#include <QApplication>
#include <QPalette>

#include <iostream>
#include <stdexcept>

#include <QDate>
#include <QFile>

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

    Calendar *calendar = new Calendar;
    QDate begin(2001, 03, 14);
    QDate end(2002, 06, 10);

    DailyScheduleSPtr schedule(new DailySchedule);

    schedule->addEvent(new RegularEvent(QTime::currentTime(), 1000));
    //schedule->addEvent(new IrregularEvent(QTime::currentTime(), 40));

    for (QDate t = begin; t <= end; t = t.addDays(1)) {
        calendar->setSchedule(t, schedule->clone());
    }

    //std::cerr << DailySchedule::count << std::endl;
    //std::cerr << Event::count << std::endl;

    //std::cerr << calendar->getDaysInRange(QDate(2001, 02, 01), QDate(2002, 03, 13)).size() << std::endl;

    delete calendar;

    //schedule.reset();

    //std::cerr << DailySchedule::count << std::endl;
    //std::cerr << Event::count << std::endl;
    //std::cerr << schedule->events().size() << std::endl;

    DayWidget* dayWidget = new DayWidget(schedule, QDate(2001, 02, 01));
    //dayWidget->setStyleSheet("QPushButton {  color: white; background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #88d, stop: 0.1 #99e, stop: 0.49 #77c, stop: 0.5 #66b, stop: 1 #77c);}");
    dayWidget->show();

    return app.exec();
}

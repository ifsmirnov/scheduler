#include <QApplication>
#include <QPalette>
#include <QFile>
#include <QDomElement>
#include <QDomDocument>

#include <iostream>
#include <stdexcept>

#include <QDate>

#include <src/event.hpp>
#include <src/regularevent.hpp>
#include <src/irregularevent.hpp>
#include <src/calendar/calendar.hpp>
#include <src/calendar/monthcontainer.hpp>
#include <src/calendar/globalcontainer.hpp>
#include <src/day.hpp>
#include <gui/addeventdialog.hpp>
#include <gui/daywidget.hpp>
#include <gui/weekwidget.hpp>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QPalette pal = app.palette();

    pal.setColor(QPalette::Window, QColor(Qt::green).lighter());
    app.setPalette(pal);

    Calendar *calendar = new Calendar;
    QDate begin(2001, 03, 14);
    QDate end(2002, 03, 14);

    DailyScheduleSPtr schedule(new DailySchedule);

    schedule->addEvent(new RegularEvent(QTime::currentTime(), 1000));
    //schedule->addEvent(new IrregularEvent(QTime::currentTime(), 40));

    for (QDate t = begin; t <= end; t = t.addDays(1)) {
        calendar->setSchedule(t, schedule->clone());
    }

    std::cerr << calendar->getDaysInRange(QDate(2000, 1, 1), QDate(2010, 1, 1)).size() << std::endl;


    DayWidget* dayWidget = new DayWidget(schedule, QDate(2001, 02, 01));
    dayWidget->show();

    QVector<DailyScheduleSPtr> dailySchedules;
    dailySchedules.push_back(schedule);
    dailySchedules.push_back(schedule);
    dailySchedules.push_back(schedule);
    dailySchedules.push_back(schedule);
    dailySchedules.push_back(schedule);
    dailySchedules.push_back(schedule);
    dailySchedules.push_back(schedule);
    WeekWidget* weekWidget = new WeekWidget(begin, dailySchedules);
    weekWidget->show();

    return app.exec();
}

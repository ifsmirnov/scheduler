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
    QDate end(2001, 05, 15);

    DailyScheduleSPtr schedule(new DailySchedule);

    schedule->addEvent(new RegularEvent(QTime::currentTime(), 10, "hello world"));
    schedule->addEvent(new IrregularEvent(QTime::currentTime(), 40));

    for (QDate t = begin; t <= end; t = t.addDays(1)) {
        calendar->setSchedule(t, schedule->clone());
    }

    QFile file("/tmp/file");
    if (!file.open(QIODevice::WriteOnly)) {
        throw;
    }

    QDomDocument document;
    document.appendChild(calendar->serialize(document));

    QString text = document.toString(2);

    file.write(text.toAscii());

    delete calendar;

    //schedule.reset();

    std::cerr << DailySchedule::count << std::endl;
    std::cerr << Event::count << std::endl;

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

#include <QApplication>
#include <QPalette>
#include <QFile>
#include <QDomElement>
#include <QDomDocument>

#include <iostream>
#include <cassert>
#include <stdexcept>

#include <QDate>
#include <QFile>

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

#include "src/managers/collectionmanager.hpp"
#include "src/managers/schedulemanager.hpp"
#include "src/managers/singlemanager.hpp"
#include "src/managers/weekmanager.hpp"


void testDayWidget() {


    Calendar *calendar = new Calendar;
    QDate begin(2001, 03, 14);
    QDate end(2002, 03, 14);

    DailyScheduleSPtr schedule(new DailySchedule);

    schedule->addEvent(new RegularEvent(QTime(1, 0), 3000, "YAHOO!"));
    schedule->addEvent(new IrregularEvent(QTime(1, 30), 60 * 90, "YAHOOHOO!"));
    //schedule->addEvent(new IrregularEvent(QTime::currentTime(), 40));

    for (QDate t = begin; t <= end; t = t.addDays(1)) {
        calendar->setSchedule(t, schedule->clone());
    }

    std::cerr << calendar->getDaysInRange(QDate(2000, 1, 1), QDate(2010, 1, 1)).size() << std::endl;


    DayWidget* dayWidget = new DayWidget(schedule, QDate(2001, 02, 01));
    //dayWidget->setStyleSheet("QPushButton {  color: white; background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #88d, stop: 0.1 #99e, stop: 0.49 #77c, stop: 0.5 #66b, stop: 1 #77c);}");
    dayWidget->show();

    QVector<DailyScheduleSPtr> dailySchedules;
    dailySchedules.push_back(schedule);
    dailySchedules.push_back(schedule);
    dailySchedules.push_back(schedule);
    dailySchedules.push_back(schedule);
    dailySchedules.push_back(schedule);
    dailySchedules.push_back(schedule);
    dailySchedules.push_back(schedule);

    /*WeekWidget* weekWidget = new WeekWidget(QDate(2013, 4, 27), dailySchedules);
    weekWidget->show();*/

}

void testManagers()
{
    CollectionManager *manager = new CollectionManager;
    SingleManager *singleManager = new SingleManager;
    WeekManager *weekManager = new WeekManager;
    manager->addChildManager(singleManager);
    manager->addChildManager(weekManager);

    singleManager->addEvent(new RegularEvent(QTime::currentTime(), 10, "Hello"), QDate(2013, 04, 19));
    weekManager->addEvent(new IrregularEvent(QTime::currentTime(), 20, "world!"), 4);

    std::cerr << manager->getEvents(QDate(2013, 04, 12)).size() << std::endl;
    std::cerr << "Events count: " << Event::count << std::endl;

    delete manager;

    std::cerr << "Events count: " << Event::count << std::endl;
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QPalette pal = app.palette();

    pal.setColor(QPalette::Window, QColor(Qt::green).lighter());
    app.setPalette(pal);

    //testDayWidget();

    testManagers();

    return app.exec();
    //return 0;
}

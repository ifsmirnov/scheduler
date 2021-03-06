#include <QApplication>
#include <QPalette>
#include <QFile>
#include <QDomElement>
#include <QDomDocument>
#include <QMainWindow>

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
#include <gui/mainwindow.hpp>
#include <gui/eventslist.hpp>

#include "src/managers/collectionmanager.hpp"
#include "src/managers/schedulemanager.hpp"
#include "src/managers/singlemanager.hpp"
#include "src/managers/weekmanager.hpp"

#include "gui/calendarwidget.hpp"
#include "gui/monthwidget.hpp"


void testDayWidget() {


    /*Calendar *calendar = new Calendar;
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
            painter.drawText(textRect, "Date: " + day.toString());
    dailySchedules.push_back(schedule);
    dailySchedules.push_back(schedule);*/

    /*WeekWidget* weekWidget = new WeekWidget(QDate(2013, 4, 27), dailySchedules);
    weekWidget->show();*/

}

void testWeekWidgetAndEventsList() {
    Calendar* calendar = new Calendar();
    Event* event1 = new IrregularEvent(QTime(12, 40), QTime(13, 10), "Tralala!", Qt::red);
    Event* event2 = new IrregularEvent(QTime(14, 00), QTime(14, 30), "Trulala!", Qt::green);
    calendar->addIrregularEvent(QDate::currentDate(), event1);
    calendar->addIrregularEvent(QDate::currentDate(), event2);
    calendar->addIrregularEvent(QDate::currentDate(), event1);
    calendar->addIrregularEvent(QDate::currentDate(), event2);
    calendar->addIrregularEvent(QDate::currentDate(), event1);
    calendar->addIrregularEvent(QDate::currentDate(), event2);
    calendar->addIrregularEvent(QDate::currentDate(), event1);
    calendar->addIrregularEvent(QDate::currentDate(), event2);
    calendar->addIrregularEvent(QDate::currentDate(), event1);
    calendar->addIrregularEvent(QDate::currentDate(), event2);
    calendar->addIrregularEvent(QDate::currentDate(), event1);
    calendar->addIrregularEvent(QDate::currentDate(), event2);
    calendar->addIrregularEvent(QDate::currentDate(), event1);
    calendar->addIrregularEvent(QDate::currentDate(), event2);
    calendar->addIrregularEvent(QDate::currentDate(), event1);
    calendar->addIrregularEvent(QDate::currentDate(), event2);
    calendar->addIrregularEvent(QDate::currentDate(), event1);
    calendar->addIrregularEvent(QDate::currentDate(), event2);
    calendar->addIrregularEvent(QDate::currentDate(), event1);
    calendar->addIrregularEvent(QDate::currentDate(), event2);
    calendar->addIrregularEvent(QDate::currentDate(), event1);
    calendar->addIrregularEvent(QDate::currentDate(), event2);
    calendar->addIrregularEvent(QDate::currentDate(), event1);
    calendar->addIrregularEvent(QDate::currentDate(), event2);
    calendar->addIrregularEvent(QDate::currentDate(), event1);
    calendar->addIrregularEvent(QDate::currentDate(), event2);
    calendar->addIrregularEvent(QDate::currentDate(), event1);
    calendar->addIrregularEvent(QDate::currentDate(), event2);
    calendar->addIrregularEvent(QDate::currentDate(), event1);
    calendar->addIrregularEvent(QDate::currentDate(), event2);
    calendar->addIrregularEvent(QDate::currentDate(), event1);
    calendar->addIrregularEvent(QDate::currentDate(), event2);
    calendar->addIrregularEvent(QDate::currentDate(), event1);
    calendar->addIrregularEvent(QDate::currentDate(), event2);


    /*WeekWidget* weekWidget = new WeekWidget(QDate::currentDate(), calendar->getManager());
    QObject::connect(weekWidget, SIGNAL(addWeeklyWidget(int,Event*)), calendar, SLOT(addWeeklyEvent(int,Event*)));
    weekWidget->show();*/

    EventsList* eventsList = new EventsList(QDate::currentDate(), QDate::currentDate(), calendar->getManager());
    eventsList->show();
}

void testManagers()
{
    CollectionManager *manager = new CollectionManager;
    SingleManager *singleManager = new SingleManager;
    WeekManager *weekManager = new WeekManager;
    manager->addChildManager(singleManager);
    manager->addChildManager(weekManager);

    //singleManager->addEvent(new RegularEvent(QTime::currentTime(), 10, "Hello"), QDate(2013, 04, 19));
    //weekManager->addEvent(new IrregularEvent(QTime::currentTime(), 20, "world!"), 4);

    std::cerr << manager->getEvents(QDate(2013, 04, 12)).size() << std::endl;
    std::cerr << "Events count: " << Event::count << std::endl;

    delete manager;

    std::cerr << "Events count: " << Event::count << std::endl;
}

//Calendar calendar;

void testManagersWithGui()
{
    QDate date = QDate::currentDate();

    QFile file("/tmp/ser");
    file.open(QIODevice::ReadOnly);
    QDomDocument document;
    document.setContent(&file);

    //Calendar *calendar = Calendar::deserialize(document.firstChildElement("calendar"));
    Calendar *calendar = new Calendar;

    DayWidget *dayWidget = new DayWidget(calendar->getManager(), date);
    QObject::connect(dayWidget, SIGNAL(addIrregularEvent(QDate,Event*)),
                     calendar, SLOT(addIrregularEvent(QDate,Event*)));

    /*DayWidget *dayWidget = new DayWidget(calendar.getManager(), date);
    QObject::connect(dayWidget, SIGNAL(addIrregularEvent(QDate,Event*)),
                     &calendar, SLOT(addIrregularEvent(QDate,Event*)));
                             */
    dayWidget->show();
}

void testCalendarWidget()
{
    QDate date = QDate::currentDate();
    Calendar *calendar = new Calendar;
    CalendarWidget *calendarWidget = new CalendarWidget(date, calendar);
    calendarWidget->show();
}

void testMonthWidget()
{
    Calendar *calendar = new Calendar;
    MonthWidget *widget = new MonthWidget(calendar->getManager(), QDate::currentDate());

    widget->show();
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QPalette pal = app.palette();
    MainWindow mw(new Calendar());

    pal.setColor(QPalette::Window, QColor(Qt::green).lighter());
    app.setPalette(pal);

    //testDayWidget();
    //testManagers();
    //testManagersWithGui();
    //testWeekWidget();
    mw.show();
    //testManagersWithGui();
    //testWeekWidgetAndEventsList();

    //testCalendarWidget();
    //testMonthWidget();

    return app.exec();
}

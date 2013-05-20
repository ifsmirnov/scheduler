#ifndef CALENDARWIDGET_HPP
#define CALENDARWIDGET_HPP

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QSignalMapper>
#include <QLabel>

#include "src/calendar/calendar.hpp"
#include "src/managers/schedulemanager.hpp"
#include "gui/daywidget.hpp"
#include "gui/monthwidget.hpp"
#include "gui/weekwidget.hpp"
#include "gui/eventslist.hpp"

class CalendarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CalendarWidget(QDate date, Calendar *calendar, QWidget *parent = 0);
    ~CalendarWidget();
    
signals:
    
public slots:
    void hideEvent(QHideEvent *);
    void dayPressed(QDate date);
    void setDate(QDate date);
    void displayWeek();
    void closeWeek();
    void closeDay();

public:
    void setCalendar(Calendar *newCalendar);

private:
    QDate date_;
    Calendar *calendar;
    DayWidget *dayWidget;
    MonthWidget *monthWidget;
    WeekWidget *weekWidget;
    EventsList *eventList;

    QLabel *title;
};

#endif // CALENDARWIDGET_HPP

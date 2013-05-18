#ifndef CALENDARWIDGET_HPP
#define CALENDARWIDGET_HPP

#include <QWidget>

#include "src/calendar/calendar.hpp"
#include "src/managers/schedulemanager.hpp"
#include "gui/daywidget.hpp"
#include "gui/monthwidget.hpp"

class CalendarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CalendarWidget(QDate date, Calendar *calendar, QWidget *parent = 0);
    ~CalendarWidget();
    
signals:
    
public slots:
    void closeEvent(QCloseEvent *);

    void setHighlight(QDate date);
    void noHighlight();

    void dayPressed(QDate date);

public:
    bool hasHighlight() const;
    void setCalendar(Calendar *newCalendar);

private:
    Calendar *calendar;
    int curYear, curMonth, curDay;

    DayWidget *dayWidget;
    MonthWidget *monthWidget;
    
};

#endif // CALENDARWIDGET_HPP

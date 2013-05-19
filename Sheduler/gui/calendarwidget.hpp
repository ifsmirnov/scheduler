#ifndef CALENDARWIDGET_HPP
#define CALENDARWIDGET_HPP

#include <QWidget>
#include <QLabel>

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
    void dayPressed(QDate date);
    void setDate(QDate date);

public:
    void setCalendar(Calendar *newCalendar);

private:
    Calendar *calendar;
    DayWidget *dayWidget;
    MonthWidget *monthWidget;

    QLabel *title;
    
};

#endif // CALENDARWIDGET_HPP

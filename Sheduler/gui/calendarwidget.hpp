#ifndef CALENDARWIDGET_HPP
#define CALENDARWIDGET_HPP

#include <QWidget>

#include "src/calendar/calendar.hpp"
#include "src/managers/schedulemanager.hpp"
#include "gui/daywidget.hpp"

class CalendarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CalendarWidget(QDate date, ScheduleManager *manager, QWidget *parent = 0);
    ~CalendarWidget();
    
signals:
    
public slots:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *);

    void setHighlight(QDate date);
    void noHighlight();

public:
    bool hasHighlight() const;

private:
    Calendar *calendar;
    int curYear, curMonth, curDay;

    ScheduleManager *manager;
    DayWidget *dayWidget;
    
};

#endif // CALENDARWIDGET_HPP

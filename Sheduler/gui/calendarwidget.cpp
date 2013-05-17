#include "calendarwidget.hpp"

#include <iostream>

#include <QPainter>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QFrame>

CalendarWidget::CalendarWidget(QDate date, Calendar *calendar, QWidget *parent) :
    QWidget(parent), calendar(calendar), dayWidget(nullptr)
{
    std::cerr << "CW created" << std::endl;
    setHighlight(date);
    noHighlight();

    QHBoxLayout *layout = new QHBoxLayout(this);
    monthWidget = new MonthWidget(calendar->getManager(), date, this);
    layout->addWidget(monthWidget);

    connect(monthWidget, SIGNAL(dayPressedSignal(int)),
            this, SLOT(dayPressed(int)));
}

CalendarWidget::~CalendarWidget()
{
    std::cerr << "Calendar widget removed" << std::endl;
}

void CalendarWidget::closeEvent(QCloseEvent *)
{
    if (dayWidget) {
        dayWidget->close();
        delete dayWidget;
    }
}

void CalendarWidget::noHighlight()
{
    std::cerr << "set nohl" << std::endl;
    curDay = -1;
    if (dayWidget) {
        delete dayWidget;
    }
}

void CalendarWidget::dayPressed(int day)
{
    std::cerr << "dp " << day << std::endl;
    if (monthWidget->hasHighlight()) {
        monthWidget->noHighlight();
        if (dayWidget) {
            delete dayWidget;
        }
    }
    else {
        QDate date(curYear, curMonth, day + 1);
        monthWidget->setHighlight(date);
        dayWidget = new DayWidget(calendar->getManager(), date);

        connect(dayWidget, SIGNAL(dateChanged(QDate)),
                monthWidget, SLOT(setHighlight(QDate)));
        connect(dayWidget, SIGNAL(addIrregularEvent(QDate,Event*)),
                calendar, SLOT(addIrregularEvent(QDate,Event*)));
        connect(dayWidget, SIGNAL(closed()),
                monthWidget, SLOT(noHighlight()));

        dayWidget->show();
    }
}

bool CalendarWidget::hasHighlight() const
{
    return curDay != -1;
}

void CalendarWidget::setCalendar(Calendar *newCalendar)
{
    calendar = newCalendar;
}

void CalendarWidget::setHighlight(QDate date)
{
    curYear = date.year();
    curMonth = date.month();
    curDay = date.day();
}

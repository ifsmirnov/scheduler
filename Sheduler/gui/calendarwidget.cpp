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

    QHBoxLayout *layout = new QHBoxLayout(this);
    monthWidget = new MonthWidget(calendar->getManager(), date, this);
    layout->addWidget(monthWidget);

    connect(monthWidget, SIGNAL(dayPressedSignal(QDate)),
            this, SLOT(dayPressed(QDate)));
    connect(monthWidget, SIGNAL(monthChanged(QDate)),
            this, SLOT(setDate(QDate)));
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

void CalendarWidget::dayPressed(QDate date)
{
    if (monthWidget->hasHighlight()) {
        monthWidget->noHighlight();
        if (dayWidget) {
            delete dayWidget;
        }
    }
    else
    {
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

void CalendarWidget::setDate(QDate date)
{
    curYear = date.year();
    curMonth = date.month();
    curDay = date.day();
}

void CalendarWidget::setCalendar(Calendar *newCalendar)
{
    calendar = newCalendar;
    monthWidget->setManager(calendar->getManager());
}


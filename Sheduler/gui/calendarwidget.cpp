#include "calendarwidget.hpp"

#include <iostream>

#include <QPainter>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QSizePolicy>
#include <QVBoxLayout>
#include <QFrame>
#include <QTimer>

#include "gui/weekwidget.hpp"
#include "gui/eventslist.hpp"

CalendarWidget::CalendarWidget(QDate date, Calendar *calendar, QWidget *parent) :
    QWidget(parent), calendar(calendar), dayWidget(nullptr), weekWidget(nullptr)
{
    // month widget
    monthWidget = new MonthWidget(calendar->getManager(), date, this);
    connect(monthWidget, SIGNAL(dayPressedSignal(QDate)),
            this, SLOT(dayPressed(QDate)));
    connect(monthWidget, SIGNAL(monthChanged(QDate)),
            this, SLOT(setDate(QDate)));

    // week button
    QPushButton *weekButton = new QPushButton("week");
    connect(weekButton, SIGNAL(clicked()),
            this, SLOT(displayWeek()));

    // title
    title = new QLabel("some text here");
    title->setFont(QFont("Courier", 15));
    title->setAlignment(Qt::AlignCenter);

    // event list
    eventList = new EventsList(QDate::currentDate().addDays(-10),
                                           QDate::currentDate().addDays(10),
                                           calendar->getManager(), this);

    // widgets layout (month and events list)
    QHBoxLayout *widgetsLayout = new QHBoxLayout;
    widgetsLayout->addWidget(monthWidget);
    widgetsLayout->addWidget(eventList);

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(title);
    mainLayout->addLayout(widgetsLayout);
    mainLayout->addWidget(weekButton);

    setDate(date);
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
    date_ = date;
    title->setText(date.toString("MMMM yyyy"));
    update();
}

void CalendarWidget::displayWeek()
{
    if (weekWidget == nullptr) {
        weekWidget = new WeekWidget(date_, calendar->getManager());
        connect(weekWidget, SIGNAL(closed()),
                this, SLOT(closeWeek()));
        connect(weekWidget, SIGNAL(addWeeklyWidget(int,Event*)),
                calendar, SLOT(addWeeklyEvent(int,Event*)));
        weekWidget->show();
    }
}

void CalendarWidget::closeWeek()
{
    if (weekWidget != nullptr) {
        weekWidget->close();
        delete weekWidget;
        weekWidget = nullptr;
    }
}

void CalendarWidget::setCalendar(Calendar *newCalendar)
{
    calendar = newCalendar;
    monthWidget->setManager(calendar->getManager());
    eventList->setManager(calendar->getManager());
}


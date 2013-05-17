#include "monthwidget.hpp"

#include <iostream>

#include <QPainter>
#include <QGridLayout>
#include <QMouseEvent>

MonthWidget::MonthWidget(ScheduleManager *manager, QDate date, QWidget *parent) :
    QWidget(parent), manager(manager)
{
    coveredDay = -1;
    date.setDate(date.year(), date.month(), 1);

    curDay = -1;
    curMonth = date.month();
    curYear = date.year();

    QGridLayout *layout = new QGridLayout(this);

    days.resize(date.daysInMonth());
    for (int day = 0; day < date.daysInMonth(); day++, date = date.addDays(1)) {
        days[day] = new DayOfMonth(manager, date, this);
        days[day]->setMinimumSize(50, 50);

        connect(days[day], SIGNAL(dayCovered(int)),
                this, SLOT(dayCovered(int)));
        connect(days[day], SIGNAL(dayPressed(int)),
                this, SLOT(dayPressed(int)));

        layout->addWidget(days[day], day/7, day%7);
    }

    setLayout(layout);

    setMouseTracking(true);
}

MonthWidget::~MonthWidget()
{
    for (auto day: days) {
        delete day;
    }
}

void MonthWidget::setHighlight(QDate date)
{
    if (curDay != date.day() && curDay != -1) {
        days[curDay - 1]->setHighlited(false);
    }
    curYear = date.year();
    curMonth = date.month();
    curDay = date.day();
    days[curDay - 1]->setHighlited(true);

    update();
}

void MonthWidget::noHighlight()
{
    if (curDay != -1) {
        days[curDay - 1]->setHighlited(false);
    }
    curDay = -1;

    update();
}

void MonthWidget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
}

void MonthWidget::mouseMoveEvent(QMouseEvent *)
{
    if (coveredDay != -1) {
        days[coveredDay]->setCovered(false);
        coveredDay = -1;
        update();
    }
}

void MonthWidget::dayPressed(int day)
{
    std::cerr << "Mouse button pressed on day " << day << std::endl;
    emit dayPressedSignal(day);
}

void MonthWidget::dayCovered(int day)
{
    if (coveredDay != -1 && coveredDay != day) {
        days[coveredDay]->setCovered(false);
        coveredDay = -1;
    }
    if (coveredDay == -1) {
        coveredDay = day;
        days[coveredDay]->setCovered(true);
        update();
    }
}

bool MonthWidget::hasHighlight() const
{
    return curDay != -1;
}


DayOfMonth::DayOfMonth(ScheduleManager *manager, QDate date, QWidget *parent) :
    QWidget(parent), manager(manager), date(date)
{
    covered = false;
    highlited = false;
    setMouseTracking(true);
}

DayOfMonth::DayOfMonth(const DayOfMonth &dayOfMonth) :
    QWidget(dayOfMonth.parentWidget())
{
    manager = dayOfMonth.manager;
    date = dayOfMonth.date;
}

DayOfMonth DayOfMonth::operator =(const DayOfMonth &dayOfMonth)
{
    setParent(dayOfMonth.parentWidget());
    manager = dayOfMonth.manager;
    date = dayOfMonth.date;
    return *this;
}

void DayOfMonth::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (covered) {
        painter.setBrush(palette().dark());
    }
    else if (highlited) {
        painter.setBrush(palette().alternateBase());
    }
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
    painter.setBrush(palette().background());
    QString text = QString::number(date.day()) +
            "\n" +
            QString::number(manager->getEvents(date).size());
    painter.drawText(rect().adjusted(5, 5, 0, 0), text);
}

void DayOfMonth::mousePressEvent(QMouseEvent *)
{
    emit dayPressed(date.day() - 1);
}

void DayOfMonth::mouseMoveEvent(QMouseEvent *)
{
    if (!covered) {
        emit dayCovered(date.day() - 1);
    }
}

bool DayOfMonth::getCovered() const
{
    return covered;
}

void DayOfMonth::setCovered(bool value)
{
    covered = value;
}

bool DayOfMonth::getHighlited() const
{
return highlited;
}

void DayOfMonth::setHighlited(bool value)
{
highlited = value;
}

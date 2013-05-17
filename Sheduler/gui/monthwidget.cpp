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

    setHighlight(date);
    noHighlight();

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
    curYear = date.year();
    curMonth = date.month();
    curDay = date.day();
}

void MonthWidget::noHighlight()
{
    curDay = -1;
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


DayOfMonth::DayOfMonth(ScheduleManager *manager, QDate date, QWidget *parent) :
    QWidget(parent), manager(manager), date(date)
{
    covered = false;
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
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
    if (covered) {
        painter.setBrush(palette().background());
    }
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

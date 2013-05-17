#include "monthwidget.hpp"

#include <QPainter>
#include <QGridLayout>

MonthWidget::MonthWidget(ScheduleManager *manager, QDate date, QWidget *parent) :
    QWidget(parent), manager(manager)
{
    date.setDate(date.year(), date.month(), 1);

    setHighlight(date);
    noHighlight();

    QGridLayout *layout = new QGridLayout(this);

    days.resize(date.daysInMonth());
    for (int day = 0; day < date.daysInMonth(); day++, date = date.addDays(1)) {
        days[day] = new DayOfMonth(manager, date, this);
        days[day]->setMinimumSize(50, 50);
        layout->addWidget(days[day], day/7, day%7);
    }

    setLayout(layout);
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


DayOfMonth::DayOfMonth(ScheduleManager *manager, QDate date, QWidget *parent) :
    QWidget(parent), manager(manager), date(date)
{
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
    QString text = QString::number(date.day()) +
            "\n" +
            QString::number(manager->getEvents(date).size());
    painter.drawText(rect().adjusted(5, 5, 0, 0), text);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
}

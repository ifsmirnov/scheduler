#include "calendarwidget.hpp"

#include <iostream>

#include <QPainter>
#include <QMouseEvent>

CalendarWidget::CalendarWidget(QDate date, Calendar *calendar, QWidget *parent) :
    QWidget(parent), calendar(calendar), dayWidget(nullptr)
{
    std::cerr << "CW created" << std::endl;
    setHighlight(date);
    noHighlight();
}

CalendarWidget::~CalendarWidget()
{
    std::cerr << "Calendar widget removed" << std::endl;
}

void CalendarWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if (hasHighlight()) {
        painter.drawText(rect(), QDate(curYear, curMonth, curDay).toString());
    }
    else {
        painter.drawText(rect(), "No day specified");
    }
}

void CalendarWidget::mousePressEvent(QMouseEvent *event)
{
    std::cerr << "mpe" << std::endl;
    if (event->button() == Qt::LeftButton) {
        if (hasHighlight()) {
            noHighlight();
        }
        else {
            setHighlight(QDate::currentDate());

            dayWidget = new DayWidget(calendar->getManager(), QDate::currentDate());
            connect(dayWidget, SIGNAL(addIrregularEvent(QDate,Event*)),
                    calendar, SLOT(addIrregularEvent(QDate,Event*)));
            connect(dayWidget, SIGNAL(dateChanged(QDate)),
                    this, SLOT(setHighlight(QDate)));
            connect(dayWidget, SIGNAL(closed()),
                    this, SLOT(noHighlight()));

            dayWidget->show();
            std::cerr << "Created dw" << std::endl;
        }
        update();
    }
    else {
        QWidget::mousePressEvent(event);
    }

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

bool CalendarWidget::hasHighlight() const
{
    return curDay != -1;
}

void CalendarWidget::setHighlight(QDate date)
{
    curYear = date.year();
    curMonth = date.month();
    curDay = date.day();
}

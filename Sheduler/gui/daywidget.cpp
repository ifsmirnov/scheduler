#include "daywidget.hpp"

#include <QPainter>

DayWidget::DayWidget(Day* day, QWidget *parent) :
    QWidget(parent), day_(day)
{
}

void DayWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    int coeff = 60 * 60 * 24;

    painter.setBrush(Qt::blue);
    painter.setPen(Qt::blue);
    painter.drawRect(rect());

    QVector<Event*> events = day()->events();

    painter.setBrush(Qt::transparent);

    for (auto event: events) {
        int begin = (double)(QTime(0, 0).secsTo(event->begin())) / coeff * height();
        int len = (double)event->duration() / coeff * height();
        QRect eventRect(rect().left(), begin, rect().width()-1, len);
        if (event->isRegular()) {
            eventRect.adjust(10, 10, -10, -10);
            painter.setPen(Qt::green);
        } else {
            eventRect.adjust(20, 20, -20, -20);
            painter.setPen(Qt::red);
        }
        painter.drawRect(eventRect);
    }
}

Day* DayWidget::day() {
    return day_;
}

QSize DayWidget::sizeHint() const {
    return QSize(240, 600);
}

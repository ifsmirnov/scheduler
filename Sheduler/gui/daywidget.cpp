#include "daywidget.hpp"

#include <QPainter>
#include <iostream>

DayWidget::DayWidget(Day* day, QWidget *parent) :
    QWidget(parent), day_(day)
{
    for (int hour = 0; hour < 24; hour++) {
        hourLabels.push_back(new QLabel(QTime(hour, 0).toString("hh:mm"), this));
    }
}

void DayWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    int coeff = 60 * 60 * 24;
    int height_ = height() - 10;  //for borders at the top and at the bottom of frame

    painter.setBrush(QColor(Qt::green).lighter());
    painter.setPen(Qt::blue);
    painter.drawRect(rect());

    QVector<Event*> events = day()->events();


    painter.setBrush(Qt::transparent);

    for (int hour = 0; hour < 24; hour++) {
        int begin = 5 + (double)(QTime(0, 0).secsTo(QTime(hour, 0))) / coeff * height_;
        int len = (double)(60*60) / coeff * height_;
        hourLabels[hour]->setGeometry(std::max(width() / 10, 50) - 45, begin, std::max(width() / 20, 45), height_ / 24);
        hourLabels[hour]->show();
        QRect eventRect(rect().left(), begin, rect().width()-1, len);
        eventRect.adjust(std::max(width() / 10, 50) , 0, -20, 0);
        painter.setPen(Qt::black);
        painter.setBrush(Qt::white);
        painter.drawRect(eventRect);
    }

    for (auto event: events) {
        int begin = 5 + (double)(QTime(0, 0).secsTo(event->begin())) / coeff * height_;
        int len = (double)event->duration() / coeff * height_;
        //std::cout << event->duration() << ' ' << QTime(0, 0).secsTo(event->begin()) << ' ' << begin << ' ' << len << std::endl;
        QRect eventRect(rect().left(), begin, rect().width()-1, len);
        if (event->isRegular()) {
            eventRect.adjust(std::max(width() / 10, 50), 0, -20, 0);
            painter.setBrush(QColor(Qt::red).lighter(125));
        } else {
            eventRect.adjust(std::max(width() / 10, 50), 0, -20, 0);
            painter.setBrush(QColor(Qt::blue).lighter(125));
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

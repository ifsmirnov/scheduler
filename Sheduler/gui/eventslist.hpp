#ifndef EVENTSLIST_HPP
#define EVENTSLIST_HPP

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QDate>
#include <QTime>
#include <QPainter>
#include <QGridLayout>
#include <QScrollArea>
#include <QScrollBar>
#include <iostream>
#include <src/dailyschedule.hpp>
#include <src/event.hpp>
#include <gui/daywidget.hpp>

class EventsList : public QWidget
{
    Q_OBJECT

private:
    ScheduleManager* manager;
    QDate firstDay;
    QDate lastDay;

public:
    EventsList(QDate firstDay, QDate lastDay, ScheduleManager* manager, QWidget* parent = 0);

signals:

public slots:

};

#endif // EVENTSLIST_HPP
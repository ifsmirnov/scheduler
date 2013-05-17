#ifndef SCHEDULEMANAGER_HPP
#define SCHEDULEMANAGER_HPP

#include <QVector>
#include <QDate>

#include "src/event.hpp"

class ScheduleManager
{
public:
    ScheduleManager() { }
    virtual ~ScheduleManager() { }

public:
    virtual QVector<Event*> getEvents(QDate date) = 0;
};

#endif // SCHEDULEMANAGER_HPP

#ifndef SCHEDULEMANAGER_HPP
#define SCHEDULEMANAGER_HPP

#include <QVector>
#include <QDate>
#include <QDomElement>
#include <QDomDocument>

#include "src/event.hpp"

class ScheduleManager
{
public:
    ScheduleManager() { }
    virtual ~ScheduleManager() { }

public:
    virtual QVector<Event*> getEvents(QDate date) = 0;

    virtual QDomElement serialize(QDomDocument &document);
    static ScheduleManager *deserialize(QDomElement element);
};

#endif // SCHEDULEMANAGER_HPP

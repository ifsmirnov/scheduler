#ifndef WEEKMANAGER_HPP
#define WEEKMANAGER_HPP

#include <QVector>
#include <QDate>

#include "src/managers/schedulemanager.hpp"
#include "src/event.hpp"

class WeekManager : public ScheduleManager
{
public:
    WeekManager();
    virtual ~WeekManager();

public:
    virtual QVector<Event*> getEvents(QDate date);
    void addEvent(Event *event, int dayOfWeek);

private:
    QVector<Event*> events[7];
};

#endif // WEEKMANAGER_HPP

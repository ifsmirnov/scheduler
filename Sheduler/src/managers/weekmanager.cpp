#include "weekmanager.hpp"

WeekManager::WeekManager()
{
    for (int dayOfWeek = 0; dayOfWeek < 7; dayOfWeek++) {
        events[dayOfWeek].clear();
    }
}

WeekManager::~WeekManager()
{
    for (int dayOfWeek = 0; dayOfWeek < 7; dayOfWeek++) {
        for (auto event: events[dayOfWeek]) {
            delete event;
        }
    }
}

QVector<Event *> WeekManager::getEvents(QDate date)
{
    int dayOfWeek = date.dayOfWeek() - 1;
    return events[dayOfWeek];
}

void WeekManager::addEvent(Event *event, int dayOfWeek)
{
    events[dayOfWeek].push_back(event);
}

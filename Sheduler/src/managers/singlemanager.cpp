#include "singlemanager.hpp"

using std::make_pair;

SingleManager::SingleManager()
{
}

SingleManager::~SingleManager()
{
    for (auto event: events) {
        delete event.second;
    }
}

QVector<Event *> SingleManager::getEvents(QDate date)
{
    QVector<Event*> result;
    for (auto i: events) {
        if (i.first == date) {
            result.push_back(i.second);
        }
    }
    return result;
}

void SingleManager::addEvent(Event *event, QDate date)
{
    events.push_back(make_pair(date, event));
}

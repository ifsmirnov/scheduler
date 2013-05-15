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

void SingleManager::addEvent(QDate date, Event *event)
{
    events.push_back(make_pair(date, event));
}

QDomElement SingleManager::serialize(QDomDocument &document)
{
    QDomElement element = document.createElement("manager");
    element.setAttribute("type", "single");

    for (auto i: events) {
        QDomElement child = i.second.serialize(document);
        child.setAttribute("date", i.first.toString("yyyy:mm:dd"));
        element.appendChild(child);
    }

    return element;
}

ScheduleManager *SingleManager::deserialize(QDomElement element)
{
    // TODO
}

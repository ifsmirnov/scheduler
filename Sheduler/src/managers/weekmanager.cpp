#include "weekmanager.hpp"

#include <iostream>

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

void WeekManager::addEvent(int dayOfWeek, Event *event)
{
    events[dayOfWeek].push_back(event);
}

QDomElement WeekManager::serialize(QDomDocument &document)
{
    QDomElement element = document.createElement("manager");
    element.setAttribute("type", "week");

    for (int dayOfWeek = 0; dayOfWeek < 7; dayOfWeek++) {
        for (auto event: events[dayOfWeek]) {
            QDomElement child = event->serialize(document);
            child.setAttribute("weekday", dayOfWeek);
            element.appendChild(child);
        }
    }

    return element;
}

ScheduleManager *WeekManager::deserialize(QDomElement element)
{
    if (element.tagName() != "manager") {
        std::cerr << "Not a manager" << std::endl;
    }

    if (!element.hasAttribute("type") || element.attribute("type") != "week") {
        std::cerr << "Not a week manager" << std::endl;
    }

    WeekManager *manager = new WeekManager;

    for (QDomElement child = element.firstChildElement("event");
         !child.isNull();
         child = child.nextSiblingElement("event")) {
        // TODO existance check
        int dayOfWeek = child.attribute("weekday").toInt();
        Event *event = Event::deserialize(child);
        manager->addEvent(dayOfWeek, event);
    }

    return manager;
}

#include "calendar.hpp"

#include "globalcontainer.hpp"

#include <iostream>

using calendar_containers::GlobalContainer;

Calendar::Calendar(QObject *parent) :
    QObject(parent)
{
    manager = new CollectionManager;
    singleManager = new SingleManager;
    weekManager = new WeekManager;
    manager->addChildManager(singleManager);
    manager->addChildManager(weekManager);
}
Calendar::~Calendar()
{
    delete manager;
}

void Calendar::addIrregularEvent(QDate date, Event *event)
{
    singleManager->addEvent(date, event);
}

void Calendar::addWeeklyEvent(int dayOfWeek, Event *event)
{
    weekManager->addEvent(dayOfWeek, event);
}

ScheduleManager *Calendar::getManager() const
{
    return manager;
}

QDomElement Calendar::serialize(QDomDocument &document) const
{
    QDomElement element = document.createElement("calendar");

    element.appendChild(container->serialize(document));

    return element;
}

Calendar *Calendar::deserialize(QDomElement element)
{
    if (element.tagName() != "calendar") {
        std::cerr << "Not a calendar" << std::endl;
    }

    Calendar *calendar = new Calendar;
    delete calendar->container;

    QDomElement child = element.firstChildElement("container");
    calendar->container = GlobalContainer::deserialize(child);

    return calendar;
}



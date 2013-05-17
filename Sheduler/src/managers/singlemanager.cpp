#include "singlemanager.hpp"

#include <iostream>

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
        QDomElement child = i.second->serialize(document);
        child.setAttribute("date", i.first.toString("yyyy.MM.dd"));
        element.appendChild(child);
    }

    return element;
}

ScheduleManager *SingleManager::deserialize(QDomElement element)
{
    if (element.tagName() != "manager") {
        std::cerr << "Not a manager" << std::endl;
    }

    if (!element.hasAttribute("type") || element.attribute("type") != "single") {
        std::cerr << "Not a single manager" << std::endl;
        std::cerr << element.text().toStdString() << std::endl;
    }

    SingleManager *manager = new SingleManager;

    for (QDomElement child = element.firstChildElement("event");
         !child.isNull();
         child = child.nextSiblingElement("event")) {
        // TODO existance check
        QDate date = QDate::fromString(child.attribute("date"), "yyyy.MM.dd");
        Event *event = Event::deserialize(child);
        manager->addEvent(date, event);
        std::cerr << "Add event to child" << std::endl;
    }

    return manager;
}

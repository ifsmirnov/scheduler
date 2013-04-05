#include "dailyschedule.hpp"

#include <iostream>

DailySchedule::DailySchedule()
{
    ++count;
}

DailySchedule::~DailySchedule()
{
    --count;
    for (auto event: events_) {
        delete event;
    }
}

QVector<Event*> DailySchedule::events()
{
    return events_;
}
QVector<RegularEvent*> DailySchedule::regularEvents()
{
    QVector<RegularEvent*> result;
    for (auto event: events_) {
        if (event->isRegular()) {
            result.push_back(dynamic_cast<RegularEvent*>(event));
        }
    }
    return result;
}
QVector<IrregularEvent*> DailySchedule::irregularEvents()
{
    QVector<IrregularEvent*> result;
    for (auto event: events_) {
        if (!event->isRegular()) {
            result.push_back(dynamic_cast<IrregularEvent*>(event));
        }
    }
    return result;
}

DailyScheduleSPtr DailySchedule::clone()
{
    DailySchedule *newSchedule = new DailySchedule;
    for (auto event: events_) {
        newSchedule->addEvent(event->clone());
    }
    return DailyScheduleSPtr(newSchedule);
}

void DailySchedule::addEvent(Event *event)
{
    events_.push_back(event);
}

QDomElement DailySchedule::serialize(QDomDocument &document) const
{
    QDomElement element = document.createElement("schedule");

    for (auto event: events_) {
        element.appendChild(event->serialize(document));
    }

    return element;
}

std::shared_ptr<DailySchedule> DailySchedule::deserialize(QDomElement element)
{
    if (element.tagName() != "schedule") {
        std::cerr << "Not a schedule" << std::endl;
    }

    DailySchedule* schedule = new DailySchedule;

    for (QDomElement child = element.firstChildElement("event");
         !child.isNull();
         child = child.nextSiblingElement("event")) {
        schedule->addEvent(Event::deserialize(child));
    }

    return DailyScheduleSPtr(schedule);
}

int DailySchedule::count = 0;

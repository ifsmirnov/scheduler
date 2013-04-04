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

int DailySchedule::count = 0;

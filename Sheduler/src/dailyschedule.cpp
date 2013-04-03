#include "dailyschedule.hpp"

DailySchedule::DailySchedule()
{
}

DailySchedule::~DailySchedule()
{
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

void DailySchedule::addEvent(Event *event)
{
    events_.push_back(event);
}

#include "calendar.hpp"

#include <stdexcept>
#include <algorithm>

Calendar::Calendar(QObject *parent) :
    QObject(parent)
{
}

Calendar::~Calendar()
{
    for (auto day: days) {
        delete day;
    }
    for (auto event: events) {
        delete event;
    }
}

void Calendar::addDay(Day *day)
{
    for (const auto &day_: days) {
        if (day_->date() == day->date()) {
            throw std::invalid_argument("day with this date already exists");
        }
    }
    days.push_back(day);
}
void Calendar::addEvent(Event *event, const QDate &date)
{
    Day *associatedDay = nullptr;
    for (auto day: days) {
        if (day->date() == date) {
            associatedDay = day;
            break;
        }
    }

    if (associatedDay == nullptr) {
        throw std::invalid_argument("event is not associated with any valid day");
    }

    events.push_back(event);
    associatedDay->addEvent(event);
}

QVector<Day*> Calendar::getDaysInRange(const QDate &begin, const QDate &end)
{
    QVector<Day*> result;
    for (auto day: days) {
        if (begin <= day->date() && day->date() <= end) {
            result.push_back(day);
        }
    }
    std::sort(result.begin(), result.end(), compareDayPointers);
    return result;
}

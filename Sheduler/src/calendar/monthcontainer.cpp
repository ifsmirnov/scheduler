#include "monthcontainer.hpp"

namespace calendar_containers {

MonthContainer::MonthContainer()
{
    entries.resize(31);
}

MonthContainer::~MonthContainer()
{
}

void MonthContainer::getDaysInRange(QDate begin,
                                    QDate end,
                                    QVector<DailyScheduleSPtr> &result)
{
    int firstDay = begin.day() - 1;
    int lastDay = end.day() - 1;
    for (int day = firstDay; day <= lastDay; day++) {
        if (entries[day] != nullptr) {
            result.push_back(entries[day]);
        }
    }
}
void MonthContainer::setSchedule(QDate date, DailyScheduleSPtr schedule)
{
    entries[date.day() - 1] = schedule;
}

QDomElement MonthContainer::serialize(QDomDocument &document) const
{
    QDomElement element = document.createElement("container");

    element.setAttribute("type", "month");

    for (int i = 0; i < 31; i++) {
        if (entries[i] != nullptr) {
            QDomElement child = entries[i]->serialize(document);
            child.setAttribute("day", i + 1);
            element.appendChild(child);
        }
    }

    return element;
}

} // calendar_containers

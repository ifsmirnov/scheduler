#include "monthcontainer.hpp"

#include <iostream>

namespace calendar_containers {

MonthContainer::MonthContainer()
{
    ++count;
    entries.resize(31);
}

MonthContainer::~MonthContainer()
{
    --count;
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

MonthContainer *MonthContainer::deserialize(QDomElement element)
{
    if (element.tagName() != "container") {
        std::cerr << "Not a container" << std::endl;
    }
    if (!element.hasAttribute("type") || element.attribute("type") != "month") {
        std::cerr << "Not a month container" << std::endl;
    }

    MonthContainer *container = new MonthContainer;

    for (QDomElement child = element.firstChildElement("schedule");
         !child.isNull();
         child = child.nextSiblingElement("schedule")) {
        DailyScheduleSPtr schedule = DailySchedule::deserialize(child);
        int day = child.attribute("day").toInt() - 1;
        container->entries[day] = schedule;
    }

    return container;
}

int MonthContainer::count = 0;

} // calendar_containers

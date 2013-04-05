#include "yearcontainer.hpp"

namespace calendar_containers {

YearContainer::YearContainer()
{
    entries.resize(12);
}

YearContainer::~YearContainer()
{
    for (auto i: entries) {
        if (i != nullptr) {
            delete i;
        }
    }
}

void YearContainer::getDaysInRange(QDate begin,
                                   QDate end,
                                   QVector<DailyScheduleSPtr> &result)
{
    int firstMonth = begin.month();
    int lastMonth = end.month();
    for (int month = firstMonth; month <= lastMonth; month++) {
        if (entries[month - 1] == nullptr) {
            continue;
        }

        QDate childBegin(begin.year(), month, 1);
        QDate childEnd(begin.year(), month, 1);
        childEnd.setDate(begin.year(), month, childEnd.daysInMonth());

        if (month == firstMonth) {
            childBegin.setDate(childBegin.year(), childBegin.month(), begin.day());
        }
        if (month == lastMonth) {
            childEnd.setDate(childEnd.year(), childEnd.month(), end.day());
        }
        entries[month - 1]->getDaysInRange(childBegin, childEnd, result);
    }
}

void YearContainer::setSchedule(QDate date, DailyScheduleSPtr schedule)
{
    int id = date.month() - 1;
    if (entries[id] == nullptr) {
        entries[id] = new MonthContainer;
    }
    entries[id]->setSchedule(date, schedule);
}

QDomElement YearContainer::serialize(QDomDocument &document) const
{
    QDomElement element = document.createElement("container");

    element.setAttribute("type", "year");
    for (int i = 0; i < 12; i++) {
        MonthContainer *month = entries[i];
        if (month != nullptr) {
            QDomElement child = month->serialize(document);
            child.setAttribute("month", QString::number(i + 1));
            element.appendChild(child);
        }
    }

    return element;
}

YearContainer *YearContainer::deserialize(QDomElement element)
{
    if (element.tagName() != "container") {
        std::cerr << "Not a container" << std::endl;
    }
    if (!element.hasAttribute("type") || element.attribute("type") != "year") {
        std::cerr << "Not a year container" << std::endl;
    }

    YearContainer *container = new YearContainer;

    for (QDomElement child = element.firstChildElement("container");
         !child.isNull();
         child = child.nextSiblingElement("container")) {
        int month = child.attribute("month").toInt();
        container->entries[month - 1] = MonthContainer::deserialize(child);
    }

    return container;
}

} // calendar_containers

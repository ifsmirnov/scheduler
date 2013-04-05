#include "globalcontainer.hpp"

namespace calendar_containers {

GlobalContainer::GlobalContainer()
{
    ++count;
}

GlobalContainer::~GlobalContainer()
{
    --count;
    for (auto i: years) {
        delete i.second;
    }
}

void GlobalContainer::getDaysInRange(QDate begin,
                                     QDate end,
                                     QVector<DailyScheduleSPtr> &result)
{
    int firstYear = begin.year();
    int lastYear = end.year();
    for (int year = firstYear; year <= lastYear; ++year) {
        QDate childBegin(year, 1, 1);
        QDate childEnd(year, 12, 31);

        if (year == firstYear) {
            childBegin.setDate(childBegin.year(), begin.month(), begin.day());
        }
        if (year == lastYear) {
            childEnd.setDate(childEnd.year(), end.month(), end.day());
        }

        std::map<int, YearContainer*>::iterator it = years.find(year);
        if (it != years.end()) {
            it->second->getDaysInRange(childBegin, childEnd, result);
        }
    }
}

void GlobalContainer::setSchedule(QDate date, DailyScheduleSPtr schedule)
{
    if (years.find(date.year()) == years.end()) {
        years[date.year()] = new YearContainer;
    }
    years[date.year()]->setSchedule(date, schedule);
}

QDomElement GlobalContainer::serialize(QDomDocument &document) const
{
    QDomElement element = document.createElement("container");

    element.setAttribute("type", "global");

    for (auto i: years) {
        QDomElement child = i.second->serialize(document);
        child.setAttribute("year", i.first);
        element.appendChild(child);
    }

    return element;
}

GlobalContainer *GlobalContainer::deserialize(QDomElement element)
{
    if (element.tagName() != "container") {
        std::cerr << "Not a container";
    }
    if (!element.hasAttribute("type") || element.attribute("type") != "global") {
        std::cerr << "Not a global container";
    }

    GlobalContainer *container = new GlobalContainer;

    for (QDomElement child = element.firstChildElement("container");
         !child.isNull();
         child = child.nextSiblingElement("container")) {
        int year = child.attribute("year").toInt();
        container->years[year] = YearContainer::deserialize(child);
    }

    return container;
}

int GlobalContainer::count = 0;

} // calendar_containers

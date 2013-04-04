#include "calendar.hpp"

#include "globalcontainer.hpp"

#include <iostream>

using calendar_containers::GlobalContainer;

Calendar::Calendar(QObject *parent) :
    QObject(parent)
{
    container = new GlobalContainer;
}
Calendar::~Calendar()
{
    delete container;
}

void Calendar::setSchedule(QDate date, DailyScheduleSPtr schedule)
{
    container->setSchedule(date, schedule);
}

QVector<DailyScheduleSPtr> Calendar::getDaysInRange(QDate begin, QDate end)
{
    QVector<DailyScheduleSPtr> result;
    container->getDaysInRange(begin, end, result);
    return result;
}

QDomElement Calendar::serialize(QDomDocument &document) const
{
    QDomElement element = document.createElement("calendar");

    element.appendChild(container->serialize(document));

    return element;
}



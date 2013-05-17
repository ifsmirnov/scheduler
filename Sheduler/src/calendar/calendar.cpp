#include "calendar.hpp"

#include "globalcontainer.hpp"

#include <iostream>

#include <QFile>
#include <QString>
#include <QIODevice>
#include <QDomDocument>
#include <QDomElement>

using calendar_containers::GlobalContainer;

Calendar::Calendar(QObject *parent) :
    QObject(parent)
{
    manager = new CollectionManager;
    singleManager = new SingleManager;
    weekManager = new WeekManager;
    manager->addChildManager(singleManager);
    manager->addChildManager(weekManager);
}

Calendar::Calendar(SingleManager *singleManager, WeekManager *weekManager, QObject *parent) :
    QObject(parent), singleManager(singleManager), weekManager(weekManager)
{
    manager = new CollectionManager;
    manager->addChildManager(singleManager);
    manager->addChildManager(weekManager);
}
Calendar::~Calendar()
{
    std::cerr << "Quit, there are " << manager->getEvents(QDate::currentDate()).size() <<
                 " events today" << std::endl;

    /*QFile file("/tmp/ser");
    file.open(QIODevice::WriteOnly);

    QDomDocument document;
    document.appendChild(serialize(document));

    file.write(document.toString(2).toAscii());
    file.close();*/

    delete manager;
}

void Calendar::addIrregularEvent(QDate date, Event *event)
{
    singleManager->addEvent(date, event);
}

void Calendar::addWeeklyEvent(int dayOfWeek, Event *event)
{
    weekManager->addEvent(dayOfWeek, event);
}

ScheduleManager *Calendar::getManager() const
{
    return manager;
}

QDomElement Calendar::serialize(QDomDocument &document) const
{
    QDomElement element = document.createElement("calendar");

    element.appendChild(singleManager->serialize(document));
    element.appendChild(weekManager->serialize(document));

    return element;
}

Calendar *Calendar::deserialize(QDomElement element)
{
    if (element.tagName() != "calendar") {
        std::cerr << "Not a calendar" << std::endl;
    }

    SingleManager *singleManager = nullptr;
    WeekManager *weekManager = nullptr;

    for (QDomElement child = element.firstChildElement("manager");
         !child.isNull();
         child = child.nextSiblingElement("manager")) {
        ScheduleManager *value = ScheduleManager::deserialize(child);
        if (child.attribute("type") == "single") {
            singleManager = dynamic_cast<SingleManager*>(value);
        }
        else if (child.attribute("type") == "week") {
            weekManager = dynamic_cast<WeekManager*>(value);
        }
    }

    if (singleManager == nullptr || weekManager == nullptr) {
        std::cerr << "Child managers deserialized incorrectly!" << std::endl;
    }

    return new Calendar(singleManager, weekManager);
}



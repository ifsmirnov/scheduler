#include "collectionmanager.hpp"

#include <iostream>

CollectionManager::CollectionManager()
{
}

CollectionManager::~CollectionManager()
{
    for (auto manager: managers) {
        delete manager;
    }
}

QVector<Event *> CollectionManager::getEvents(QDate date)
{
    QVector<Event*> result;
    for (auto manager: managers) {
        result += manager->getEvents(date);
    }
    return result;
}

ScheduleManager *CollectionManager::addChildManager(ScheduleManager *manager)
{
    managers.push_back(manager);
    return manager;
}

QDomElement CollectionManager::serialize(QDomDocument &document)
{
    QDomElement element = document.createElement("manager");
    element.setAttribute("type", "collection");

    for (auto manager: managers) {
        element.appendChild(manager->serialize(document));
    }

    return element;
}

ScheduleManager *CollectionManager::deserialize(QDomElement element)
{
    if (element.tagName() != "manager") {
        std::cerr << "Not a manager" << std::endl;
    }

    if (!element.hasAttribute("type") || element.attribute("type") != "collection") {
        std::cerr << "Not a collection manager" << std::endl;
    }

    CollectionManager *manager = new CollectionManager;
    for (QDomElement child = element.firstChildElement("manager");
         !child.isNull();
         child = child.nextSiblingElement("manager")) {
        manager->addChildManager(ScheduleManager::deserialize(child));
    }

    return manager;
}

/*int CollectionManager::childCount() const
{
    return managers.size();
}

ScheduleManager *CollectionManager::getChildManager(int id)
{
    return managers[id];
}
*/

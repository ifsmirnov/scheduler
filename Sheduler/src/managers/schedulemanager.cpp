#include "schedulemanager.hpp"

//ScheduleManager* ScheduleManager::deserialize(QDomElement element)
//{
//TODO
//}

#include <iostream>

#include <QString>

#include "src/managers/collectionmanager.hpp"
#include "src/managers/singlemanager.hpp"
#include "src/managers/weekmanager.hpp"

ScheduleManager *ScheduleManager::deserialize(QDomElement element)
{
    if (element.tagName() != "manager") {
        std::cerr << "Not a manager" << std::endl;
    }

    if (!element.hasAttribute("type")) {
        std::cerr << "Type not specified" << std::endl;
    }

    QString type = element.attribute("type");

    if (type == "single") {
        return SingleManager::deserialize(element);
    }
    else if (type == "week") {
        return SingleManager::deserialize(element);
    }
    else if (type == "collection") {
        return CollectionManager::deserialize(element);
    }
    else {
        std::cerr << "Incorrect manager type" << std::endl;
        return nullptr;
    }
}

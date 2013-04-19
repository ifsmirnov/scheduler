#include "collectionmanager.hpp"

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

int CollectionManager::addChildManager(ScheduleManager *manager)
{
    managers.push_back(manager);
    return managers.size() - 1;
}

int CollectionManager::childCount() const
{
    return managers.size();
}

ScheduleManager *CollectionManager::getChildManager(int id)
{
    return managers[id];
}

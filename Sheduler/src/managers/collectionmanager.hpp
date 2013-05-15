#ifndef COLLECTIONMANAGER_HPP
#define COLLECTIONMANAGER_HPP

#include <QVector>
#include <QDate>

#include "src/managers/schedulemanager.hpp"
#include "src/event.hpp"

class CollectionManager : public ScheduleManager
{
public:
    CollectionManager();
    virtual ~CollectionManager();

public:
    virtual QVector<Event*> getEvents(QDate date);

    ScheduleManager* addChildManager(ScheduleManager *manager); // returns id
    //int childCount() const;
    //ScheduleManager *getChildManager(int id);

private:
    QVector<ScheduleManager*> managers;
};

#endif // COLLECTIONMANAGER_HPP

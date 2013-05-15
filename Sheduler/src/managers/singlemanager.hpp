#ifndef SINGLEMANAGER_HPP
#define SINGLEMANAGER_HPP

#include <utility>

#include <QVector>
#include <QDate>

#include "src/managers/schedulemanager.hpp"
#include "src/event.hpp"

using std::pair;

class SingleManager : public ScheduleManager
{
public:
    SingleManager();
    virtual ~SingleManager();

public:
    virtual QVector<Event*> getEvents(QDate date);
    void addEvent(QDate date, Event *event);

    virtual QDomElement serialize(QDomDocument &document);
    static ScheduleManager *deserialize(QDomElement element);


private:
    QVector<pair<QDate, Event*> > events;
};

#endif // SINGLEMANAGER_HPP

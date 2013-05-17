#ifndef CALENDAR_HPP
#define CALENDAR_HPP

#include <memory>

#include <QObject>
#include <QDate>
#include <QVector>
#include <QDomElement>
#include <QDomDocument>

#include "src/dailyschedule.hpp"
#include "src/managers/schedulemanager.hpp"
#include "src/managers/collectionmanager.hpp"
#include "src/managers/singlemanager.hpp"
#include "src/managers/weekmanager.hpp"

class Calendar : public QObject
{
    Q_OBJECT
public:
    explicit Calendar(QObject *parent = 0);
    Calendar(SingleManager *singleManager, WeekManager *weekManager, QObject *parent = 0);
    ~Calendar();
    
public slots:
    void addIrregularEvent(QDate date, Event *event);
    void addWeeklyEvent(int dayOfWeek, Event *event);

public:
    ScheduleManager* getManager() const;
    QDomElement serialize(QDomDocument &document) const;
    static Calendar *deserialize(QDomElement element);
    
private:
    CollectionManager *manager;
    SingleManager *singleManager;
    WeekManager *weekManager;
    
};

#endif // CALENDAR_HPP

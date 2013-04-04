#ifndef GLOBALCONTAINER_HPP
#define GLOBALCONTAINER_HPP

#include <map>

#include <QVector>
#include <QDate>

#include "container.hpp"
#include "yearcontainer.hpp"

namespace calendar_containers {

class GlobalContainer : public Container
{
public:
    GlobalContainer();
    virtual ~GlobalContainer();

public:
    virtual void getDaysInRange(QDate begin,
                        QDate end,
                        QVector<DailyScheduleSPtr> &result);
    virtual void setSchedule(QDate date, DailyScheduleSPtr schedule);

    virtual QDomElement serialize(QDomDocument &document) const;

private:
    std::map<int, YearContainer*> years;

};

} // calendar_containers

#endif // GLOBALCONTAINER_HPP

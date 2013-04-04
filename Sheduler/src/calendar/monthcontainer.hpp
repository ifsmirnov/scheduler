#ifndef MONTHCONTAINER_HPP
#define MONTHCONTAINER_HPP

#include <QVector>
#include <QDate>

#include "container.hpp"
#include "src/dailyschedule.hpp"

namespace calendar_containers {

class MonthContainer : public Container
{
public:
    MonthContainer();
    virtual ~MonthContainer();

public:
    virtual void getDaysInRange(QDate begin,
                                QDate end,
                                QVector<DailyScheduleSPtr> &result);
    virtual void setSchedule(QDate date, DailyScheduleSPtr schedule);

    virtual QDomElement serialize(QDomDocument &document) const;
    static MonthContainer *deserialize(QDomElement element);

public:
    static int count;

private:
    QVector<DailyScheduleSPtr> entries;
};

} // calendar_containers

#endif // MONTHCONTAINER_HPP

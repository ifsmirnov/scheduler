#ifndef YEARCONTAINER_HPP
#define YEARCONTAINER_HPP

#include <QVector>
#include <QDate>

#include "container.hpp"
#include "monthcontainer.hpp"

namespace calendar_containers {

class YearContainer : public Container
{
public:
    YearContainer();
    ~YearContainer();

public:
    void getDaysInRange(QDate begin,
                        QDate end,
                        QVector<DailyScheduleSPtr> &result);
    virtual void setSchedule(QDate date, DailyScheduleSPtr schedule);

    virtual QDomElement serialize(QDomDocument &document) const;
    static YearContainer *deserialize(QDomElement element);

private:
    QVector<MonthContainer*> entries;
};

} // calendar_containers

#endif // YEARCONTAINER_HPP

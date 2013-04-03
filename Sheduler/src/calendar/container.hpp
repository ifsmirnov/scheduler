#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <iostream>
// TODO: get rid of iostream

#include <QVector>
#include <QDate>

#include "src/dailyschedule.hpp"

namespace calendar_containers {

/**
 * @brief The Container class contains schedule entries for some set of days,
 *  e.g. a year or a month. The only its ability is to return days which
 *  belong to a given date interval.
 */
class Container
{
public:
    Container() { }
    virtual ~Container() { }

public:
    virtual void getDaysInRange(QDate begin,
                                QDate end,
                                QVector<DailyScheduleSPtr> &result) = 0;
    virtual void setSchedule(QDate date, DailyScheduleSPtr schedule) = 0;
};

} // calendar_containers

#endif // CONTAINER_HPP

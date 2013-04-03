#include "yearcontainer.hpp"

namespace calendar_containers {

YearContainer::YearContainer()
{
    entries.resize(12);
}

YearContainer::~YearContainer()
{
}

void YearContainer::getDaysInRange(QDate begin,
                                   QDate end,
                                   QVector<DailyScheduleSPtr> &result)
{
    int firstMonth = begin.month();
    int lastMonth = end.month();
    for (int month = firstMonth; month <= lastMonth; month++) {
        QDate childBegin(begin.year(), month, 1);
        QDate childEnd(begin.year(), month, 1);
        childEnd.setDate(begin.year(), month, childEnd.daysInMonth());

        if (month == firstMonth) {
            childBegin.setDate(childBegin.year(), childBegin.month(), begin.day());
        }
        if (month == lastMonth) {
            childEnd.setDate(childEnd.year(), childEnd.month(), end.day());
        }
        entries[month - 1].getDaysInRange(childBegin, childEnd, result);
    }
}

void YearContainer::setSchedule(QDate date, DailyScheduleSPtr schedule)
{
    entries[date.month() - 1].setSchedule(date, schedule);
}

} // calendar_containers

#include "globalcontainer.hpp"

namespace calendar_containers {

GlobalContainer::GlobalContainer()
{
}

GlobalContainer::~GlobalContainer()
{
}

void GlobalContainer::getDaysInRange(QDate begin,
                                     QDate end,
                                     QVector<DailyScheduleSPtr> &result)
{
    int firstYear = begin.year();
    int lastYear = end.year();
    for (int year = firstYear; year <= lastYear; ++year) {
        QDate childBegin(year, 1, 1);
        QDate childEnd(year, 12, 31);

        if (year == firstYear) {
            childBegin.setDate(childBegin.year(), begin.month(), begin.day());
        }
        if (year == lastYear) {
            childEnd.setDate(childEnd.year(), end.month(), end.day());
        }

        std::map<int, YearContainer>::iterator it = years.find(year);
        if (it != years.end()) {
            it->second.getDaysInRange(childBegin, childEnd, result);
        }
    }
}

void GlobalContainer::setSchedule(QDate date, DailyScheduleSPtr schedule)
{
    years[date.year()].setSchedule(date, schedule);
}

} // calendar_containers

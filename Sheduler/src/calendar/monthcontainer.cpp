#include "monthcontainer.hpp"

namespace calendar_containers {

MonthContainer::MonthContainer()
{
    entries.resize(31);
}

MonthContainer::~MonthContainer()
{
}

void MonthContainer::getDaysInRange(QDate begin,
                                    QDate end,
                                    QVector<DailyScheduleSPtr> &result)
{
    int firstDay = begin.day() - 1;
    int lastDay = end.day() - 1;
    for (int day = firstDay; day <= lastDay; day++) {
        if (entries[day] != nullptr) {
            result.push_back(entries[day]);
        }
    }
}
void MonthContainer::setSchedule(QDate date, DailyScheduleSPtr schedule)
{
    entries[date.day() - 1] = schedule;
}

} // calendar_containers

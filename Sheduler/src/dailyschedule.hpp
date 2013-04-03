#ifndef DAILYSCHEDULE_HPP
#define DAILYSCHEDULE_HPP

#include <memory>

#include <QVector>

#include "event.hpp"
#include "regularevent.hpp"
#include "irregularevent.hpp"

class DailySchedule
{
public:
    DailySchedule();
    ~DailySchedule(); // should it delete its Event*s -- IS

public:
    QVector<Event*> events();
    QVector<RegularEvent*> regularEvents();
    QVector<IrregularEvent*> irregularEvents();

    // think over if this getters should be constant -- IS

    void addEvent(Event* event);

private:
    QVector<Event*> events_;

};

typedef std::shared_ptr<DailySchedule> DailyScheduleSPtr;

#endif // DAILYSCHEDULE_HPP

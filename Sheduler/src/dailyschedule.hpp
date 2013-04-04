#ifndef DAILYSCHEDULE_HPP
#define DAILYSCHEDULE_HPP

#include <memory>

#include <QVector>
#include <QDomElement>
#include <QDomDocument>

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

    std::shared_ptr<DailySchedule> clone();

    // think over if this getters should be constant -- IS

    void addEvent(Event* event);

    QDomElement serialize(QDomDocument &document) const;
    static std::shared_ptr<DailySchedule> deserialize(QDomElement element);

public:
    static int count;

private:
    QVector<Event*> events_;
};

typedef std::shared_ptr<DailySchedule> DailyScheduleSPtr;

#endif // DAILYSCHEDULE_HPP

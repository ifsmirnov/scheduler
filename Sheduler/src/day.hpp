#ifndef DAY_HPP
#define DAY_HPP

#include <QVector>
#include <QDate>

#include "event.hpp"
#include "regularevent.hpp"
#include "irregularevent.hpp"

/**
 * @brief The Day class. Represents one day in a schedule. Contains
 *        its date and events.
 */
class Day
{
public:
    Day();
    Day(QDate date);

public:
    QDate date() const;
    QVector<Event*> events();
    QVector<RegularEvent*> regularEvents();
    QVector<IrregularEvent*> irregularEvents();
    // maybe last three getters should be constant, I'm not sure yet  -- IS

    void setDate(const QDate& date);
    void addEvent(Event* event);
    // or const Event* ? -- IS

public:
    static const Day* defaultDay();
    static const Day* const defaultDay_;

private:
    QDate date_;
    QVector<Event*> events_;
};

bool operator <(const Day& lhs, const Day& rhs);
bool compareDayPointers(const Day* lhs, const Day* rhs);

#endif // DAY_HPP

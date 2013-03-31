#ifndef CALENDAR_HPP
#define CALENDAR_HPP

#include <memory>

#include <QObject>
#include <QVector>
#include <QDate>

#include "event.hpp"
#include "day.hpp"

class Calendar : public QObject
{
    Q_OBJECT
public:
    explicit Calendar(QObject *parent = 0);
    ~Calendar();

public:
    QVector<Day*> getDaysInRange(const QDate &begin, const QDate &end);
    
public slots:
    void addDay(Day* day);
    void addEvent(Event *event, const QDate &date);

private:
    QVector<Event*> events;
    QVector<Day*> days;

    /*
     * TODO
     * 1) which container should be used to handle days
     *    linear vector is convinient, but too slow on
     *    large amount of date
     * 2) Who is responsible on deleting Day*-s?
     *    answer: of course, we are (Calendar is)
     */
};

#endif // CALENDAR_HPP

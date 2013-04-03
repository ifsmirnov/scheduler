#ifndef CALENDAR_HPP
#define CALENDAR_HPP

#include <memory>

#include <QObject>
#include <QDate>
#include <QVector>

#include "container.hpp"
#include "src/dailyschedule.hpp"

using calendar_containers::Container;

class Calendar : public QObject
{
    Q_OBJECT
public:
    explicit Calendar(QObject *parent = 0);
    ~Calendar();
    
public slots:
    void setSchedule(QDate date, DailyScheduleSPtr schedule);
    QVector<DailyScheduleSPtr> getDaysInRange(QDate begin, QDate end);
    
private:
    Container *container;
    
};

#endif // CALENDAR_HPP

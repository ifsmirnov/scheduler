#ifndef EVENT_HPP
#define EVENT_HPP

#include <QTime>
#include <QString>

/**
 * @brief The Event class
 * @remarks begin stands for the first second of the event, end stands for the last
 *          duration is measured in seconds; duration = end() - begin() + 1
 */
class Event
{
public:
    Event();
    virtual ~Event() { }

public:
    virtual QTime begin() const = 0;
    virtual QTime end() const = 0;
    virtual int duration() const = 0;
    virtual QString info() const = 0;

    virtual void setBegin(const QTime& time) = 0;
    virtual void setEnd(const QTime& time) = 0;
    virtual void setDuration(int value) = 0;
    virtual void setInfo(const QString& value) = 0;
};

#endif // EVENT_HPP
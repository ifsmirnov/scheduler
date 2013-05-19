#ifndef REGULAREVENT_HPP
#define REGULAREVENT_HPP

#include "event.hpp"

#include <QTime>

/**
 * @brief The RegularEvent class; represents some scheduled events as lessons
 */
class RegularEvent : public Event
{
public:
    RegularEvent();
    RegularEvent(QTime begin, int duration, QString info = "");
    RegularEvent(QTime begin, QTime end, QString info = "");
    virtual ~RegularEvent();

public:
    virtual QTime begin() const;
    virtual QTime end() const;
    virtual int duration() const;
    virtual QString info() const;
    virtual QColor color() const;

    virtual void setBegin(const QTime& time);
    virtual void setEnd(const QTime& time);
    virtual void setDuration(int value);
    virtual void setInfo(const QString& value);
    virtual void setColor(const QColor& color);

    virtual bool isRegular() const;

    virtual Event *clone() const;

    virtual QDomElement serialize(QDomDocument &document) const;

private:
    QTime begin_, end_;
    QString info_;
};

#endif // REGULAREVENT_HPP

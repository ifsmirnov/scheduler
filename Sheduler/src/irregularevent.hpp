#ifndef IRREGULAREVENT_HPP
#define IRREGULAREVENT_HPP

#include "event.hpp"

/**
 * @brief The IrregularEvent class; represents some unusual events like hometasks
 *        and tests
 */
class IrregularEvent : public Event
{
public:
    IrregularEvent();
    IrregularEvent(QTime begin, int duration, QString info = "", QColor color = QColor());
    IrregularEvent(QTime begin, QTime end, QString info = "", QColor color = QColor());
    ~IrregularEvent();

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
    QColor color_;
};

#endif // IRREGULAREVENT_HPP

#include "regularevent.hpp"

#include <iostream>
#include <stdexcept>
#include <QTime>

RegularEvent::RegularEvent()
{
    // I have to use the constructor in this function
    // because setters do not accept null times
    begin_ = end_ = QTime();
    info_ = "";
}
RegularEvent::~RegularEvent()
{
}

RegularEvent::RegularEvent(QTime begin, int duration, QString info)
{
    try {
        setBegin(begin);
        setDuration(duration);
        setInfo(info);
    }
    catch (std::invalid_argument &e) {
        std::cerr << "Incorrect argument " << e.what() << " passed to the RegularEvent constructor" << std::endl;
    }
}

RegularEvent::RegularEvent(QTime begin, QTime end, QString info)
{
    try {
        setBegin(begin);
        setEnd(end);
        setInfo(info);
    }
    catch (std::invalid_argument &e) {
        std::cerr << "Incorrect argument " << e.what() << " passed to the RegularEvent constructor" << std::endl;
    }
}

QTime RegularEvent::begin() const {
    return begin_;
}
QTime RegularEvent::end() const {
    return end_;
}
int RegularEvent::duration() const {
    return begin().secsTo(end()) + 1;
}
QString RegularEvent::info() const {
    return info_;
}
QColor RegularEvent::color() const {
    return QColor();
}

void RegularEvent::setBegin(const QTime &time) {
    if (!time.isValid())
        throw std::invalid_argument("begin");
    begin_ = time;
}
void RegularEvent::setEnd(const QTime &time) {
    if (!time.isValid() || (!begin().isNull() && begin() > time))
        throw std::invalid_argument("end");
    end_ = time;
}
void RegularEvent::setDuration(int value) {
    if (value < 0 || value >= 24 * 60 * 60 || begin().isNull())
        throw std::invalid_argument("duration");
    QTime tmp = begin().addSecs(value);
    setEnd(tmp);
    // Is it correct that if exception is raised in setEnd it will be passed further
    // and I don't need to put try-catch block here?
}
void RegularEvent::setInfo(const QString &value) {
    info_ = value;
}
void RegularEvent::setColor(const QColor&) {}

bool RegularEvent::isRegular() const {
    return true;
}

Event *RegularEvent::clone() const
{
    return new RegularEvent(begin(), end(), info());
}

QDomElement RegularEvent::serialize(QDomDocument &document) const
{
    QDomElement element = document.createElement("event");

    element.setAttribute("begin", begin().toString("hh:mm:ss"));
    element.setAttribute("end", end().toString("hh:mm:ss"));
    element.setAttribute("info", info());
    element.setAttribute("regular", "true");

    return element;
}

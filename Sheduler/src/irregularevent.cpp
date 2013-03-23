#include "irregularevent.hpp"

#include <iostream>
#include <stdexcept>
#include <QTime>

IrregularEvent::IrregularEvent()
{
    // I have to use the constructor in this function
    // because setters do not accept null times
    begin_ = end_ = QTime();
    info_ = "";
}

IrregularEvent::IrregularEvent(QTime begin, int duration, QString info)
{
    try {
        setBegin(begin);
        setDuration(duration);
        setInfo(info);
    }
    catch (std::invalid_argument &e) {
        std::cerr << "Incorrect argument " << e.what() << " passed to the IregularEvent constructor" << std::endl;
    }
}

IrregularEvent::IrregularEvent(QTime begin, QTime end, QString info)
{
    try {
        setBegin(begin);
        setEnd(end);
        setInfo(info);
    }
    catch (std::invalid_argument &e) {
        std::cerr << "Incorrect argument " << e.what() << " passed to the IregularEvent constructor" << std::endl;
    }
}

QTime IrregularEvent::begin() const {
    return begin_;
}
QTime IrregularEvent::end() const {
    return end_;
}
int IrregularEvent::duration() const {
    return begin().secsTo(end()) + 1;
}
QString IrregularEvent::info() const {
    return info_;
}

void IrregularEvent::setBegin(const QTime &time) {
    if (!time.isValid())
        throw std::invalid_argument("begin");
    begin_ = time;
}
void IrregularEvent::setEnd(const QTime &time) {
    if (!time.isValid() || (!begin().isNull() && begin() > time))
        throw std::invalid_argument("end");
    end_ = time;
}
void IrregularEvent::setDuration(int value) {
    if (value < 0 || value >= 24 * 60 * 60 || begin().isNull())
        throw std::invalid_argument("duration");
    QTime tmp = begin().addSecs(value);
    setEnd(tmp);
    // Is it correct that if exception is raised in setEnd it will be passed further
    // and I don't need to put try-catch block here?
}
void IrregularEvent::setInfo(const QString &value) {
    info_ = value;
}

bool IrregularEvent::isRegular() const {
    return false;
}

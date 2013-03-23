#include "day.hpp"

#include <QVector>
#include <QDate>

Day::Day() {
    setDate(Date());
}
Day::Day(QDate date) {
    setDate(date);
}

QDate Day::date() const {
    return date_;
}
QVector<Event*> Day::events() {
    return events_;
}
QVector<RegularEvent*> Day::regularEvents() {
    QVector<RegularEvent*> res;
    for (auto i: events_) {
        if (i->isRegular()) {
            RegularEvent* t = dynamic_cast<RegularEvent*>(i);
            if (t)
                res.push_back(t);
        }
    }
    return res;
}
QVector<IrregularEvent*> Day::irregularEvents() {
    QVector<IrregularEvent*> res;
    for (auto i: events_) {
        if (!i->isRegular()) {
            IrregularEvent* t = dynamic_cast<IrregularEvent*>(i);
            if (t)
                res.push_back(t);
        }
    }
    return res;
}

void Day::setDate(const QDate &date) {
    date_ = date;
}
void Day::addEvent(Event *event) {
    events_.push_back(event);
}

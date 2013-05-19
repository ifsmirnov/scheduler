#include "event.hpp"

#include <iostream>

#include <QTime>
#include <QString>

#include "regularevent.hpp"
#include "irregularevent.hpp"

int Event::count = 0;

bool operator <(const Event& lhs, const Event& rhs) {
    return rhs.begin() <= lhs.begin();
}


Event *Event::deserialize(QDomElement element)
{
    if (element.tagName() != "event") {
        std::cerr << "Not an event" << std::endl;
    }
    if (!element.hasAttribute("regular")) {
        std::cerr << "Regularity not specified" << std::endl;
    }
    if (!element.hasAttribute("begin") || !element.hasAttribute("end")) {
        std::cerr << "Time interval not specified" << std::endl;
    }

    QTime begin = QTime::fromString(element.attribute("begin"), "hh:mm:ss");
    QTime end = QTime::fromString(element.attribute("end"), "hh:mm:ss");
    QString info = element.attribute("info", "");
    if (element.attribute("regular") == "true") {
        return new RegularEvent(begin, end, info);
    }
    else {
        if (!element.hasAttribute("color")) {
            std::cerr << "Irregular event without color" << std::endl;
        }
        QColor color = QColor(element.attribute("color"));
        return new IrregularEvent(begin, end, info, color);
    }
}

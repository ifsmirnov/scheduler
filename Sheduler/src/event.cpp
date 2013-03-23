#include "event.hpp"

#include <QTime>

Event::Event() {
}

bool operator <(const Event& lhs, const Event& rhs) {
    return rhs.begin() <= lhs.begin();
}

#include "event.hpp"

#include <QTime>

int Event::count = 0;

bool operator <(const Event& lhs, const Event& rhs) {
    return rhs.begin() <= lhs.begin();
}

//
// Created by thijs on 01-07-20.
//

#include <cmath>
#include "Position.h"

double Position::distance2(const Position &other) const {
    return (*this - other).length2();
}

double Position::distance(const Position &other) const {
    return sqrt(distance2(other));
}

double Position::length2() const {
    return dot(*this);
}

double Position::length() const {
    return std::sqrt(length2());
}

double Position::dot(const Position &other) const {
    return x * other.x + y * other.y;
}

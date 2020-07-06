//
// Created by thijs on 01-07-20.
//

#ifndef RAYCASTER_POSITION_H
#define RAYCASTER_POSITION_H


#include <cfloat>

class Position {
public:
    double x;
    double y;
    Position(double x, double y) : x(x), y(y) { };
    Position() : x(-DBL_MAX), y(-DBL_MAX) { };

    [[nodiscard]] double distance2(const Position &other) const;
    [[nodiscard]] double distance(const Position &other) const;

    [[nodiscard]] double length2() const;
    [[nodiscard]] double length() const;

    [[nodiscard]] double dot(const Position &other) const;

    Position operator-(const Position &other) const {
        return Position(x - other.x, y - other.y);
    }
    Position operator+(const Position &other) const {
        return Position(x + other.x, y + other.y);
    }
    Position operator-(const double &other) const {
        return Position(x - other, y - other);
    }
    Position operator+(const double &other) const {
        return Position(x + other, y + other);
    }
    Position operator*(const double &other) const {
        return Position(x * other, y * other);
    }
    bool operator==(const Position &other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Position &other) const {
        return !(*this==other);
    }
};

#endif //RAYCASTER_POSITION_H

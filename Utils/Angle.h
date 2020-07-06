//
// Created by thijs on 01-07-20.
//

#ifndef RAYCASTER_ANGLE_H
#define RAYCASTER_ANGLE_H

class Angle {
private:
    double angle;
public:
    explicit Angle(double angle);
    Angle() : angle(-1) {};

    bool isSet();

    double getAngle() const;
    double getAngleRad() const;

    Angle operator-(const Angle &other) const {
        auto a = Angle(this->angle - other.angle);
        return a;
    }
    Angle operator+(const Angle &other) const {
        auto a = Angle(this->angle + other.angle);
        return a;
    }
    Angle operator-(const double &other) const {
        auto a = Angle(this->angle - other);
        return a;
    }
    Angle operator+(const double &other) const {
        auto a = Angle(this->angle + other);
        return a;
    }
};


#endif //RAYCASTER_ANGLE_H

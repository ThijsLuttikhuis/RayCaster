//
// Created by thijs on 01-07-20.
//

#include <cmath>
#include "Angle.h"

Angle::Angle(double angle_) {
    if (angle_ == -1) {
        this->angle = -1;
        return;
    }
    this->angle = std::fmod(angle_, 360);
}

double Angle::getAngle() const {
    return angle;
}

double Angle::getAngleRad() const {
    return angle*M_PI/180;
}

bool Angle::isSet() {
    return angle != -1;
}

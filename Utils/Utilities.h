//
// Created by thijs on 05-07-20.
//

#ifndef RAYCASTER_UTILITIES_H
#define RAYCASTER_UTILITIES_H

#include <string>
#include <sstream>
#include <iterator>

template<class Container>
static void split(const std::string &str, Container &cont, char delim = ' ') {
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {
        cont.push_back(token);
    }
}

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

static double distanceLineSegmentToPoint(Position line1, Position line2, Position point) {

    double l2 = line1.distance2(line2);  // i.e. |w-v|^2 -  avoid a sqrt
    if (l2 == 0.0) return line1.distance(point);   // v == w case
    // Consider the line extending the segment, parameterized as v + t (w - v).
    // We find projection of point p onto the line.
    // It falls where t = [(p-v) . (w-v)] / |w-v|^2
    // We clamp t from [0,1] to handle points outside the segment vw.
    double t = std::max(0.0, std::min(1.0, (point - line1).dot(line2 - line1) / l2));
    Position projection = line1 + (line2 - line1) * t;  // Projection falls on the segment
    return point.distance(projection);
}

static double distanceLineToPoint(Position line1, Position line2, Position point) {

    double l2 = line1.distance2(line2);  // i.e. |w-v|^2 -  avoid a sqrt
    if (l2 == 0.0) return line1.distance(point);   // v == w case
    // Consider the line extending the segment, parameterized as v + t (w - v).
    // We find projection of point p onto the line.
    // It falls where t = [(p-v) . (w-v)] / |w-v|^2
    // We clamp t from [0,1] to handle points outside the segment vw.
    double t = (point - line1).dot(line2 - line1) / l2;
    Position projection = line1 + (line2 - line1) * t;  // Projection falls on the segment
    return point.distance(projection);
}

static Position lineSegmentIntersection(Position r0, Position r1, Position a, Position b) {

    Position s1 = r1 - r0;
    Position s2 = b - a;

    double s = (-s1.y * (r0.x - a.x) + s1.x * (r0.y - a.y)) / (-s2.x * s1.y + s1.x * s2.y);
    double t = (s2.x * (r0.y - a.y) - s2.y * (r0.x - a.x)) / (-s2.x * s1.y + s1.x * s2.y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
// Collision detected
// Return the point of intersection
        return Position(r0.x + (t * s1.x), r0.y + (t * s1.y));
    }

    return {}; // No collision
}

#endif //RAYCASTER_UTILITIES_H

#include "../Final/Segment.h"
#include <cmath>

Segment::Segment(const Point& start, double length, double angle)
    : start(start), length(length), angle(angle) {
    updateEnd();
}

void Segment::updateEnd() {
    double dx = length * std::cos(angle);
    double dy = length * std::sin(angle);
    end = Point(start.x + dx, start.y + dy);
}

const Point& Segment::getStart() const {
    return start;
}

const Point& Segment::getEnd() const {
    return end;
}

double Segment::getAngle() const {
    return angle;
}

void Segment::setAngle(double newAngle) {
    // Prevent unnatural flips
    if (newAngle > M_PI) newAngle = M_PI;
    if (newAngle < -M_PI) newAngle = -M_PI;

    angle = newAngle;
    updateEnd();
}

void Segment::rotate(double angleDelta) {
    angle += angleDelta;
    updateEnd();
}

double Segment::getLength() const {
    return length;
}
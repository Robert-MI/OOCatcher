#include "../Preliminary/Segment.h"
#include <cmath>

Segment::Segment(Point start, double length, double angle)
    : start(start), length(length), angle(angle) {
    updateEnd();
}

void Segment::updateEnd() {
    end.x = start.x + length * cos(angle);
    end.y = start.y + length * sin(angle);
}

void Segment::rotate(double deltaAngle) {
    angle += deltaAngle;
    updateEnd();
}

Point Segment::getStart() const {
    return start;
}

Point Segment::getEnd() const {
    return end;
}

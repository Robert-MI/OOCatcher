#ifndef SEGMENT_H
#define SEGMENT_H

#include "../Final/Point.h"

class Segment {
private:
    Point start;
    Point end;
    double length;
    double angle;
    void updateEnd();
public:
    Segment(const Point& start, double length, double angle);

    const Point& getStart() const;
    const Point& getEnd() const;

    double getAngle() const;
    void setAngle(double newAngle);
    void rotate(double angleDelta);
    double getLength() const;
};

#endif

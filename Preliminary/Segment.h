#ifndef SEGMENT_H
#define SEGMENT_H

#include "../Preliminary/Point.h"

class Segment {
private:
    Point start;
    Point end;
    double length;
    double angle;
    void updateEnd();
public:
    Segment(Point start, double length, double angle = 0.0);
    void rotate(double deltaAngle);
    Point getStart() const;
    Point getEnd() const;
};

#endif

#ifndef BODY_H
#define BODY_H

#include "../Preliminary/Segment.h"
#include <vector>

class Body {
private:
    std::vector<Segment> segments;
public:
    Body();
    void move();
    void display() const;
};

#endif

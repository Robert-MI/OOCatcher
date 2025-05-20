#ifndef BODY_H
#define BODY_H

#include "../Final/Segment.h"
#include <vector>

class Body {
private:
    std::vector<Segment> segments;
public:
    Body();
    void move();
    void display() const;
    const Segment& getRightArm() const; // Returns the right arm segment
    void adjustRightArmToward(const Point& target); // Aims the right arm at a point
    std::pair<Point, Point> computeThrowStats() const; // Position and velocity of the snowball
    std::vector<Point> getAllEndpoints() const;
    std::vector<Point> getEndpointsTouchingBall(const Point& center, double radius) const;
    const std::vector<Segment>& getSegments() const;
    void step(double size);
};

#endif

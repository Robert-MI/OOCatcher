#include "../Final/Body.h"
#include <iostream>
#include <cmath>
#include <utility>

Body::Body() {
    const double PI = 3.141592653589793;
    double len = 10.0;

    Point torsoBase(0, 0);

    // Legs
    segments.push_back(Segment(torsoBase, len, -PI / 4)); // Left leg
    segments.push_back(Segment(torsoBase, len, -3 * PI / 4)); // Right leg

    // Torso
    segments.push_back(Segment(torsoBase, len, PI / 2)); // |

    // Arms
    Point shoulder = segments.back().getEnd();
    segments.push_back(Segment(shoulder, len, 3 * PI / 4)); // Left arm
    segments.push_back(Segment(shoulder, len, PI / 4)); // Right arm

    Point handBase = segments.back().getEnd(); // End of right arm
    double fingerLength = 2.0;

    // Fingers on right hand
    segments.push_back(Segment(handBase, fingerLength, PI / 4)); // Middle Finger
    segments.push_back(Segment(handBase, fingerLength, PI / 4 + 0.2)); // Upper Finger
    segments.push_back(Segment(handBase, fingerLength, PI / 4 - 0.2)); // Lower Finger
}

const Segment& Body::getRightArm() const {
    return segments.at(4);
}

// Rotates the right arm so that it points toward the given target
void Body::adjustRightArmToward(const Point& target) {
    Segment& arm = segments.at(4); // Right arm
    Point base = arm.getStart();
    double angleToTarget = std::atan2(target.y - base.y, target.x - base.x);
    arm.setAngle(angleToTarget);

    // Update fingers after arm rotates
    if (segments.size() >= 8) {
        segments.erase(segments.end() - 3, segments.end());
    }

    Point handBase = arm.getEnd();
    double baseAngle = arm.getAngle();
    double fingerLength = 2.0;

    segments.push_back(Segment(handBase, fingerLength, baseAngle)); // Middle Finger
    segments.push_back(Segment(handBase, fingerLength, baseAngle + 0.2)); // Upper Finger
    segments.push_back(Segment(handBase, fingerLength, baseAngle - 0.2)); // Lower Finger
}

// Computes the throw parameters: start position and velocity of snowball
std::pair<Point, Point> Body::computeThrowStats() const {
    const Segment& arm = segments.at(4); // Right arm
    Point start = arm.getEnd();
    double angle = arm.getAngle();
    double speed = 30.0;

    Point velocity(std::cos(angle) * speed, std::sin(angle) * speed);
    return {start, velocity};
}

const std::vector<Segment>& Body::getSegments() const {
    return segments;
}

void Body::step(double size) {
    for (Segment& seg : segments) {
        Point newStart = seg.getStart();
        newStart.x += size;

        seg = Segment(newStart, seg.getLength(), seg.getAngle());
    }
}

void Body::move() {
    segments.back().rotate(0.1);
}

std::vector<Point> Body::getAllEndpoints() const {
    std::vector<Point> points;
    for (const Segment& seg : segments) {
        points.push_back(seg.getStart());
        points.push_back(seg.getEnd());
    }
    return points;
}

std::vector<Point> Body::getEndpointsTouchingBall(const Point& center, double radius) const {
    std::vector<Point> result;
    for (const Point& p : getAllEndpoints()) {
        double dx = p.x - center.x;
        double dy = p.y - center.y;
        if (std::sqrt(dx * dx + dy * dy) <= radius) {
            result.push_back(p);
        }
    }
    return result;
}

void Body::display() const {
    for (const auto& seg : segments) {
        Point start = seg.getStart();
        Point end = seg.getEnd();
        std::cout << "Segment from (" << start.x << ", " << start.y << ") to ("
                  << end.x << ", " << end.y << ")\n";
    }

    // ASCII grid
    const int width = 40;
    const int height = 40;
    char grid[height][width];

    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
            grid[y][x] = ' ';

    for (const auto& seg : segments) {
        Point s = seg.getStart();
        Point e = seg.getEnd();

        int sx = static_cast<int>(round(s.x)) + width / 2;
        int sy = height / 2 - static_cast<int>(round(s.y));

        int ex = static_cast<int>(round(e.x)) + width / 2;
        int ey = height / 2 - static_cast<int>(round(e.y));

        if (sx >= 0 && sx < width && sy >= 0 && sy < height)
            grid[sy][sx] = '*';
        if (ex >= 0 && ex < width && ey >= 0 && ey < height)
            grid[ey][ex] = '*';
    }

    // Print grid
    std::cout << "\nASCII Visualization:\n";
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x)
            std::cout << grid[y][x];
        std::cout << "\n";
    }
}

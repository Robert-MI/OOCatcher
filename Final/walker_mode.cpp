#include "../Final/Body.h"
#include "../Final/Point.h"
#include <iostream>
#include <cmath>
#include <vector>

constexpr double GROUND_Y = -7.07107;

int countGroundPoints(const Body& body) {
    int count = 0;
    for (const Point& pt : body.getAllEndpoints()) {
        if (std::abs(pt.y - GROUND_Y) < 1e-5) {
            count++;
        }
    }
    return count;
}

// Checks if a point is touching a circle
bool isTouchingCircle(const Point& p, const Point& center, double radius) {
    double dx = p.x - center.x;
    double dy = p.y - center.y;
    return std::sqrt(dx * dx + dy * dy) <= radius;
}

// Finds all free endpoints in contact with the object
std::vector<Point> getFreeEndpointsTouchingObject(const Body& body, const Point& center, double radius) {
    std::vector<Point> allEnds = body.getAllEndpoints();
    std::vector<Point> allStarts;
    for (const Segment& seg : body.getSegments()) {
        allStarts.push_back(seg.getStart());
    }

    // Free endpoints = ends that are not the start of another segment
    std::vector<Point> freeEnds;
    for (const Point& end : allEnds) {
        bool isFree = true;
        for (const Point& start : allStarts) {
            if (std::abs(end.x - start.x) < 1e-5 && std::abs(end.y - start.y) < 1e-5) {
                isFree = false;
                break;
            }
        }
        if (isFree && isTouchingCircle(end, center, radius)) {
            freeEnds.push_back(end);
        }
    }

    return freeEnds;
}

int main() {
    Body body;

    const auto& segments = body.getSegments();
    std::cout << "Initial Segment Coordinates:\n";
    for (size_t i = 0; i < segments.size(); ++i) {
        const auto& s = segments[i];
        std::cout << "  Segment " << i << ": "
                  << "Start(" << s.getStart().x << ", " << s.getStart().y << "), "
                  << "End(" << s.getEnd().x << ", " << s.getEnd().y << ")\n";
    }

    // Object to grab
    Point objectCenter(20.0, 15.0);
    double objectRadius = 3.0;

    std::cout << "\nWalker Mode Start\n";

    for (int step = 0; step < 20; ++step) {
        std::cout << "\nStep " << step + 1 << ":\n";

        body.step(1);
        body.adjustRightArmToward(objectCenter);

        int ground = countGroundPoints(body);
        std::cout << "Ground contact points: " << ground << "\n";
        if (ground < 2) {
            std::cout << "Invalid step, not enough ground contact.\n";
            break;
        }

        auto grabbingPoints = getFreeEndpointsTouchingObject(body, objectCenter, objectRadius);
        std::cout << "Free endpoints touching object: " << grabbingPoints.size() << "\n";

        const auto& segments = body.getSegments();
        std::cout << "Segment Coordinates:\n";
        for (size_t i = 0; i < segments.size(); ++i) {
            const auto& s = segments[i];
            std::cout << "  Segment " << i << ": "
                      << "Start(" << s.getStart().x << ", " << s.getStart().y << "), "
                      << "End(" << s.getEnd().x << ", " << s.getEnd().y << ")\n";
        }

        if (grabbingPoints.size() >= 3) {
            std::cout << "Object successfully grabbed!\n";
            break;
        }
    }

    return 0;
}

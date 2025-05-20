#include "../Final/Body.h"
#include "../Final/Point.h"
#include <iostream>
#include <cmath>

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

double distanceFromLineToPoint(const Point& origin, const Point& direction, const Point& targetCenter) {
    double dx = targetCenter.x - origin.x;
    double dy = targetCenter.y - origin.y;

    double mag = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    double vx = direction.x / mag;
    double vy = direction.y / mag;

    double proj = dx * vx + dy * vy;
    double closestX = origin.x + proj * vx;
    double closestY = origin.y + proj * vy;

    double distX = targetCenter.x - closestX;
    double distY = targetCenter.y - closestY;

    return std::sqrt(distX * distX + distY * distY);
}

int main() {
    Body body;

    // Define the held snowball
    Point ballCenter = body.getSegments()[5].getEnd(); // First finger (middle)
    double ballRadius = 2.0;


    // 1. Check which body endpoints are touching the ball initially
    auto touchingBefore = body.getEndpointsTouchingBall(ballCenter, ballRadius);
    std::cout << "Touching ball before move: " << touchingBefore.size() << " points\n";

    if (touchingBefore.empty()) {
        std::cout << "Body is not holding the snowball.\n";
        return 1;
    }

    double targetX, targetY, targetRadius;
    std::cout << "Enter target X Y position (e.g., 25 15): ";
    std::cin >> targetX >> targetY;

    std::cout << "Enter target radius (e.g., 5): ";
    std::cin >> targetRadius;

    Point target(targetX, targetY);

    // 2. Move the right arm to simulate releasing the snowball
    body.adjustRightArmToward(target);

    // Ground check
    int ground = countGroundPoints(body);
    std::cout << "Ground contact points: " << ground << "\n";
    if (ground < 2) {
        std::cout << "Invalid move, not enough ground contact.\n";
    }

    // 3. Recheck touching points after the move
    auto touchingAfter = body.getEndpointsTouchingBall(ballCenter, ballRadius);
    std::cout << "Touching ball after move: " << touchingAfter.size() << " points\n";

    if (!touchingAfter.empty()) {
        std::cout << "Body has not released the snowball yet.\n";
        return 1;
    }

    // 4. Proceed with the throw
    auto [launchPosition, velocity] = body.computeThrowStats();
    std::cout << "Snowball thrown!\n";
    std::cout << "Start position: (" << launchPosition.x << ", " << launchPosition.y << ")\n";
    std::cout << "Velocity vector: (" << velocity.x << ", " << velocity.y << ")\n";

    // Ground check
    int ground1 = countGroundPoints(body);
    std::cout << "Ground contact points: " << ground1 << "\n";
    if (ground1 < 2) {
        std::cout << "Invalid move, not enough ground contact.\n";
    }

    // 5. Hit test
    Point targetCenter = target;
    double closest = distanceFromLineToPoint(launchPosition, velocity, targetCenter);
    std::cout << "Closest approach: " << closest << ", Target Radius: " << targetRadius << "\n";

    if (closest <= targetRadius) {
        std::cout << "Target hit!\n";
    } else {
        std::cout << "Missed the target.\n";
    }

    return 0;
}

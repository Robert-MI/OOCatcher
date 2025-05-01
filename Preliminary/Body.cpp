#include "../Preliminary/Body.h"
#include <iostream>
#include <cmath>

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
}

void Body::move() {
    segments.back().rotate(0.1);
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

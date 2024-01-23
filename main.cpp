#include <iostream>
#include <fstream>
#include "graham_scan.hpp"

//#define VERBOSE 1
#define HR_CLOCK_NOW() std::chrono::high_resolution_clock::now()
#define HR_CLOCK_DURATION(a, b) std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count()

struct point
{
    size_t id;
    float x;
    float y;
};

std::istream &operator>>(std::istream &is, point &p)
{
    is >> p.x >> p.y;
    return is;
}

float get_x(point &p)
{
    return p.x;
}

float get_y(point &p)
{
    return p.y;
}

void load_points_from_file(std::istream &file, std::vector<point> &points)
{
    int n = 0;
    file >> n;
    for(int i = 0; i < n; i++) {
        point p {};
        file >> p;
        p.id = i;
        points.push_back(p);
    }
}

int main()
{
    size_t i = 0;
    std::vector<point> points{};
    std::ifstream file("points2.txt");
    if(!file.is_open()){
        std::cerr << "file not found!";
        return -2;
    }
    load_points_from_file(file, points);

#ifdef VERBOSE
    std::cout << "Points: ";
    for (const auto &p : points) {
        std::cout << "[" << i++ << "] = " << "(" << p.x << ", " << p.y << "),";

    }
    std::cout << std::endl;
#endif

    // Run the graham_scan function
    auto convex_hull =
        graham_scan<point>(points, std::function<float(point &)>(get_x), std::function<float(point &)>(get_y));

    // Print the points in the convex hull
    std::cout << "\nConvex hull size: " << convex_hull.size();
    std::cout << ", points:\n";
    for (const auto &p : convex_hull) {
        std::cout << "[" << p.id << "]" << "(" << p.x << ", " << p.y << ")," << std::endl;
    }

    return 0;
}

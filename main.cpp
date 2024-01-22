#include <iostream>
#include <fstream>
#include "graham_scan.hpp"
#include "grahamp.h"

struct point
{
    float x;
    float y;
    bool dbg_marked = false;
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
        points.push_back(p);
    }
}

int _main(){
    std::vector<Point> points = ReadPointsFromFile("points3.txt");
    for (const auto &p : points) {
        std::cout << "(" << p.x << ", " << p.y << "),";
    }


    std::vector<Point> hull = GrahamScan(points);
    std::cout << std::endl;
    for (const auto &p : hull) {
        std::cout << "(" << p.x << ", " << p.y << "),";
    }

}


int main()
{
    std::vector<point> points{};
    std::ifstream file("points3.txt");
    load_points_from_file(file, points);

    for (const auto &p : points) {
        std::cout << "(" << p.x << ", " << p.y << "),";
    }
    std::cout << std::endl;

    // Run the graham_scan function
    auto convex_hull =
        graham_scan<point>(points, std::function<float(point &)>(get_x), std::function<float(point &)>(get_y));

    // Print the points in the convex hull
    for (const auto &p : convex_hull) {
        std::cout << "(" << p.x << ", " << p.y << "),";
    }

    return 0;
}

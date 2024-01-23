#pragma once

#include <algorithm>
#include <vector>
#include <stack>
#include <cmath>
#include <functional>
#include <iostream>
#include <chrono>

#define HR_CLOCK_NOW() std::chrono::high_resolution_clock::now()
#define HR_CLOCK_DURATION(a, b) std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count()

// Clockwise
template<typename TX, typename TY>
int ccw(TX x1, TY y1, TX x2, TY y2, TX x3, TY y3)
{
    auto val = (y2 - y1) * (x3 - x2) - (x2 - x1) * (y3 - y2);

    return val == 0 ? 0 : (val > 0 ? 1 : -1);
}

template<typename T, typename TX = float, typename TY = TX>
int ccw(T &p1, T &p2, T &p3, std::function<TX(T &)> get_x, std::function<TY(T &)> get_y)
{
    return ccw(get_x(p1), get_y(p1), get_x(p2), get_y(p2), get_x(p3), get_y(p3));
}

template<typename T, typename TX = float, typename TY = TX>
std::vector<T> graham_scan(std::vector<T> points, std::function<TX(T &)> get_x, std::function<TY(T &)> get_y)
{
    std::vector<T> point_stack{};

    auto start = HR_CLOCK_NOW();
    auto P0it = std::min_element(points.begin(), points.end(), [&](T &a, T &b) {
        return get_y(a) < get_y(b) || (get_y(a) == get_y(b) && get_x(a) < get_x(b));
    });
    auto end = HR_CLOCK_NOW();
    std::cout << "finding Min element took " << HR_CLOCK_DURATION(start, end) << " ms" << std::endl;

    // Swap P0 with the first element
    std::iter_swap(points.begin(), P0it);
    T& P0 = points[0];

    // Sort the points by polar angle
    auto start2 = HR_CLOCK_NOW();
    std::sort(points.begin()+1, points.end(), [&](T &a, T &b) {

        int orientation = ccw(P0, a, b, get_x, get_y);
        if (orientation == 0) {
            auto dist_a = (get_x(a) - get_x(P0)) * (get_x(a) - get_x(P0))
                + (get_y(a) - get_y(P0)) * (get_y(a) - get_y(P0));
            auto dist_b = (get_x(b) - get_x(P0)) * (get_x(b) - get_x(P0))
                + (get_y(b) - get_y(P0)) * (get_y(b) - get_y(P0));

            return dist_a < dist_b;
        }
        return orientation > 0;
    });
    end = HR_CLOCK_NOW();
    std::cout << "sorting took " << HR_CLOCK_DURATION(start2, end) << " ms" << std::endl;

    auto start3 = HR_CLOCK_NOW();
    for (int i = 0; i < points.size(); i++) {
        while (point_stack.size() > 1 && ccw(point_stack[point_stack.size() - 2],
                                             point_stack[point_stack.size() - 1],
                                             points[i], get_x, get_y) <= 0) {
            point_stack.pop_back();
        }
        point_stack.push_back(points[i]);
    }
    end = HR_CLOCK_NOW();
    std::cout << "graham scan algorithm took " << HR_CLOCK_DURATION(start3, end) << " ms" << std::endl;
    std::cout << "total graham scan took " << HR_CLOCK_DURATION(start, end) << " ms" << std::endl;

    return point_stack;
}
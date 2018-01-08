//
// Created by mcsim on 03.01.18.
//

#import <SFML/Graphics.hpp>
#include <cmath>

template <typename T> sf::Vector2<T> normalize(sf::Vector2<T> vector2) {
    T len = sqrt(vector2.x*vector2.x + vector2.y*vector2.y);
    return sf::Vector2<T>(vector2.x / len, vector2.y / len);
}

template <typename T> T length(sf::Vector2<T> vector2) {
    return sqrt(vector2.x * vector2.x + vector2.y * vector2.y);
}

template <typename T> float vectorIntersection(sf::Vector2<T> p1, sf::Vector2<T> p2, sf::Vector2<T> m1, sf::Vector2<T> m2) {
    auto ax = p2.x - p1.x;
    auto ay = p2.y - p1.y;
    auto bx = m1.x - m2.x;
    auto by = m1.y - m2.y;
    auto cx = p1.x - m1.x;
    auto cy = p1.y - m1.y;

    auto lambda = (bx*cy - cx*by) / (ax*by - ay*bx);
    auto gamma = (-cy - ay*lambda) / by;
    if (lambda >= 0 && lambda <= 1 && gamma >= 0 && gamma <= 1) {
        return lambda;
    } else {
        return -1;
    }
//    return lambda >= 0 && lambda <= 1 ? lambda : -1;
}
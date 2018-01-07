//
// Created by mcsim on 03.01.18.
//

#import <SFML/Graphics.hpp>

template <typename T> sf::Vector2<T> normalize(sf::Vector2<T> vector2) {
    T len = sqrt(vector2.x*vector2.x + vector2.y*vector2.y);
    return sf::Vector2<T>(vector2.x / len, vector2.y / len);
}

//
// Created by mcsim on 02.01.18.
//

#ifndef SANDBOX_WALL_HPP
#define SANDBOX_WALL_HPP

#include <SFML/Graphics.hpp>
#define WALL_THICKNESS 15.0f

class Wall: public sf::ConvexShape {
public:
    Wall(sf::Vector2f begin, sf::Vector2f end);
    Wall(sf::Vector2f first, sf::Vector2f second, sf::Vector2f third, sf::Vector2f fourth);
};


#endif //SANDBOX_WALL_HPP

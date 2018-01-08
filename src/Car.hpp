//
// Created by mcsim on 02.01.18.
//

#ifndef SANDBOX_CAR_HPP
#define SANDBOX_CAR_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <list>
#include "Wall.hpp"

#define CAR_HEIGHT 80
#define CAR_WIDTH 120

class Car: public sf::RectangleShape {
public:
    Car();

    void tick(std::__1::list<Wall *> list);

    bool isActive() { return _active; }

private:
    sf::Vector2f direction;

    bool _active = true;

    void rotate(float angle);

    static sf::Uint8 randomColor();
};


#endif //SANDBOX_CAR_HPP


// bio
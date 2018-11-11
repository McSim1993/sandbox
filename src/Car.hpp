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
#define CAR_WIDTH 150

#define SENSORS_COUNT 5
#define SENSOR_LEN 100

class Car {
public:
    Car();

    void draw(sf::RenderWindow* window);

    void move(float x, float y);

    void tick(std::list<Wall *> list);

    bool isActive() { return _active; }

private:
    sf::Vector2f direction;
    sf::ConvexShape model;
    std::vector<sf::ConvexShape> sensors = std::vector<sf::ConvexShape>(SENSORS_COUNT);

    bool _active = true;

    void rotate(float angle);

    static sf::Uint8 randomColor();

    bool intersects(sf::ConvexShape* pWall);

    void generateModel();

    void generateSensors();

    void move(sf::Vector2<float> vector2);
};


#endif //SANDBOX_CAR_HPP


// bio
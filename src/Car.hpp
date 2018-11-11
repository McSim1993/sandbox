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
#define SENSOR_LEN 120

#define SPEED_FACTOR 2.0f

class Car {
public:
    Car();

    void draw(sf::RenderWindow* window);

    void move(float x, float y);

    void tick(std::list<Wall *> list);

    bool isActive() { return _active; }

    double getFitness() { return fitness; }

    sf::Vector2f getPosition() {
        return this->model.getPosition();
    }

private:
    sf::Vector2f direction;
    sf::ConvexShape model;
    std::vector<sf::ConvexShape> sensors = std::vector<sf::ConvexShape>(SENSORS_COUNT);
    std::vector<double> inputs = std::vector<double>(SENSORS_COUNT);
    double fitness = 0.0;

    bool _active = true;

    void rotate(float angle);

    static sf::Uint8 randomColor();

    bool intersects(sf::ConvexShape* pWall);

    void generateModel();

    void generateSensors();

    void move(sf::Vector2<float> vector2);

    void dropInputs();
};


#endif //SANDBOX_CAR_HPP


// bio
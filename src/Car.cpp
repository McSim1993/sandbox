//
// Created by mcsim on 02.01.18.
//

#include "Car.hpp"

Car::Car(): sf::RectangleShape(sf::Vector2f(CAR_WIDTH, CAR_HEIGHT)) {
    this->direction = sf::Vector2f(1, 0);
    this->setFillColor(sf::Color(randomColor(), randomColor(), randomColor()));
    this->setOrigin(CAR_WIDTH/2, CAR_HEIGHT/2);

    this->rotate(std::rand() %180 - 90);
}

sf::Uint8 Car::randomColor() {
    return static_cast<sf::Uint8>(std::rand() % 255);
}

void Car::tick() {
    this->move(this->direction / 30.0f);
}

void Car::rotate(float angle) {
    sf::Transformable::rotate(angle);
    sf::Transform rotation;
    rotation.rotate(angle, 0, 0);
    this->direction = rotation.transformPoint(this->direction);
}

//
// Created by mcsim on 02.01.18.
//

#include <list>
#include "Car.hpp"
#include "Wall.hpp"
#include "VectorUtils.cpp"

Car::Car(): sf::ConvexShape() {
    this->direction = sf::Vector2f(1, 0);
    this->setPointCount(4);
    this->setPoint(0, sf::Vector2f(0,0));
    this->setPoint(1, sf::Vector2f(CAR_WIDTH,0));
    this->setPoint(2, sf::Vector2f(CAR_WIDTH,CAR_HEIGHT));
    this->setPoint(3, sf::Vector2f(0,CAR_HEIGHT));

    this->setFillColor(sf::Color(randomColor(), randomColor(), randomColor()));
    this->setOrigin(CAR_WIDTH/2, CAR_HEIGHT/2);

    this->rotate(std::rand() %180 - 90);
}

sf::Uint8 Car::randomColor() {
    return static_cast<sf::Uint8>(std::rand() % 255);
}

void Car::tick(std::list<Wall *> walls) {
    if (this->_active) {
        this->move(this->direction / 2.0f);
        for (auto &wall: walls) {
            if (wall->getGlobalBounds().intersects(this->getGlobalBounds())) {
                if (this->intersects(wall)) {
                    this->_active = false;
                }
            }
        }
    }
}

void Car::rotate(float angle) {
    sf::Transformable::rotate(angle);
    sf::Transform rotation;
    rotation.rotate(angle, 0, 0);
    this->direction = rotation.transformPoint(this->direction);
}

bool Car::intersects(sf::ConvexShape* wall) {
    auto result = false;
    size_t i = 0;
    while(i < wall->getPointCount() && !result) {
        size_t j = 0;
        while(j < this->getPointCount() && !result) {
            if (vectorIntersection(this->getTransform().transformPoint(this->getPoint(j)),
                                   this->getTransform().transformPoint(this->getPoint((j+1)%this->getPointCount())),
                                   wall->getPoint(i),
                                   wall->getPoint((i+1)%wall->getPointCount())) >= 0) {
                result = true;
            }
            j++;
        }
        i++;
    }
    return result;
}

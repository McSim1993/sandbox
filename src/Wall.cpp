//
// Created by mcsim on 02.01.18.
//

#include "Wall.hpp"
#include "VectorUtils.cpp"

Wall::Wall(sf::Vector2f begin, sf::Vector2f end) {
    auto bone = (end - begin);
    auto direction = normalize(bone) * WALL_THICKNESS;

    sf::Transform rotationNeg;
    rotationNeg.rotate(-45);
    sf::Transform rotationPos;
    rotationPos.rotate(45);

    this->setPointCount(4);
    this->setPoint(0, end + rotationNeg.transformPoint(direction));
    this->setPoint(1, end + rotationPos.transformPoint(direction));
    direction *= (-1.0f);
    this->setPoint(2, begin + rotationNeg.transformPoint(direction));
    this->setPoint(3, begin + rotationPos.transformPoint(direction));
}

Wall::Wall(sf::Vector2f first, sf::Vector2f second, sf::Vector2f third, sf::Vector2f fourth) {
    this->setPointCount(4);
    this->setPoint(0, first);
    this->setPoint(1, second);
    this->setPoint(2, third);
    this->setPoint(3, fourth);
}

//
// Created by mcsim on 02.01.18.
//

#include <list>
#include "Car.hpp"
#include "Wall.hpp"
#include "VectorUtils.cpp"
#import <iostream>

Car::Car() {
    this->direction = sf::Vector2f(1, 0);
    this->generateModel();
    this->generateSensors();
    this->dropInputs();

    this->rotate(std::rand() % 40 - 20);
}

sf::Uint8 Car::randomColor() {
    return static_cast<sf::Uint8>(std::rand() % 255);
}

void Car::dropInputs() {
    for (auto &input: this->inputs) {
        input = 0;
    }
}

void Car::tick(std::list<Wall *> walls) {
    this->dropInputs();
    if (this->_active) {
        this->move(this->direction / SPEED_FACTOR);
        for (auto &wall: walls) {
            if (wall->getGlobalBounds().intersects(this->model.getGlobalBounds())) {
                if (this->intersects(wall)) {
                    this->_active = false;
                }
            }

            for (auto i = 0; i < SENSORS_COUNT; i++) {
                auto sensor = this->sensors[i];
                auto p1 = sensor.getTransform().transformPoint(sensor.getPoint(1));
                auto p2 = sensor.getTransform().transformPoint(sensor.getPoint(0));
                for (size_t j = 0; j < wall->getPointCount(); j++) {
                    auto m1 = wall->getPoint(j);
                    auto m2 = wall->getPoint((j+1)%wall->getPointCount());
                    auto candidate = vectorIntersection(p1, p2, m1, m2);
                    if (candidate >= 0 && candidate > this->inputs[i]) {
                        this->inputs[i] = candidate;
                    }
                }
            }
        }
        fitness += 1;
    }

    for (size_t i = 0; i < SENSORS_COUNT; i++) {
        auto input = this->inputs[i];
        this->sensors[i].setFillColor(sf::Color(floor(255*input), floor(255*(1-input/2)), 0));
    }
}

void Car::rotate(float angle) {
    this->model.rotate(angle);
    for(auto &sensor: this->sensors) {
        sensor.rotate(angle);
    }
    sf::Transform rotation;
    rotation.rotate(angle, 0, 0);
    this->direction = rotation.transformPoint(this->direction);
}

bool Car::intersects(sf::ConvexShape* wall) {
    auto result = false;
    size_t i = 0;
    while(i < wall->getPointCount() && !result) {
        size_t j = 0;
        while(j < this->model.getPointCount() && !result) {
            if (vectorIntersection(this->model.getTransform().transformPoint(this->model.getPoint(j)),
                                   this->model.getTransform().transformPoint(this->model.getPoint((j+1)%this->model.getPointCount())),
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

void Car::draw(sf::RenderWindow* window) {
    window->draw(this->model);
    for(auto &sensor: this->sensors) {
        window->draw(sensor);
    }
}

void Car::move(float x, float y) {
    this->model.move(x,y);
    for(auto &sensor: this->sensors) {
        sensor.move(x, y);
    }
}

void Car::generateModel() {
    this->model.setPointCount(4);
    this->model.setPoint(0, sf::Vector2f(0,0));
    this->model.setPoint(1, sf::Vector2f(CAR_WIDTH,0));
    this->model.setPoint(2, sf::Vector2f(CAR_WIDTH,CAR_HEIGHT));
    this->model.setPoint(3, sf::Vector2f(0,CAR_HEIGHT));

    this->model.setFillColor(sf::Color(randomColor(), randomColor(), randomColor()));
    this->model.setOrigin(CAR_WIDTH/2, CAR_HEIGHT/2);
}

void Car::generateSensors() {
    for (auto i = 0; i < SENSORS_COUNT; i++) {
        auto sensor = &this->sensors[i];
        auto heightFactor = -1*abs(i - SENSORS_COUNT / 2) + SENSORS_COUNT / 2;
        sensor->setPointCount(4);
        sensor->setPoint(0, sf::Vector2f(CAR_WIDTH/2 - 2, -15*heightFactor));
        sensor->setPoint(1, sf::Vector2f(CAR_WIDTH/2 - 2, -15*heightFactor-SENSOR_LEN));
        sensor->setPoint(2, sf::Vector2f(CAR_WIDTH/2 + 2, -15*heightFactor-SENSOR_LEN));
        sensor->setPoint(3, sf::Vector2f(CAR_WIDTH/2 + 2, -15*heightFactor));
        sensor->setOrigin(CAR_WIDTH/2, CAR_HEIGHT/2);
        sensor->rotate(i * (120 / (SENSORS_COUNT - 1)) + 30);
        sensor->setFillColor(sf::Color::Red);
    }
}

void Car::move(sf::Vector2<float> vector2) {
    this->move(vector2.x, vector2.y);
}

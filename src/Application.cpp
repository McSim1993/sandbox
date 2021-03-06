//
// Created by Maxim Gribov on 02.01.18.
//

#include "Application.hpp"
#include <fstream>
#include <ostream>
#include <iostream>
#include <sstream>

void Application::start() {
    std::srand(unsigned(std::time(0)));
    this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "", sf::Style::None);
    this->window->setVerticalSyncEnabled(true);

    if (!font.loadFromFile("../OpenSans-Regular.ttf")) {
        std::cout << "Error loading font" << std::endl;
    }
    this->debugText.setFont(this->font);
    this->debugText.setPosition(100,100);
    this->debugText.setCharacterSize(24);
    this->debugText.setFillColor(sf::Color::Red);


    std::vector<Car> cars(15);
    for (auto &car : cars) {
        car.move(100, WINDOW_HEIGHT/2);
    }

    this->loadWalls();

    while (this->window->isOpen())
    {
        sf::Event event{};
        while (this->window->pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::KeyPressed:
                    this->processKeyPressed(event);
                    break;
                case sf::Event::KeyReleased:
                    this->processKeyReleased(event);
                    break;
                case sf::Event::MouseButtonPressed:
                    this->processMouseKeyPressed(event);
                    break;
                case sf::Event::MouseButtonReleased:
                    this->processMouseKeyReleased(event);
                    break;
                case sf::Event::MouseMoved:
                    this->processMouseMoved(event);
                    break;
                case sf::Event::MouseWheelScrolled:
                    this->processWheelScroll(event);
                    break;
                default:
                    break;
            }
        }

        this->window->clear(bgColor);

        for (auto &car : cars) {
            car.tick(this->walls);
        }

        auto maxFitnessCar = cars[0];
        for (auto &car : cars) {
            if (car.getFitness() > maxFitnessCar.getFitness()) {
                maxFitnessCar = car;
            }
            if (car.isActive()) {
                car.draw(this->window);
            }
        }
        if (this->newWall) {
            window->draw(*this->newWall);
        }
        for (auto &wall : walls) {
            window->draw(*wall);
        }

        if (this->currentInputState == NONE) {
            const auto center = maxFitnessCar.getPosition();
            auto view = this->window->getView();
            view.setCenter(center);
            this->window->setView(view);
        }
        this->drawCarUI(maxFitnessCar);
        this->window->display();
    }
}

void Application::processKeyPressed(sf::Event event) {
    switch (event.key.code) {
        case sf::Keyboard::Escape:
        case sf::Keyboard::Q:
            this->window->close();
            break;

        case sf::Keyboard::Space:
            if (this->currentInputState == NONE) {
                this->currentInputState = DRAW;
            }
        default:
            break;

    }
}

void Application::processKeyReleased(sf::Event event) {
    switch (event.key.code) {
        case sf::Keyboard::Space:
            this->currentInputState = NONE;
            delete this->newWall;
            this->newWall = NULL;
            this->mousePos = {
                    x: 0,
                    y: 0
            };
            break;

        case sf::Keyboard::S:
            this->saveWalls();
        default:
            break;
    }
}

void Application::processMouseKeyPressed(sf::Event event) {
    switch (event.mouseButton.button) {
        case sf::Mouse::Left:
            this->mousePos.x = event.mouseButton.x;
            this->mousePos.y = event.mouseButton.y;
            switch (this->currentInputState) {
                case DRAW:
                    if (this->newWall) {
                        this->walls.push_back(this->newWall);
                        this->newWall = NULL;
                    }
                    break;
                case NONE:
                    this->currentInputState = DRAG;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void Application::processMouseMoved(sf::Event event) {
    sf::View tmp;
    switch (this->currentInputState) {
        case DRAG:
            tmp = this->window->getView();
            tmp.move(this->mousePos.x - event.mouseMove.x, this->mousePos.y - event.mouseMove.y);
            this->window->setView(tmp);
            this->mousePos = event.mouseMove;
            break;
        case DRAW:
            delete this->newWall;

            if (this->mousePos.x == 0 && this->mousePos.y == 0) {
                this->mousePos = event.mouseMove;
            } else {
                auto x = this->window->getView().getCenter().x - WINDOW_WIDTH/2;
                auto y = this->window->getView().getCenter().y - WINDOW_HEIGHT/2;
                this->newWall = new Wall(sf::Vector2f(this->mousePos.x + x, this->mousePos.y + y),
                                         sf::Vector2f(event.mouseMove.x + x, event.mouseMove.y + y));
            }
            break;
        case NONE:
            break;
    }
}

void Application::processMouseKeyReleased(sf::Event event) {
    switch (this->currentInputState) {
        case DRAG:
            this->currentInputState = NONE;
            this->mousePos = {
                    x: 0,
                    y: 0
            };
            break;

        default:
            break;
    }
}

void Application::processWheelScroll(sf::Event event) {
    auto tmp = this->window->getView();
    tmp.zoom(1 - event.mouseWheelScroll.delta / 50.0f);
    this->window->setView(tmp);
}

void Application::saveWalls() {
    std::ofstream out("walls.txt");
    for (auto &wall : this->walls) {
        out << wall->getPoint(0).x << "\t" << wall->getPoint(0).y << "\t";
        out << wall->getPoint(1).x << "\t" << wall->getPoint(1).y << "\t";
        out << wall->getPoint(2).x << "\t" << wall->getPoint(2).y << "\t";
        out << wall->getPoint(3).x << "\t" << wall->getPoint(3).y << "\t" << std::endl;
    }
    out.close();

    printf("Walls Saved");
}

void Application::loadWalls() {
    std::ifstream in("walls.txt");
    while (in.good()) {
        sf::Vector2f p1,p2,p3,p4;
        in >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y >> p4.x >> p4.y;
        if (p1.x != 0) {
            this->walls.push_back(new Wall(p1, p2, p3, p4));
        }
    }
}

void Application::drawMousePos(sf::Event::MouseMoveEvent event) {
    std::stringstream ss;
    auto x = this->window->getView().getCenter().x - WINDOW_WIDTH/2;
    auto y = this->window->getView().getCenter().y - WINDOW_HEIGHT/2;
    ss << "X: " << event.x + x  << "; Y: " << event.y + y;
    this->debugText.setString(ss.str());
}

void Application::drawCarUI(Car car) {
    std::stringstream ss;
    ss << "Fitness: " << car.getFitness();
    this->debugText.setString(ss.str());
    window->draw(debugText);
}



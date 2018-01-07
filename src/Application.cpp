//
// Created by Maxim Gribov on 02.01.18.
//

#include "Application.hpp"

void Application::start() {
    std::srand(unsigned(std::time(0)));
    this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "");
    this->window->setVerticalSyncEnabled(true);

    std::vector<sf::Drawable*> drawable;
    std::vector<Car> cars(15);
    for (auto &car : cars) {
        car.setPosition(100, WINDOW_HEIGHT/2);
        drawable.push_back(&car);
    }


    while (this->window->isOpen())
    {
        sf::Event event;
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
                default:
                    break;
            }
        }

        this->window->clear(bgColor);

        for (auto &car : cars) {
            car.tick();
        }

        for (auto &obj : drawable) {
            this->window->draw(*obj);
        }
        if (this->newWall) {
            window->draw(*this->newWall);
        }
        for (auto &chain : walls) {
            for (auto &wall : *chain) {
                window->draw(*wall);
            }
        }

        printf("Chains: %d. Walls: %d\n", (int) this->walls.size(), this->walls.back() ? (int) this->walls.back()->size() : 0);

        this->window->display();
    }
}

void Application::processKeyPressed(sf::Event event) {
    switch (event.key.code) {
        case sf::Keyboard::Escape:
        case sf::Keyboard::Q:
            this->window->close();
            delete this->window;
            break;

        case sf::Keyboard::Space:
            if (this->currentInputState == NONE) {
                this->currentInputState = DRAW;
                this->walls.push_back(new std::list<Wall*>());
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
                        this->walls.back()->push_back(this->newWall);
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
                if (this->walls.back()->empty()) {
                    this->newWall = new Wall(sf::Vector2f(this->mousePos.x, this->mousePos.y),
                                             sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
                } else {
                    auto last = this->walls.back()->back();
                    this->newWall = new Wall(last->getPoint(1), last->getPoint(0),
                                             sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
                }
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
            break;

        default:
            break;
    }
}
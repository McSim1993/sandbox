//
// Created by Maxim Gribov on 02.01.18.
//

#include "Application.hpp"

void Application::start() {
    std::srand(unsigned(std::time(0)));
    this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "", sf::Style::None);
    this->window->setVerticalSyncEnabled(true);

    std::vector<sf::Drawable*> drawable;
    std::vector<Car> cars(15);
    for (auto &car : cars) {
        car.setPosition(100, WINDOW_HEIGHT/2);
        drawable.push_back(&car);
    }

    std::vector<Wall> walls(2);


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

        this->window->display();
    }
}

void Application::processKeyPressed(sf::Event event) {
    switch (event.key.code) {
        case sf::Keyboard::Escape:
        case sf::Keyboard::Q:
            this->window->close();
            break;
        default:
            break;

    }
}

void Application::processKeyReleased(sf::Event event) {

}

void Application::processMouseKeyPressed(sf::Event event) {
    switch (event.mouseButton.button) {
        case sf::Mouse::Left:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                this->currentInputState = DRAW;
                this->walls.push_back(new std::list<sf::Shape*>());
            } else {
                this->currentInputState = DRAG;
            }
            this->mousePos.x = event.mouseButton.x;
            this->mousePos.y = event.mouseButton.y;
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
//            this->newWall = new sf::ConvexShape();
//            this->newWall->setPointCount(4);

            break;
        case NONE:
            break;
    }
}

void Application::processMouseKeyReleased(sf::Event event) {
    this->currentInputState = NONE;
}

#include <SFML/Graphics.hpp>
#include "Car.hpp"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

int main()
{
    std::srand(unsigned(std::time(0)));
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "", sf::Style::None);
    window.setVerticalSyncEnabled(true);
    sf::Color bgColor(167, 200, 209);

    std::vector<sf::Drawable*> drawable;
    std::vector<Car> cars(5);
    for (auto &car : cars) {
        car.setPosition(100, WINDOW_HEIGHT/2);
        drawable.push_back(&car);
    }

    std::vector<Wall> walls(2);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed &&
                    (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Q))
                window.close();
        }

        window.clear(bgColor);

        for (auto &car : cars) {
            car.tick();
        }

        for (auto &obj : drawable) {
            window.draw(*obj);
        }

        window.display();
    }

    return 0;
}
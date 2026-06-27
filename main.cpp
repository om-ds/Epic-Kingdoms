#include <SFML/Graphics.hpp>
#include "tilePlain.cpp"


const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const float CAMERA_SPEED = 300.0;


int main()
{
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Hex Game", sf::Style::Fullscreen);

    sf::Texture texturePlain;
    texturePlain.loadFromFile("./textures/debug/texturePlain.png");
    tilePlain test(100, 100, texturePlain);


    sf::View camera(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Delete)
                {
                    window.close();
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            camera.move(-CAMERA_SPEED * dt, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            camera.move(CAMERA_SPEED * dt, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            camera.move(0, -CAMERA_SPEED * dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            camera.move(0, CAMERA_SPEED * dt);
        }

        window.setView(camera);

        window.clear(sf::Color::Black);
        window.draw(test.sprite);
        window.display();
    }

    return 0;
}

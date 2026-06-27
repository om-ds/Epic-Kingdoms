#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include "Tile.cpp"


const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const float CAMERA_SPEED = 300.0;
const float TILE_HEX_SIZE = 50.0;
const float dx = 88;
const float dy = 75;


int main()
{
    //LOADING TEXTURES
    sf::Texture texturePlain, textureDesert;
    texturePlain.loadFromFile("./textures/debug/texturePlain.png");
    textureDesert.loadFromFile("./textures/debug/textureDesert.png");

    int cols, rows;
    std::cin >> cols;
    std::cin >> rows;

    //CREATING TILE GRID
    std::vector<std::vector<Tile>> grid(rows, std::vector<Tile>(cols));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            grid[i][j].setTile(TileType::Desert, &textureDesert, (static_cast<float>(j) + 0.5f * static_cast<float>(i % 2)) * dx, static_cast<float>(i) * dy);
        }
    }

    //CREATING WINDOW AND CAMERA
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Hex Game", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    sf::View camera(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
    sf::Clock clock;

    //MAIN CYCLE
    while (window.isOpen())
    {
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

        //CAMERA MOVEMENT
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            camera.move(-CAMERA_SPEED * dt, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            camera.move(CAMERA_SPEED * dt, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            camera.move(0, -CAMERA_SPEED * dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            camera.move(0, CAMERA_SPEED * dt);
        }
        window.setView(camera);

        //DRAWING
        window.clear(sf::Color(0, 128, 128));

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                grid[i][j].draw(window);
            }
        }

        window.display();
    }
}

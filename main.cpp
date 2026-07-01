#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include <memory>
#include "Collision.hpp"
#include "Button.hpp"
#include "Tile.hpp"
#include "MeleeUnit.hpp"
#include "RangedUnit.hpp"
#include "CivilianUnit.hpp"


const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const float CAMERA_SPEED = 300.0;
const float TILE_HEX_SIZE = 50.0;


int main()
{
    //LOADING TILE TEXTURES
    sf::Texture texturePlain, textureDesert;
    texturePlain.loadFromFile("./textures/debug/texturePlain.png");
    textureDesert.loadFromFile("./textures/debug/textureDesert.png");

    //CREATING BUTTONS
    sf::Font fontNasa21;
    fontNasa21.loadFromFile("./fonts/Nasa21.ttf");
    Button buttonNextTurn(4 * SCREEN_WIDTH / 5, 0, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 10, "Next turn", fontNasa21, 45, sf::Color(0, 96, 96), sf::Color(96, 96, 96));

    //LOADING UNIT TEXTURES
    sf::Texture textureSkeleton;
    textureSkeleton.loadFromFile("./textures/debug/textureSkeleton.png");

    //POINTERS FOR SELECTED OBJECTS
    Unit* selectedUnit = nullptr;
    int selectedUnitIndex = 0;
    Tile* selectedTile = nullptr;

    //CREATING TILE GRID
    int cols, rows;
    std::cin >> cols;
    std::cin >> rows;

    std::vector<std::vector<Tile>> grid(rows, std::vector<Tile>(cols));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            grid[i][j].setTile(TileType::Plain, &texturePlain, (static_cast<float>(j) + 0.5f * static_cast<float>(i % 2)) * dx, static_cast<float>(i) * dy, i, j);
        }
    }

    //CREATING TEST UNIT
    std::vector<std::unique_ptr<Unit>> units;
    units.push_back(std::make_unique<MeleeUnit>(MeleeType::lightInfantry, &grid[1][2], &textureSkeleton));

    //CREATING WINDOW AND CAMERA
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Epic Kingdoms", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    sf::View camera(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
    sf::View ui(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
    sf::Vector2f mousePosition;
    sf::Clock clock;

    //MAIN CYCLE
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        window.setView(camera);
        mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

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

            //RIGHT MOUSE BUTTON CLICK
            if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Right)
            {
                selectedUnit = nullptr;
                selectedTile = nullptr;
            }

            //LEFT MOUSE BUTTON CLICK
            if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left)
            {
                for (int i = 0; i < units.size(); i++)
                {
                    if (Collision::SingleSpritePixelTest(units[i]->sprite, mousePosition))
                    {
                        selectedUnit = units[i].get();
                    }
                }

                for (int i = 0; i < rows; i++)
                {
                    for (int j = 0; j < cols; j++)
                    {
                        if (Collision::SingleSpritePixelTest(grid[i][j].sprite, mousePosition))
                        {
                            selectedTile = &grid[i][j];
                        }
                    }
                }

                if (selectedTile != nullptr and selectedUnit != nullptr and selectedTile != selectedUnit->currentTile)
                {
                    selectedUnit->moveUnit(selectedTile);
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

        //DRAWING TILE GRID
        window.clear(sf::Color(0, 128, 128));

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                grid[i][j].draw(window);
            }
        }

        //DRAWING TEST UNIT
        for (int i = 0; i < units.size(); i++)
        {
            units[i]->draw(window);
        }

        //UPDATING UI
        window.setView(ui);
        mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        buttonNextTurn.update(window, mousePosition);
        if (buttonNextTurn.isClicked(event, mousePosition))
        {
            for (int i = 0; i < units.size(); i++)
            {
                units[i]->currentMovementPoints = units[i]->maxMovementPoints;
            }
        }

        window.display();
    }
}

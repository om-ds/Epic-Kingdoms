#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.hpp"


class Unit
{
public:
    sf::Sprite sprite;
    int x;
    int y;
    int hp;
    int maxHp;
    int currentMovementPoints;
    int maxMovementPoints;
    Tile* currentTile;

    Unit() = default;

    ~Unit() = default;

    void draw(sf::RenderWindow& window)
    {
        window.draw(sprite);
    }
};

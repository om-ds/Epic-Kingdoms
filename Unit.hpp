#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.hpp"


class Unit
{
public:
    sf::Sprite sprite;
    int x;
    int y;
    float hp;
    float maxHp;
    int currentMovementPoints;
    int maxMovementPoints;
    int unitCost;
    float infantryDamageFactor;
    float cavarlyDamageFactor;
    float rangedDamageFactor;
    float cityDamageFactor;

    Tile* currentTile;

    Unit() = default;

    ~Unit() = default;

    void draw(sf::RenderWindow& window)
    {
        window.draw(sprite);
    }
};

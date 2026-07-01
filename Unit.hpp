#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.hpp"


enum class Race : unsigned char
{
    undead,
    human
};

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
    Race race;

    ~Unit() = default;

    virtual void draw(sf::RenderWindow& window)
    {
        window.draw(sprite);
    }

    virtual void moveUnit(Tile* tile) = 0;
};

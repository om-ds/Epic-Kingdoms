#pragma once
#include <SFML/Graphics.hpp>
#include "GetRandomNumber.hpp"
#include "Tile.hpp"


enum class Race : unsigned char
{
    undead,
    human
};

enum class UnitRole : unsigned char
{
    melee,
    ranged,
    civilian
};

class Unit
{
public:
    sf::Sprite sprite;
    int x;
    int y;
    float currentHp;
    float maxHp;
    float minDamage;
    float maxDamage;
    int currentMovementPoints;
    int maxMovementPoints;
    int unitCost;
    float infantryDamageFactor;
    float cavarlyDamageFactor;
    float rangedDamageFactor;
    float cityDamageFactor;
    Tile* currentTile;
    Race race;
    UnitRole role;

    ~Unit() = default;

    virtual void draw(sf::RenderWindow& window)
    {
        window.draw(sprite);
    }

    virtual void moveUnit(Tile* tile) = 0;

    virtual void attackUnit(Unit* unit) = 0;

    bool isAlife()
    {
        return (currentHp > 0);
    }
};

float calculateDamage(Unit* unit)
{
    float result = getRandomFloat(unit->minDamage, unit->maxDamage) * unit->currentHp / unit->maxHp;
    return result;
}

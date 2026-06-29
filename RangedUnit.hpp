#pragma once
#include "Unit.hpp"


enum class RangedType : unsigned char
{
    Archer,
    Crossbowman,
    Catapult
};


class RangedUnit : public Unit
{
public:
    int attackRange;

    RangedUnit(Tile* tile, sf::Texture* texturePointer)
    {
        currentTile = tile;
        sprite.setTexture(*texturePointer);
        sprite.setPosition((static_cast<float>(tile->y) + 0.5f * static_cast<float>(tile->x % 2)) * dx, static_cast<float>(tile->x) * dy);
    }
};

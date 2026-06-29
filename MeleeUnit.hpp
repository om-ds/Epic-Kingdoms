#pragma once
#include "Unit.hpp"


enum class MeleeType : unsigned char
{
    lightInfantry,
    heavyInfantry,
    lightCavarly,
    heavyCavarly,
    siegeTower
};


class MeleeUnit : public Unit
{
public:
    MeleeUnit(Tile* tile, sf::Texture* texturePointer)
    {
        currentTile = tile;
        sprite.setTexture(*texturePointer);
        sprite.setPosition((static_cast<float>(tile->y) + 0.5f * static_cast<float>(tile->x % 2)) * dx, static_cast<float>(tile->x) * dy);
    }
};

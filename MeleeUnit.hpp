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
    MeleeType type;

    MeleeUnit(MeleeType type_, Race race_, Tile* tile, sf::Texture* texturePointer)
    {
        currentTile = tile;
        sprite.setTexture(*texturePointer);
        x = tile->x;
        y = tile->y;
        type = type_;
        race = race_;
        sprite.setPosition((static_cast<float>(tile->y) + 0.5f * static_cast<float>(tile->x % 2)) * dx, static_cast<float>(tile->x) * dy);

        if (type == MeleeType::lightInfantry)
        {
            maxMovementPoints = 3;
            currentMovementPoints = 3;
        }

        tile->currentUnit = this;
    }

    void moveUnit(Tile* tile) override
    {
        if (currentMovementPoints > 0)
        {
            x = tile->x;
            y = tile->y;
            currentTile->currentUnit = nullptr;
            currentTile = tile;
            currentMovementPoints -= tile->movementCost;
            sprite.setPosition((static_cast<float>(tile->y) + 0.5f * static_cast<float>(tile->x % 2)) * dx, static_cast<float>(tile->x) * dy);
        }
    }
};

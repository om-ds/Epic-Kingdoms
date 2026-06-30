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

/*int x;
int y;
float hp;
float maxHp;
int currentMovementPoints;
int maxMovementPoints;
int unitCost;
float infantryDamageFactor;
float cavarlyDamageFactor;
float rangedDamageFactor;
float cityDamageFactor;*/

class MeleeUnit : public Unit
{
public:
    MeleeUnit(MeleeType type, Tile* tile, sf::Texture* texturePointer)
    {
        currentTile = tile;
        sprite.setTexture(*texturePointer);
        x = tile->x;
        y = tile->y;
        sprite.setPosition((static_cast<float>(tile->y) + 0.5f * static_cast<float>(tile->x % 2)) * dx, static_cast<float>(tile->x) * dy);

        if (type == MeleeType::lightInfantry)
        {
            maxMovementPoints = 3;
            currentMovementPoints = 3;
        }
    }

    void moveUnit(Tile* tile) override
    {
        x = tile->x;
        y = tile->y;
        sprite.setPosition((static_cast<float>(tile->y) + 0.5f * static_cast<float>(tile->x % 2)) * dx, static_cast<float>(tile->x) * dy);
    }
};

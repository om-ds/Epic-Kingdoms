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
    UnitRole role;

    MeleeUnit(MeleeType type_, Race race_, Tile* tile, sf::Texture* texturePointer)
    {
        role = UnitRole::melee;
        currentTile = tile;
        tile->currentUnit = this;
        sprite.setTexture(*texturePointer);
        x = tile->x;
        y = tile->y;
        type = type_;
        race = race_;
        sprite.setPosition((static_cast<float>(tile->y) + 0.5f * static_cast<float>(tile->x % 2)) * dx, static_cast<float>(tile->x) * dy);

        if (type == MeleeType::lightInfantry)
        {
            maxMovementPoints = 3;
            currentMovementPoints = maxMovementPoints;
            maxHp = 100;
            currentHp = maxHp;
            minDamage = 35;
            maxDamage = 45;
        }

        if (type == MeleeType::heavyInfantry)
        {
            maxMovementPoints = 2;
            currentMovementPoints = maxMovementPoints;
            maxHp = 200;
            currentHp = maxHp;
            minDamage = 50;
            maxDamage = 65;
        }

        tile->currentUnit = this;
    }

    void moveUnit(Tile* tile) override
    {
        if (currentMovementPoints > 0 and tile->currentUnit == nullptr)
        {
            x = tile->x;
            y = tile->y;
            currentTile->currentUnit = nullptr;
            currentTile = tile;
            currentMovementPoints -= tile->movementCost;
            sprite.setPosition((static_cast<float>(tile->y) + 0.5f * static_cast<float>(tile->x % 2)) * dx, static_cast<float>(tile->x) * dy);
        }
    }

    void attackUnit(Unit* enemy) override
    {
        if (currentMovementPoints > 0)
        {
            currentMovementPoints -= 1;
            float inflictedDamage = calculateDamage(this);
            float receivedDamage = calculateDamage(enemy);
            currentHp -= receivedDamage;
            enemy->currentHp -= inflictedDamage;

            if (currentHp > 0 and enemy->currentHp <= 0)
            {
                currentMovementPoints += 1;
                enemy->currentTile->currentUnit = nullptr;
                this->moveUnit(enemy->currentTile);
            }
        }
    }
};

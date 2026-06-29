#pragma once
#include <SFML/Graphics.hpp>

inline const float dx = 88;
inline const float dy = 75;

enum class TileType : unsigned char
{
    Plain,
    Desert
};


class Tile
{
public:
    int x;
    int y;
    int movementCost;
    float defenceFactor;
    bool noCity;
    bool noUnit;
    sf::Sprite sprite;

    Tile() = default;

    void setTile(TileType type, sf::Texture* texturePointer, float X, float Y, int x_, int y_)
    {
        sprite.setTexture(*texturePointer);
        sprite.setPosition(X, Y);
        x = x_;
        y = y_;

        if (type == TileType::Plain)
        {
            movementCost = 1;
            defenceFactor = 1.0;
        }

        if (type == TileType::Desert)
        {
            movementCost = 1;
            defenceFactor = 1.0;
        }
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(sprite);
    }
};

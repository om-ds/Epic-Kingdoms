#include <SFML/Graphics.hpp>


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
    bool noCity;
    bool noUnit;
    sf::Sprite sprite;

    Tile() = default;

    void setTile(TileType type, sf::Texture* texturePointer, float X, float Y)
    {
        sprite.setTexture(*texturePointer);
        sprite.setPosition(X, Y);
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(sprite);
    }
};

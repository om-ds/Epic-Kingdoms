#include <SFML/Graphics.hpp>

class tile
{
public:
    float x;
    float y;
    int movementCost;
    sf::Texture texture;
    sf::Sprite sprite;

    tile(float X, float Y, sf::Texture& t)
    {
        sprite.setTextureRect(sf::IntRect(0, 0, 88, 102));
        sprite.setTexture(t);
        sprite.setPosition(X, Y);
    }
};

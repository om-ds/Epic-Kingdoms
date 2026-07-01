#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button
{
public:
    sf::RectangleShape shape;
    sf::Text text;

    Button() = default;

    Button(float x, float y, float width, float height, std::string label, sf::Font& font, int fontSize)
    {
        shape.setSize(sf::Vector2f(width, height));
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color(0, 96, 96));
        shape.setOutlineThickness(2.f);
        shape.setOutlineColor(sf::Color(0, 0, 0));

        text.setFont(font);
        text.setString(label);
        text.setCharacterSize(fontSize);
        text.setFillColor(sf::Color::White);

        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
        text.setPosition(x + width / 2.f, y + height / 2.f);
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(shape);
        window.draw(text);
    }

    bool isHovered(sf::Vector2f& mousePos)
    {
        return shape.getGlobalBounds().contains(mousePos);
    }

    /*void update(const sf::Vector2f& mousePos)
    {
        if (isHovered(mousePos))
        {
            shape.setFillColor(sf::Color(80, 80, 80));
        }
        else
        {
            shape.setFillColor(sf::Color(60, 60, 60));
        }
    }*/
};

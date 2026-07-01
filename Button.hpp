#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button
{
public:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Color passive;
    sf::Color active;

    Button() = default;

    Button(float x, float y, float width, float height, std::string label, sf::Font& font, int fontSize, sf::Color passive_, sf::Color active_)
    {
        shape.setSize(sf::Vector2f(width, height));
        shape.setPosition(x, y);
        shape.setFillColor(passive);
        shape.setOutlineThickness(2.f);
        shape.setOutlineColor(sf::Color(0, 0, 0));

        passive = passive_;
        active = active_;

        text.setFont(font);
        text.setString(label);
        text.setCharacterSize(fontSize);
        text.setFillColor(sf::Color::White);

        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
        text.setPosition(x + width / 2.f, y + height / 2.f - fontSize / 3);
    }

    bool isHovered(sf::Vector2f& mousePos)
    {
        return shape.getGlobalBounds().contains(mousePos);
    }

    void update(sf::RenderWindow& window, sf::Vector2f& mousePos)
    {
        if (isHovered(mousePos))
        {
            shape.setFillColor(active);
        }

        else
        {
            shape.setFillColor(passive);
        }

        window.draw(shape);
        window.draw(text);
    }

    bool isClicked(sf::Event& event, sf::Vector2f& mousePos)
    {
        if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left)
        {
            return shape.getGlobalBounds().contains(mousePos);
        }
        return false;
    }
};

#pragma once

#include <SFML/Graphics.hpp>

enum PLATFORMS {
    OBJECT_GROUND,
    OBJECT_ONE,
    OBJECT_TWO,
    OBJECT_THREE,
    OBJECT_COUNT
};

class Platform
{
public:
    Platform(std::string texture, sf::Vector2f fSize, sf::Vector2f fPos);
    ~Platform();

    sf::RectangleShape Entity;

private:
    sf::Texture platformTexture;
    sf::Vector2f platformSize;
    sf::Vector2f platformPosition;
};
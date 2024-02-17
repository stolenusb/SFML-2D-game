#pragma once

#include <SFML\Graphics.hpp>

class Animation 
{
    public:
    void Set(sf::Sprite *sprt, int imgCount, sf::Vector2u imgSize);
    void Animate();

    public:
    int imageCount = 0;

    private:
    sf::Sprite *sprite;
    sf::Vector2u imageSize;
    sf::IntRect rect;
    sf::Clock animClock;
};
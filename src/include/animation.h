#pragma once

#include <SFML\Graphics.hpp>

class Animation 
{
public:
    Animation(sf::Sprite &Sprite, unsigned int animationSize);
    ~Animation();

    void Animate();
    void Set(sf::Texture &texture, unsigned int imageCount);

    bool lookRight =  true;

private:
    sf::Sprite &Sprite;
    sf::IntRect textureRect;
    sf::Clock clock;
    unsigned int imgCount;
    unsigned int currImage;
};
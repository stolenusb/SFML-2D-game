#pragma once

#include <SFML\Graphics.hpp>
#include "animation.h"

class Player
{
public:
    Player();
    ~Player();

    void Update(double deltaTime);

    sf::Sprite Sprite;
    Animation animation;

private:
    sf::Vector2f Velocity;
};
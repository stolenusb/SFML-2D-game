#pragma once

#include <SFML\Graphics.hpp>
#include "animation.h"

class Player
{
public:
    Player();
    ~Player();

    void Update(double deltaTime);
    void Draw(sf::RenderWindow &window);

    sf::Sprite Sprite;
    sf::RectangleShape entity;
    Animation animation;

private:
    sf::Vector2f Velocity;
    float moveSpeed = 0.2f;
    float jumpSpeed = 1.0f;
    bool canJump = true;
};
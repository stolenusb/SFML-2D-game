#pragma once

#include <SFML\Graphics.hpp>
#include "animation.h"

class Player
{
public:
    Player();
    ~Player();

    void Jumped(sf::Event &event);
    void Update(double deltaTime);
    void Draw(sf::RenderWindow &window);
    
    sf::Sprite Sprite;
    Animation animation;

private:
    sf::Vector2f Velocity;
    float moveSpeed = 200.0f;
    float jumpForce = 400.0f;
    bool Jumping = false;
};
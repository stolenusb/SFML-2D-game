#pragma once

#include <SFML\Graphics.hpp>
#include "animation.h"
#include "collision.h"

class Player
{
public:
    Player();
    ~Player();

    void Update(double deltaTime);
    void Jumped(sf::Event &event);
    void Draw(sf::RenderWindow &window);  

    Collider collider;  

private:
    void setPosition(double x, double y);
    void Input();

    sf::RectangleShape Entity;
    sf::Sprite Sprite;
    Animation animation;
    sf::Vector2f Velocity;

    const sf::Vector2f playerSize = sf::Vector2f(42, 64);
    const float moveSpeed = 100.0f;
    const float jumpForce = 400.0f;
    
    sf::RectangleShape platform;
    sf::RectangleShape ground;
};
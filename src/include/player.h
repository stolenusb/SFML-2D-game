#pragma once

#include <iostream>
#include <vector>
#include <SFML\Graphics.hpp>
#include "animation.h"
#include "collision.h"
#include "projectile.h"

class Player
{
public:
    Player(sf::RenderWindow &window, sf::Vector2f entitySize, float moveSpeed, float jumpForce);
    ~Player();

    void Update();
    void Jump();
    void Draw();  

    Collider collider;
    Projectile projectiles;

private:
    void setPosition(float x, float y);
    void Input();

    sf::Clock clock;
    sf::RenderWindow &window;

    sf::Vector2f entitySize;
    sf::RectangleShape Entity;
    sf::Sprite Sprite;

    Animation animation;

    sf::Vector2f Velocity;
    float moveSpeed;
    float jumpForce;
    float projectileSpeed = 200.f;
};
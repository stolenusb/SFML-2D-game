#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "collision.h"
#include "animation.h"

class Enemy
{
public:
    Enemy(sf::Vector2f entitySize, float positionX);
    ~Enemy();

    void Update();
    void Hurt(float damage);
    void Draw(sf::RenderWindow &window);

    Collider collider;

private:
    void setPosition(double x, double y);
    
    sf::Clock clock;
    
    sf::Vector2f entitySize;
    sf::RectangleShape Entity;
    sf::Sprite Sprite;

    Animation animation;

    sf::Vector2f Velocity;
    sf::Text enemyHP;

    sf::Font font;

    unsigned int Health = 3000;
    bool isDead = false;
};
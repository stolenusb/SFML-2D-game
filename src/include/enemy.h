#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "collision.h"
#include "animation.h"

enum ENEMY_TEXTURES
{
    ENEMY_IDLE,
    ENEMY_TEXTURES_COUNT
};

class Enemy
{
public:
    Enemy(sf::Vector2f entitySize, float positionX);
    ~Enemy();

    void Update();
    void Draw(sf::RenderWindow &window);

    Collider collider;

private:
    void setPosition(double x, double y);
    void loadTextures();
    
    sf::Clock clock;
    
    sf::Vector2f entitySize;
    sf::RectangleShape Entity;
    sf::Sprite Sprite;
    sf::Texture Texture[ENEMY_TEXTURES_COUNT];

    Animation animation;

    sf::Vector2f Velocity;
    float Health;
};
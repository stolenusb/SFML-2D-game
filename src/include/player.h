#pragma once

#include <iostream>
#include <vector>
#include <SFML\Graphics.hpp>
#include "animation.h"
#include "collision.h"
#include "projectile.h"

enum PLAYER_TEXTURES
{
    PLAYER_IDLE,
    PLAYER_WALK,
    PLAYER_RUN,
    PLAYER_JUMP,
    PLAYER_ATTACK,
    PLAYER_PROJECTILE,
    PLAYER_TEXTURES_COUNT
};

class Player
{
public:
    Player(sf::RenderWindow &window, sf::Vector2f entitySize, float moveSpeed, float jumpForce);
    ~Player();

    void Update();
    void Jump();
    void Draw();  

    Collider collider;  

private:
    void setPosition(float x, float y);
    void loadTextures();
    void Input();

    sf::Clock clock;
    sf::RenderWindow &window;

    sf::Vector2f entitySize;
    sf::RectangleShape Entity;
    sf::Sprite Sprite;
    sf::Texture Texture[PLAYER_TEXTURES_COUNT];
    Animation animation;

    sf::Vector2f Velocity;
    float moveSpeed;
    float jumpForce;
    float projectileSpeed = 100.f;
    
    Projectile projectiles;
};
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
    Player(sf::RenderWindow &window, sf::Vector2f playerSize, double moveSpeed, double jumpForce);
    ~Player();

    void Update();
    void Jump();
    void Shoot();
    void Draw();  

    Collider collider;  

private:
    void loadTextures();
    void setPosition(double x, double y);
    void Input();

    sf::Clock clock;
    sf::RenderWindow &window;

    sf::Vector2f playerSize;
    sf::RectangleShape Entity;
    sf::Sprite Sprite;
    sf::Texture Texture[PLAYER_TEXTURES_COUNT];
    Animation animation;

    sf::Vector2f Velocity;
    double moveSpeed;
    double jumpForce;
    float projectileSpeed = 100.f;
    
    Projectile projectile;
    std::vector<Projectile> projectiles;
};
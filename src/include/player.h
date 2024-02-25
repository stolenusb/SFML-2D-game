#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "animation.h"
#include "collision.h"

enum PLAYER_TEXTURES
{
    PLAYER_IDLE,
    PLAYER_WALK,
    PLAYER_RUN,
    PLAYER_JUMP,
    PLAYER_ATTACK,
    PLAYER_BULLET,
    PLAYER_TEXTURES_COUNT
};

class Player
{
public:
    Player(sf::Vector2f playerSize, double moveSpeed, double jumpForce);
    ~Player();

    void Update();
    void Jump();
    void Draw(sf::RenderWindow &window);  

    Collider collider;  

private:
    void loadTextures();
    void setPosition(double x, double y);
    void Input();

    sf::RectangleShape Entity;
    sf::Sprite Sprite;
    sf::Texture Texture[PLAYER_TEXTURES_COUNT];
    Animation animation;
    sf::Vector2f Velocity;
    sf::Vector2f playerSize;
    sf::Clock clock;
    double moveSpeed;
    double jumpForce;

    sf::Sprite Bullet;
    Animation animationBullet;
    bool bulletAttack = false;
    double bulletVelocity;
};
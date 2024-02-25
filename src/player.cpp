#include "player.h"
#include "math.h"
#include <iostream>

Player::Player() :
    animation(Sprite, 128), collider(Entity, Sprite, Velocity)
{
    Entity.setSize(playerSize);
    Entity.setOutlineThickness(3.0f);
    Entity.setFillColor(sf::Color::Transparent);
    setPosition(50, 433);
    animation.loadTextures();
}

Player::~Player()
{
}

void Player::Update(double deltaTime)
{
    // Frame Initialization
    if(collider.bCollidingWithGround)
        Velocity.x = 0.0;
    
    Velocity.y += 9.8f;
    animation.Set(PLAYER_IDLE, 8);

    // Input
    Input();

    // Update
    animation.Animate();
    Entity.move(Velocity.x * deltaTime, Velocity.y * deltaTime);
    Sprite.move(Velocity.x * deltaTime, Velocity.y * deltaTime);
}

void Player::Input()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        setPosition(50.f, 433.0f);
    
    if(collider.bCollidingWithGround)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            animation.lookRight = true;
            Velocity.x = moveSpeed;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            animation.lookRight = false;
            Velocity.x = -moveSpeed;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))) {
            animation.Set(PLAYER_RUN, 8);
            Velocity.x *= 2.50f;
        }

        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)))
            animation.Set(PLAYER_WALK, 7);
    }

    else
        animation.Set(PLAYER_JUMP, 8);
}

void Player::Jumped(sf::Event &event)
{
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && collider.bCollidingWithGround) {
        Velocity.y -= jumpForce;
        collider.bCollidingWithGround = false;
    }
}

void Player::Draw(sf::RenderWindow &window)
{
    window.draw(Sprite);
    window.draw(Entity);
}

void Player::setPosition(double x, double y)
{
    Entity.setPosition(x, y);
    Sprite.setPosition(x - playerSize.x, y - playerSize.y);
}
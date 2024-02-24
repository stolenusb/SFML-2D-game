#pragma once

#include <SFML/Graphics.hpp>

class Collider
{
public:
    Collider(sf::RectangleShape &Entity, sf::Sprite &Sprite);
    ~Collider();
    
    void playerMove(double x, double y);
    bool checkCollision(sf::RectangleShape &otherEntity, sf::Vector2f &playerVelocity);

    bool bCollidingWithGround = true;

private:
    sf::RectangleShape &playerEntity;
    sf::Sprite &playerSprite;
};
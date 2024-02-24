#include <collision.h>
#include <iostream>

Collider::Collider(sf::RectangleShape &Entity, sf::Sprite &Sprite) :
    playerEntity(Entity), playerSprite(Sprite)
{
}

Collider::~Collider()
{
}

void Collider::playerMove(double x, double y)
{
    playerEntity.move(x, y);
    playerSprite.move(x, y);
}

bool Collider::checkCollision(sf::RectangleShape &otherEntity, sf::Vector2f &playerVelocity)
{
    sf::Vector2f otherEntityHalfSize = otherEntity.getSize() / 2.0f;
    sf::Vector2f otherEntityPosition = otherEntity.getPosition() + otherEntityHalfSize;
    sf::Vector2f playerEntityHalfSize = playerEntity.getSize() / 2.0f;
    sf::Vector2f playerEntityPosition = playerEntity.getPosition() + playerEntityHalfSize;

    float deltaX = otherEntityPosition.x - playerEntityPosition.x;
    float deltaY = otherEntityPosition.y - playerEntityPosition.y;
    
    float intersectX = abs(deltaX) - (otherEntityHalfSize.x + playerEntityHalfSize.x);
    float intersectY = abs(deltaY) - (otherEntityHalfSize.y + playerEntityHalfSize.y);
    
    if(intersectX < 0.0f && intersectY < 0.0f) {

        if(intersectX > intersectY) {
            if(deltaX > 0.0f)
                playerMove(intersectX, 0.0f);
            else
                playerMove(-intersectX, 0.0f);

            playerVelocity.x = 0.0f;
        } else {
            if(deltaY > 0.0f) {
                playerMove(0.0f, intersectY);
            } else {
                bCollidingWithGround = true;
                std::cout << "colliding with ground" << std::endl;
                playerMove(0.0f, -intersectY);
            }

            playerVelocity.y = 0.0f;
        }

        return true;
    }

    bCollidingWithGround = false;

    return false;
}
#pragma once

#include <SFML\Graphics.hpp>
#include <math.h>
#include "animation.h"

class Projectile
{
public:
    Projectile(sf::RenderWindow &gameWindow, sf::Sprite &playerEntity, sf::Texture &projectileTexture);
    ~Projectile();

    void Set();
    void Move(float projectileSpeed, double deltaTime);
    void Draw() { window.draw(projectileSprite); };

private:
    sf::RenderWindow &window;

    sf::Sprite &playerEntity;
    sf::Sprite projectileSprite;
    sf::Texture &projectileTexture;
    Animation projectileAnim;
    
    sf::Vector2f projectilePos;
    float projectileAngle;
};
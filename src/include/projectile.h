#pragma once

#include <SFML\Graphics.hpp>
#include <math.h>
#include "animation.h"

class Projectile
{
public:
    Projectile(sf::Texture &projectileTexture);
    ~Projectile();

    void Update(float projectileSpeed, double deltaTime);
    void Add(sf::Vector2i windowPos, sf::Vector2f playerPos);
    void Draw(sf::RenderWindow &window);

private:
    sf::Sprite projectileSprite;
    sf::Texture &projectileTexture;

    std::vector<sf::Sprite> projectile;
    std::vector<float> projectileAngle;
    //std::vector<Animation> projectileAnim;
};
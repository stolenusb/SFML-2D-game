#pragma once

#include <SFML\Graphics.hpp>
#include <math.h>
#include "animation.h"
#include "enemy.h"
#include "collision.h"

class Projectile
{
public:
    void Update(float projectileSpeed, double deltaTime);
    void checkCollision(Enemy &enemy);
    void Add(sf::Vector2i windowPos, sf::Vector2f playerPos);
    void Draw(sf::RenderWindow &window);

private:
    struct projectile {
        sf::Sprite sprite;
        sf::RectangleShape entity;
        float angle;
        Animation anim;
    };

    struct projectile added_proj;

    std::vector<struct projectile> proj;
};
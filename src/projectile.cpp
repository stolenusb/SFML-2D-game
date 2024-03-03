#include "projectile.h"

Projectile::Projectile(sf::RenderWindow &gameWindow, sf::RectangleShape &playerEntity, sf::Texture &projectileTexture) : 
    projectileAnim(projectileSprite, 64), playerEntity(playerEntity), projectileTexture(projectileTexture), window(gameWindow)
{
}

Projectile::~Projectile()
{
}

void Projectile::Set()
{
    projectileSprite.setPosition(playerEntity.getPosition());
    projectileAnim.Set(projectileTexture, 9);
    
    projectilePos.x = sf::Mouse::getPosition(window).x - playerEntity.getPosition().x;
    projectilePos.y = sf::Mouse::getPosition(window).y - playerEntity.getPosition().y;
    projectileAngle = atan2(projectilePos.y, projectilePos.x);
}

void Projectile::Move(float projectileSpeed, double deltaTime)
{
    projectileSprite.move(projectileSpeed * cos(projectileAngle) * deltaTime, projectileSpeed * sin(projectileAngle) * deltaTime);
    projectileAnim.Animate();
}
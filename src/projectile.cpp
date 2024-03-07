#include "projectile.h"

Projectile::Projectile(sf::Texture &projectileTexture) : 
    projectileTexture(projectileTexture)
{
}

Projectile::~Projectile()
{
}

void Projectile::Update(float projectileSpeed, double deltaTime)
{
    for(int i = 0; i < projectile.size(); i++) {
        projectile[i].move(projectileSpeed * cos(projectileAngle[i]) * deltaTime, projectileSpeed * sin(projectileAngle[i]) * deltaTime);
        //projectileAnim[i].Animate();
        if(projectile[i].getPosition().x <= 0.f || projectile[i].getPosition().y <= 0.f || projectile[i].getPosition().x >= 1280.f || projectile[i].getPosition().y >= 720.f ) {
            projectile.erase(projectile.begin() + i);
            projectileAngle.erase(projectileAngle.begin() + i);
        }
    }
}

void Projectile::Add(sf::Vector2i windowPos, sf::Vector2f playerPos)
{
    projectileSprite.setPosition(playerPos);
    projectileSprite.setScale(1.5f, 1.5f);
    projectileSprite.setTexture(projectileTexture);
    projectileSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    projectile.push_back(projectileSprite);

    //projectileAnim.push_back(Animation(projectile[projectile.size() - 1], 64));
    //projectileAnim[projectileAnim.size() - 1].Set(projectileTexture, 9);

    sf::Vector2f projectilePos = sf::Vector2f(windowPos.x - playerPos.x, windowPos.y - playerPos.y);
    projectileAngle.push_back(atan2(projectilePos.y, projectilePos.x));
}

void Projectile::Draw(sf::RenderWindow &window)
{
    for(int i = 0; i < projectile.size(); i++)
        window.draw(projectile[i]);
}
#include "animation.h"
#include <iostream>

Animation::Animation(sf::Sprite &playerSprite, unsigned int playerSize) :
    playerSprite(&playerSprite)
{
    this->imageSize = playerSize;
    rect = sf::IntRect(0, 0, playerSize, playerSize);
}

Animation::~Animation()
{
}

void Animation::loadTextures()
{
    if( !playerTextures[PLAYER_IDLE].loadFromFile("..\\assets\\textures\\magician\\idle.png") ||
        !playerTextures[PLAYER_WALK].loadFromFile("..\\assets\\textures\\magician\\walk.png") ||
        !playerTextures[PLAYER_RUN].loadFromFile("..\\assets\\textures\\magician\\run.png") ||
        !playerTextures[PLAYER_JUMP].loadFromFile("..\\assets\\textures\\magician\\jump.png"))

        std::cout << "(-) Failed to load one of the player textures. " << std::endl;
}

void Animation::Set(unsigned int texture, unsigned int imageCount)
{
    Count = imageCount;

    playerSprite->setTexture(playerTextures[texture]);
}

void Animation::Animate()
{
    playerSprite->setOrigin(playerSprite->getLocalBounds().width/2, playerSprite->getLocalBounds().height/2);

    if(lookRight == true)
        playerSprite->setScale(1, 1);
    else
        playerSprite->setScale(-1, 1);
    
    if(clock.getElapsedTime().asSeconds() > 0.18f) {
        if(rect.left == (imageSize * 7)) // Using 7 instead of double Count var, (temporary bug fix for texture disappearing)
            rect.left = 0;
        else
            rect.left += imageSize;
        
        playerSprite->setTextureRect(rect);
        clock.restart();
    }
}
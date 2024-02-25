#include "animation.h"
#include <iostream>

Animation::Animation(sf::Sprite &playerSprite, unsigned int playerSize) :
    playerSprite(playerSprite)
{
    textureRect = sf::IntRect(0, 0, playerSize, playerSize);
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

        std::cout << "(-) Failed to load one of the player textures." << std::endl;
    else
        std::cout << "(+) Loaded player textures." << std::endl;
}

void Animation::Set(unsigned int texture, unsigned int imageCount)
{
    imgCount = imageCount - 1;

    playerSprite.setTexture(playerTextures[texture]);
}

void Animation::Animate()
{
    if(clock.getElapsedTime().asSeconds() > 0.18f) {
        if(currImage >= imgCount)
            currImage = 0;
        else
            currImage++;

        clock.restart();
    }

    if(lookRight == true) {
        textureRect.width = abs(textureRect.width);
        textureRect.left = currImage * textureRect.width;
    } else {
        textureRect.width = -abs(textureRect.width);
        textureRect.left = (currImage + 1) * abs(textureRect.width);
    }
        
    playerSprite.setTextureRect(textureRect);
}
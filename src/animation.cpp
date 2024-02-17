#include "animation.h"

void Animation::Set(sf::Sprite *sprt, int imgCount, sf::Vector2u imgSize)
{
    this->sprite = sprt;
    imageCount = imgCount - 1;
    this->imageSize = imgSize;

    rect = sf::IntRect(0, 0, imageSize.x, imageSize.y);
}

void Animation::Animate()
{
    if(animClock.getElapsedTime().asSeconds() > 0.18f)
    {
        if(rect.left == (imageSize.x * imageCount))
            rect.left = 0;
        else
            rect.left += imageSize.x;
        
        sprite->setTextureRect(rect);
        animClock.restart();
    }
}
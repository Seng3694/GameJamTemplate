#pragma once

#include "AnimatedSprite.hpp"

namespace gjt
{
template <typename AnimationKey>
AnimatedSprite::AnimatedSprite()
: sf::Sprite(), key(), animations(), isAnimating(true)
{
}

template <typename AnimationKey> AnimatedSprite::~AnimatedSprite()
{
}

template <typename AnimationKey>
inline void AnimatedSprite::setAnimationKey(const AnimationKey key)
{
    this->key = key;
}

template <typename AnimationKey>
inline AnimationKey &AnimatedSprite::getAnimationKey()
{
    return this->key;
}

template <typename AnimationKey>
inline std::shared_ptr<Animation> AnimatedSprite::getCurrentAnimation()
{
    return animations[key];
}

template <typename AnimationKey>
inline void AnimatedSprite::setIsAnimating(const bool isAnimating)
{
    this->isAnimating = isAnimating;
}

template <typename AnimationKey>
void AnimatedSprite::addAnimation(
    const AnimationKey &key, std::shared_ptr<Animation> animation)
{
    animations[key] = animation;

    if (animations.size() == 1)
    {
        setTexture(*animation->getTileset()->getTexture());
        setTextureRect(animation->getCurrentFrameTextureRectangle());
    }
}

template <typename AnimationKey> void AnimatedSprite::update(float dt)
{
    if (isAnimating)
    {
        std::shared_ptr<Animation> current = animations.find(key)->second;
        current->update(dt);
        setTexture(*current->getTileset()->getTexture());
        setTextureRect(current->getCurrentFrameTextureRectangle());
    }
}

} // namespace gjt

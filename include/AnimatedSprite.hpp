#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Animation.hpp"
#include <memory>

namespace gjt
{

template<typename AnimationKey>
class AnimatedSprite : public sf::Sprite
{
  public:
    AnimatedSprite();
    virtual ~AnimatedSprite();

    inline AnimationKey &getAnimationKey();
    inline std::shared_ptr<Animation> getCurrentAnimation();

    inline void setAnimationKey(const AnimationKey key);
    inline void setIsAnimating(const bool isAnimating);

    void addAnimation(
        const AnimationKey &key, std::shared_ptr<Animation> animation);
    virtual void update(float dt);

  private:
    AnimationKey key;
    std::unordered_map<AnimationKey, std::shared_ptr<Animation>> animations;
    bool isAnimating;
};

}

#include "AnimatedSprite.inl"

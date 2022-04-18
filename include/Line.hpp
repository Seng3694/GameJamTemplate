#pragma once

#include <SFML/Graphics.hpp>

namespace gjt
{
class Line : public sf::Drawable
{
  public:
    Line();
    Line(const sf::Vector2f &from, const sf::Vector2f &to, const sf::Color &color, const float thickness);

  protected:
    sf::Vertex vertices[4];

    virtual void draw(
        sf::RenderTarget &target, sf::RenderStates states) const override;
};

}

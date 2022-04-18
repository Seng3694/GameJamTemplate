#include "Line.hpp"
#include <CustomMath.hpp>

namespace gjt
{

Line::Line()
{
}

Line::Line(
    const sf::Vector2f &from, const sf::Vector2f &to,
    const sf::Color &color, const float thickness)
{
    sf::Vector2f direction = gjt::normalize(to - from);
    sf::Vector2f perpendicular(-direction.y, direction.x);

    sf::Vector2f offset = (thickness / 2.0f) * perpendicular;

    vertices[0].position = from + offset;
    vertices[1].position = to + offset;
    vertices[2].position = from - offset;
    vertices[3].position = to - offset;

    for (uint32_t i = 0; i < 4; ++i)
        vertices[i].color = color;
}

void Line::draw(
    sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(vertices, 4, sf::TriangleStrip, states);
}

}

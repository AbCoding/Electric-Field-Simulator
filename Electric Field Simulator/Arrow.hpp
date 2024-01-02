#pragma once

#include <SFML/Graphics.hpp>

class Arrow {
public:
    Arrow(float size);
    void updatePosition(float newCenterX, float newCenterY);
    void rotate(float angle);
    void setRotation(float angle);
    void setColor(float strength);
    void draw(sf::RenderWindow& window);

private:
    sf::RectangleShape arrowRect;
    sf::CircleShape ArrowTri;

    sf::Color interpolateColors(const sf::Color& color1, const sf::Color& color2, float t) const;
};

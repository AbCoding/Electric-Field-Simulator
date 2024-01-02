#include "Arrow.hpp"

Arrow::Arrow(float size)
    : arrowRect(sf::Vector2f(size, size * 3)), ArrowTri(size, 3) {
    arrowRect.setFillColor(sf::Color::White);
    arrowRect.setOrigin(size / 2, 0);
    arrowRect.setPosition(0.0f, 0.0f);

    ArrowTri.setFillColor(sf::Color::White);
    ArrowTri.setOrigin(size, size * 1.5);
    ArrowTri.setPosition(0, 0);
}

void Arrow::updatePosition(float newCenterX, float newCenterY) {
    float width = arrowRect.getSize().x;
    float height = arrowRect.getSize().y;

    arrowRect.setPosition(newCenterX, newCenterY);
    ArrowTri.setPosition(newCenterX, newCenterY);
}

void Arrow::rotate(float angle) {
    arrowRect.rotate(angle);
    ArrowTri.rotate(angle);
}

void Arrow::setRotation(float angle) {
    arrowRect.setRotation(angle + 90);
    ArrowTri.setRotation(angle + 90);
}

void Arrow::setColor(float strength) {
    strength = std::min(1.0f, std::max(0.0f, strength));
    sf::Color color = interpolateColors(sf::Color::Black, sf::Color::White, strength);

    arrowRect.setFillColor(color);
    ArrowTri.setFillColor(color);
}

void Arrow::draw(sf::RenderWindow& window) {
    window.draw(arrowRect);
    window.draw(ArrowTri);
}

sf::Color Arrow::interpolateColors(const sf::Color& color1, const sf::Color& color2, float t) const {
    t = std::min(1.0f, std::max(0.0f, t));
    float invT = 1.0f - t;
    return sf::Color(
        static_cast<sf::Uint8>(color1.r * invT + color2.r * t),
        static_cast<sf::Uint8>(color1.g * invT + color2.g * t),
        static_cast<sf::Uint8>(color1.b * invT + color2.b * t),
        static_cast<sf::Uint8>(color1.a * invT + color2.a * t)
    );
}

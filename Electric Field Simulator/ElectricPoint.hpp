#pragma once

#include <SFML/Graphics.hpp>

class ElectricPoint {
public:
    ElectricPoint(sf::Vector2f position, float charge, float radius);

    const sf::CircleShape& getCircleShape() const;
    sf::Vector2f getPosition() const;
    float getCharge() const;
    void setPosition(sf::Vector2f newPosition);
    void setCharge(float newCharge);

private:
    sf::Vector2f position;
    float charge;
    float radius;
    sf::CircleShape circleShape;
};

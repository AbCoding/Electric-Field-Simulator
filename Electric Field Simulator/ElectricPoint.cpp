#include "ElectricPoint.hpp"

ElectricPoint::ElectricPoint(sf::Vector2f position, float charge, float radius)
    : position(position), charge(charge), radius(radius) {
    circleShape.setRadius(radius);
    if (charge < 0) {
        circleShape.setFillColor(sf::Color::Blue);
    }
    else {
        circleShape.setFillColor(sf::Color::Red);
    }
    circleShape.setPosition(position - sf::Vector2f(radius, radius));
}

const sf::CircleShape& ElectricPoint::getCircleShape() const {
    return circleShape;
}

sf::Vector2f ElectricPoint::getPosition() const {
    return position;
}

float ElectricPoint::getCharge() const {
    return charge;
}

void ElectricPoint::setPosition(sf::Vector2f newPosition) {
    position = newPosition;
    circleShape.setPosition(position - sf::Vector2f(radius, radius));
}

void ElectricPoint::setCharge(float newCharge) {
    charge = newCharge;
}

#pragma once
#include <SFML/Graphics.hpp>

class Particle {
public:
    // Constructors
    Particle();  // Default constructor
    Particle(const sf::Vector2f& position, const sf::Vector2f& velocity, const sf::Vector2f& acceleration, float mass, float radius);
    Particle(const sf::Vector2f& position, float mass);
    // Other member functions and variables as needed...
    void UpdatePos(float dt);
    void UpdateVel(float dt);
    void GetAcceleration(sf::Vector2f Force);
    void UpdateParticle(float dt, sf::Vector2f Force);
    float getKE();
    // Getter functions
    const sf::Vector2f& getPosition() const;
    const sf::Vector2f& getVelocity() const;
    const sf::Vector2f& getAcceleration() const;
    
    // Getter function for CircleShape
    const sf::CircleShape& getCircleShape() const;

private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float mass;
    float radius;

    // Add an sf::CircleShape member
    sf::CircleShape circleShape;
};
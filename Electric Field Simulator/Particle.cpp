#include "Particle.hpp"

// Default constructor
Particle::Particle() : position(0.0f, 0.0f), velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f), mass(1.0f), radius(1.0f) {

    // Additional initialization if needed
    circleShape.setRadius(radius);
    circleShape.setPosition(position);
}

// Parameterized constructor
Particle::Particle(const sf::Vector2f& position, const sf::Vector2f& velocity, const sf::Vector2f& acceleration, float mass, float radius)
    : position(position), velocity(velocity), acceleration(acceleration), mass(mass), radius(radius) {
    // Additional initialization if needed
    circleShape.setRadius(radius);
    circleShape.setPosition(position);
}
Particle::Particle(const sf::Vector2f& position, float mass)
    : position(position), velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f), mass(mass), radius(1.0f) {
    // Additional initialization if needed
    circleShape.setRadius(radius);
    circleShape.setPosition(position);
}


// Getter function implementations
const sf::CircleShape& Particle::getCircleShape() const {
    return circleShape;
}

const sf::Vector2f& Particle::getPosition() const {
    return position;
}

const sf::Vector2f& Particle::getVelocity() const {
    return velocity;
}

const sf::Vector2f& Particle::getAcceleration() const {
    return acceleration;
}


// Update position based on current velocity and time step (dt)
void Particle::UpdatePos(float dt) {
    position += velocity * dt;
}

// Update velocity based on current acceleration and time step (dt)
void Particle::UpdateVel(float dt) {
    velocity += acceleration * dt;
}

// Example function to get the acceleration (implementation is missing, please add accordingly)
void Particle::GetAcceleration(sf::Vector2f Force) {
    acceleration = Force / mass;
    // Add your code here...
}

float Particle::getKE() {
    // Calculate kinetic energy without using VectorMath
    float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    return 0.5f * mass * speed * speed;
}
void Particle::UpdateParticle(float dt, sf::Vector2f Force) {
    GetAcceleration(Force);
    UpdateVel(dt);
    UpdatePos(dt);
    circleShape.setPosition(position);
}
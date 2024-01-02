#include <SFML/Graphics.hpp>
#include <cmath>
#include "Particle.hpp"
#include "ElectricPoint.hpp"
#include "Arrow.hpp"
#include "MathHelper.hpp"
#include <iostream>

sf::Vector2f getSingleField(sf::Vector2f location, const ElectricPoint& point) {
    constexpr float K = 1.0f;
    const sf::Vector2f pointPos = point.getPosition();
    const float pointCharge = point.getCharge();

    const sf::Vector2f diff = location - pointPos;
    const float distance = std::hypot(diff.x, diff.y);

    // Check if distance is close to zero to avoid division by zero
    if (distance < 0.0001f) {
        return sf::Vector2f(0.001f, 0.001f);
    }

    const sf::Vector2f direction = diff / distance;
    const float radius = 1.0f / (distance * distance);

    return direction * (K * pointCharge * radius);
}

sf::Vector2f CalcTotalField(sf::Vector2f location, const std::vector<ElectricPoint>& PointChargeArray) {
    sf::Vector2f fieldDir = sf::Vector2f(0.0f, 0.0f);

    for (const ElectricPoint& point : PointChargeArray) {
        fieldDir += getSingleField(location, point);
    }

    return fieldDir;
}

float getAngle(sf::Vector2f normalizedVector) {
    return std::atan2(normalizedVector.y, normalizedVector.x) * 180.0 / 3.1415;
}
void UpdateParticles(std::vector<Particle>& Particles, const std::vector<ElectricPoint>& pointCharges, float dt) {
    for (auto& particle : Particles) {
        

        sf::Vector2f totalField = CalcTotalField(particle.getPosition(), pointCharges);
        totalField *= 100.0f;
        particle.UpdateParticle(dt, totalField);

        
    }
}
void updateArrows(std::vector<std::vector<Arrow>>& arrows, const std::vector<ElectricPoint>& pointCharges, int gridSize, int windowSize, int StrengthScale) {
    const float cellSize = windowSize / static_cast<float>(gridSize);

    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            float x = i * cellSize + cellSize / 2.0f;
            float y = j * cellSize + cellSize / 2.0f;

            sf::Vector2f totalField = CalcTotalField(sf::Vector2f(x, y), pointCharges);
            float strength = std::hypot(totalField.x, totalField.y) * StrengthScale;

            arrows[i][j].setColor(strength);
            arrows[i][j].updatePosition(x, y);
            arrows[i][j].setRotation(getAngle(totalField));
        }
    }
}

int main() {
    float A = 100;
    const int gridSize = 40;
    const int windowSize = 800;
    float dt = .05;
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "SFML Arrow Example");
    std::vector<Particle> Particles;
    std::vector<ElectricPoint> pointCharges;
    std::vector<std::vector<Arrow>> arrows(gridSize, std::vector<Arrow>(gridSize, Arrow(3.0f)));
    
    
    while (window.isOpen()) {
        sf::Event event;
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
                pointCharges.emplace_back(sf::Vector2f(mousePosition.x, mousePosition.y), 100, 10);
                updateArrows(arrows, pointCharges, gridSize, windowSize, A);
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::N) {
                pointCharges.emplace_back(sf::Vector2f(mousePosition.x, mousePosition.y), -100, 10);
                updateArrows(arrows, pointCharges, gridSize, windowSize, A);
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) {
                A = A * 0.5;
                updateArrows(arrows, pointCharges, gridSize, windowSize, A);
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E) {
                A = A * 2;
                updateArrows(arrows, pointCharges, gridSize, windowSize, A);
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                // Right mouse button pressed, add a particle at the mouse position
                Particles.emplace_back(sf::Vector2f(mousePosition.x, mousePosition.y), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), 1.0f, 5.0f);
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                int particleIndex = 0;

                for ( auto& particle : Particles) {
                    float energy = particle.getKE();
                   

                    std::cout << "Particle at index " << particleIndex << " - Energy: " << energy <<  ")" << std::endl;

                    ++particleIndex;
                }
            }
        }

        UpdateParticles(Particles, pointCharges, dt);

        window.clear();

        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                arrows[i][j].draw(window);
            }
        }

        for (const auto& point : pointCharges) {
            window.draw(point.getCircleShape());
        }
            
        for (const auto& particle : Particles) {

            window.draw(particle.getCircleShape());
        }

   
        window.display();
    }

    return 0;
}

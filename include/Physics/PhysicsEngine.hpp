#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

struct Particle
{
    sf::Vector2f position;
    sf::Vector2f previous_position;
    sf::Vector2f acceleration;
    float radius = 5.0f;
    float density = 0.0f;
    float pressure = 0.0f;

    float getSpeedSquared() const
    {
        sf::Vector2f vel = position - previous_position;
        return (vel.x * vel.x + vel.y * vel.y);
    }

    Particle(sf::Vector2f pos)
        : position(pos), previous_position(pos), acceleration(0.f, 0.f) {}
};

class PhysicsEngine
{
public:
    PhysicsEngine(uint32_t width, uint32_t height);
    void update(float dt);
    void addParticle(float x, float y);
    const std::vector<Particle> &getParticles() const { return m_particles; }

private:
    void applyGravity();
    void applyConstraint();
    void solveCollisions();
    void updatePositions(float dt);
    void computeDensity();
    void applyFluidForces();

    std::vector<Particle> m_particles;
    sf::Vector2u m_world_size;
    sf::Vector2f m_gravity = {0.f, 1000.f};

    float m_smoothing_radius = 25.0f;
    float m_target_density = 0.02f;
    float m_pressure_multiplier = 10.0f;

    std::vector<std::vector<int>> m_grid;

    uint32_t m_grid_cols;
    uint32_t m_grid_rows;
    float m_cell_size = m_smoothing_radius;

    int getGridIndex(sf::Vector2f pos) const;
    void updateGrid();
};
#include "../../include/Physics/PhysicsEngine.hpp"
#include <algorithm>
#include <cmath>

PhysicsEngine::PhysicsEngine(uint32_t width, uint32_t height)
    : m_world_size(width, height) {}

void PhysicsEngine::addParticle(float x, float y)
{
    m_particles.emplace_back(sf::Vector2f{x, y});
}

void PhysicsEngine::update(float dt)
{
    applyGravity();
    computeDensity();
    applyFluidForces();

    updatePositions(dt);

    applyConstraint();
    solveCollisions();
}

void PhysicsEngine::applyGravity()
{
    for (auto &p : m_particles)
    {
        p.acceleration += m_gravity;
    }
}

void PhysicsEngine::updatePositions(float dt)
{
    for (auto &p : m_particles)
    {
        sf::Vector2f velocity = p.position - p.previous_position;

        p.previous_position = p.position;

        p.position = p.position + velocity + p.acceleration * (dt * dt);

        p.acceleration = {0.f, 0.f};
    }
}

void PhysicsEngine::applyConstraint()
{
    const float friction = 0.99f;
    const float restitution = 0.8f;

    for (auto &p : m_particles)
    {
        sf::Vector2f velocity = p.position - p.previous_position;

        if (p.position.y > static_cast<float>(m_world_size.y) - p.radius)
        {
            p.position.y = static_cast<float>(m_world_size.y) - p.radius;
            p.previous_position.y = p.position.y + velocity.y * restitution;
            p.previous_position.x += (p.position.x - p.previous_position.x) * (1.0f - friction);
        }

        if (p.position.y < p.radius)
        {
            p.position.y = p.radius;
            p.previous_position.y = p.position.y + velocity.y * restitution;
        }

        if (p.position.x > static_cast<float>(m_world_size.x) - p.radius)
        {
            p.position.x = static_cast<float>(m_world_size.x) - p.radius;
            p.previous_position.x = p.position.x + velocity.x * restitution;
        }

        if (p.position.x < p.radius)
        {
            p.position.x = p.radius;
            p.previous_position.x = p.position.x + velocity.x * restitution;
        }
    }
}

void PhysicsEngine::solveCollisions()
{
    const size_t count = m_particles.size();

    for (size_t i = 0; i < count; ++i)
    {
        for (size_t j = i + 1; j < count; ++j)
        {
            Particle &p1 = m_particles[i];
            Particle &p2 = m_particles[j];

            const sf::Vector2f collision_axis = p1.position - p2.position;
            const float dist_sq = collision_axis.x * collision_axis.x + collision_axis.y * collision_axis.y;
            const float min_dist = p1.radius + p2.radius;

            if (dist_sq < min_dist * min_dist)
            {
                const float dist = std::sqrt(dist_sq);
                const sf::Vector2f n = collision_axis / dist;
                const float delta = min_dist - dist;

                p1.position += 0.5f * delta * n;
                p2.position -= 0.5f * delta * n;
            }
        }
    }
}

void PhysicsEngine::computeDensity()
{
    for (auto &p1 : m_particles)
    {
        p1.density = 0.0f;
        for (auto &p2 : m_particles)
        {
            sf::Vector2f diff = p1.position - p2.position;
            float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
            if (dist < m_smoothing_radius)
            {
                float influence = std::pow(m_smoothing_radius - dist, 2);
                p1.density += influence;
            }
        }
        p1.pressure = (p1.density - m_target_density) * m_pressure_multiplier;
    }
}

void PhysicsEngine::applyFluidForces()
{
    for (auto &p1 : m_particles)
    {
        for (auto &p2 : m_particles)
        {
            if (&p1 == &p2)
                continue;

            sf::Vector2f diff = p1.position - p2.position;
            float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);

            if (dist < m_smoothing_radius && dist > 0.01f)
            {
                sf::Vector2f dir = diff / dist;
                float shared_pressure = (p1.pressure + p2.pressure) / 2.0f;
                float force = shared_pressure * std::pow(m_smoothing_radius - dist, 2);
                p1.acceleration += dir * force / p1.density;
            }
        }
    }
}
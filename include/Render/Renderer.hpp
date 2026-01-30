#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Physics/PhysicsEngine.hpp"

class Renderer
{
public:
    Renderer();

    void render(sf::RenderWindow &window, const std::vector<Particle> &particles);

private:
    sf::VertexArray m_vertices;
};
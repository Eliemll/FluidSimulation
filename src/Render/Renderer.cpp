#include "Render/Renderer.hpp"

Renderer::Renderer()
{
    m_vertices.setPrimitiveType(sf::PrimitiveType::TriangleFan);
}

void Renderer::render(sf::RenderWindow &window, const std::vector<Particle> &particles)
{
    const size_t particle_count = particles.size();

    m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    m_vertices.resize(particle_count * 6);

    for (size_t i = 0; i < particle_count; ++i)
    {
        const auto &p = particles[i];
        const float r = p.radius;
        const size_t idx = i * 6;

        float speed = p.getSpeedSquared();
        float ratio = std::min(speed / 15.0f, 1.0f);
        sf::Color color(
            static_cast<std::uint8_t>(100 + ratio * 155),
            static_cast<std::uint8_t>(150 + ratio * 105),
            255);

        sf::Vector2f tl = p.position + sf::Vector2f(-r, -r);
        sf::Vector2f tr = p.position + sf::Vector2f(r, -r);
        sf::Vector2f bl = p.position + sf::Vector2f(-r, r);
        sf::Vector2f br = p.position + sf::Vector2f(r, r);

        m_vertices[idx + 0] = {tl, color};
        m_vertices[idx + 1] = {tr, color};
        m_vertices[idx + 2] = {bl, color};

        m_vertices[idx + 3] = {tr, color};
        m_vertices[idx + 4] = {br, color};
        m_vertices[idx + 5] = {bl, color};
    }

    window.draw(m_vertices);
}
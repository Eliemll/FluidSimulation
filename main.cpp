#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "include/Physics/PhysicsEngine.hpp"
#include "include/Render/Renderer.hpp"
int main()
{
    const uint32_t window_width = 1000;
    const uint32_t window_height = 800;

    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    sf::RenderWindow window(
        sf::VideoMode({window_width, window_height}),
        "Fluid Simulation - SFML 3",
        sf::State::Windowed,
        settings);
    window.setFramerateLimit(60);

    PhysicsEngine solver(window_width, window_height);
    Renderer renderer;

    sf::Clock clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::Escape)
                {
                    window.close();
                }
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            solver.addParticle(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        }

        float dt = clock.restart().asSeconds();

        if (dt > 0.1f)
            dt = 0.1f;

        const int sub_steps = 8;
        float sub_dt = dt / static_cast<float>(sub_steps);
        for (int i = 0; i < sub_steps; ++i)
        {
            solver.update(sub_dt);
        }

        window.clear(sf::Color(10, 10, 25));

        renderer.render(window, solver.getParticles());

        window.display();
    }

    return 0;
}
#include <SFML/Graphics.hpp>
#include "../include/RectangleSimulation.h"
#include "../include/FluidSimulation.h"
#include "../include/Particle.h"
#include "../include/PressureForce.h"

int main()
{
    // Création de la fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(1400, 1000), "Simulation de fluide");

    // Création du rectangle de simulation
    RectangleSimulation simulationRect(300, 100, 800, 600);

    int nb = 5;
    float radius = 8;
    float SmoothingRadius = 0;
    float Damping = 0.95f;
    float force = 4.5f;
    sf::Vector2f initialPace(30.0f, -22.0f);
    // Création de la simulation d'eau avec un certain nombre de particules
    FluidSimulation fluidSimulation(nb, radius, SmoothingRadius, initialPace);

    while (window.isOpen())
    {
        // Gestion des événements de la fenêtre
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Effacer le contenu de la fenêtre
        window.clear(sf::Color::Black);

        // Dessin du rectangle de simulation
        simulationRect.draw(window);

        // Mise à jour et dessin de la simulation d'eau
        fluidSimulation.update(fluidSimulation, SmoothingRadius, 0.02f, Damping); // Par exemple, avec un pas de temps de 0.1 seconde
        fluidSimulation.draw(window);

        // Afficher la fenêtre
        window.display();
    }

    return 0;
}
// cd src && g++ -o PFTest testB.cpp FluidSimulation.cpp PressureForce.cpp RectangleSimulation.cpp Particle.cpp -I include -lsfml-graphics -lsfml-window -lsfml-system
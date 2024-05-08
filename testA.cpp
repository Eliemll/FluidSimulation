#include <SFML/Graphics.hpp>
#include "../include/RectangleSimulation.h"
#include "../include/FluidSimulation.h"
#include "../include/Particle.h"

int main() 
{
    // Création de la fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(1400, 1000), "Simulation de fluide");

    // Création du rectangle de simulation
    RectangleSimulation simulationRect(300, 100, 800, 600);

    // Création de la simulation d'eau avec un certain nombre de particules
    FluidSimulation fluidSimulation(1000); // Par exemple, 10 particules

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
        fluidSimulation.update(0.03f); // Par exemple, avec un pas de temps de 0.1 seconde
        fluidSimulation.draw(window);

        // Afficher la fenêtre
        window.display();
    }

    return 0;
}
// cd src && g++ -o test testA.cpp RectangleSimulation.cpp FluidSimulation.cpp Particle.cpp -I include -lsfml-graphics -lsfml-window -lsfml-system
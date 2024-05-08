// Simulation.h

#ifndef FLUID_SIMULATION_H
#define FLUID_SIMULATION_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "../include/Particle.h"
#include "../include/PressureForce.h"


class FluidSimulation
{
private:
    std::vector<Particle> m_particles; // Vecteur de particules
    sf::FloatRect confinementRect;
    std::vector<sf::Vector2f *> positions; // Tableau de pointeurs pour stocker les positions des particules

public:
    FluidSimulation(int numParticles, float radius, float SmoothingRadius, const sf::Vector2f &initialVelocity); // Constructeur

    // Méthode pour mettre à jour la simulation de l'eau
    void update(FluidSimulation fluidSimulation, float SmoothingRadius, float dt, float Damping);

    // Ajout du rectangle de confinement comme membre pour le problème de collisions
    // void setConfinementRect(const sf::RectangleShape &rect);

    // Getter listeParticules
    std::vector<Particle> getParticles() const;

    // Méthode pour dessiner la simulation de l'eau
    void draw(sf::RenderWindow &window) const;

    // Accesseurs
    float getRectLeft() const;
    float getRectRight() const;
    float getRectTop() const;
    float getRectBottom() const;
    const std::vector<sf::Vector2f *> &getPositions() const
    {
        return positions;
    }
};
#endif
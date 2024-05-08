// FluidSimulation.cpp

#include "../include/FluidSimulation.h"
#include "../include/Particle.h"
#include "../include/RectangleSimulation.h"

// Déclaration du constructeur
FluidSimulation::FluidSimulation(int numParticles, float radius, float SmoothingRadius, const sf::Vector2f &initialVelocity)
{
    // Initialisation des particules d'eau avec des positions aléatoires
    for (int i = 0; i < numParticles; ++i)
    {
        float x = static_cast<float>(rand() % 790) + 306;  // Valeur de x aléatoire dans une fenêtre de 800x600
        float y = static_cast<float>(rand() % 590) + 106;  // Valeur de y aléatoire dans une fenêtre de 800x600
        m_particles.push_back(Particle(x, y, radius, 1.0f, initialVelocity)); // Création de la particule avec une taille de rayon de 5.0

        // Créez un nouveau sf::Vector2f et stockez son pointeur dans positions
        sf::Vector2f *newPos = new sf::Vector2f(x, y);
        positions.push_back(newPos);
    }
}

void FluidSimulation::update(float dt, /*const sf::RectangleShape &rect,*/ float Damping, float force)
{
    // setConfinementRect(rect);
    for (auto &particle : m_particles)
    {
        particle.updatePosition(dt, Damping, force);
    }
}
/*
void FluidSimulation::setConfinementRect(const sf::RectangleShape &rect)
{
    // Obtenez la position et la taille de rect
    sf::Vector2f position = rect.getPosition();
    sf::Vector2f size = rect.getSize();

    // Créer un sf::FloatRect à partir de ces informations
    confinementRect.left = position.x;
    confinementRect.top = position.y;
    confinementRect.width = size.x;
    confinementRect.height = size.y;
}
*/
void FluidSimulation::draw(sf::RenderWindow &window) const
{
    // Dessiner chaque particule d'eau dans la fenêtre
    for (const auto &particle : m_particles)
    {
        particle.draw(window);
    }
}

// Accesseurs
std::vector<Particle> FluidSimulation::getParticles() const {
    return m_particles;
}

float FluidSimulation::getRectLeft() const 
{
    return confinementRect.left;
}

float FluidSimulation::getRectRight() const
{
    return confinementRect.left + confinementRect.width;
}

float FluidSimulation::getRectTop() const
{
    return confinementRect.top;
}

float FluidSimulation::getRectBottom() const
{
    return confinementRect.top + confinementRect.height;
}
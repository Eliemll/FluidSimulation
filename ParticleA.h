// Particle.h

#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp> // Inclure les en-têtes nécessaires

class Particle
{
public:
    // Constructeur avec paramètres
    Particle(float x, float y, float radius, float mass, const sf::Vector2f &initialVelocity);

    // Mettre à jour la position, vitesse
    void updatePosition(float dt, float Damping, float force);

    // Méthode pour dessiner la particule
    void draw(sf::RenderWindow &window) const;

    /*   Accesseurs   */
    // shape
    sf::CircleShape getShape() const;

    // Position
    void setPosition(const sf::Vector2f &position);
    sf::Vector2f getPosition() const;

    // Vitesse
    void setVelocity(const sf::Vector2f &velocity);
    sf::Vector2f getVelocity() const;

    // Mass
    float getMass() const;

    // Radius
    float getRadius() const;

    // Résout le problème de collision
    void resolveCollisions(float Damping);

private:
    sf::CircleShape shape;
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    float m_mass;
    float radius;
};

#endif
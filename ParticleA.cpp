// Particle.cpp

#include "../include/Particle.h"
#include <SFML/Graphics.hpp>

// Définition du constructeur
Particle::Particle(float x, float y, float radius, float mass, const sf::Vector2f &initialVelocity)
{
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Cyan);
    shape.setPosition(x, y);
    m_velocity = initialVelocity;
}
/*
// Méthode d'actualisation de la position
void Particle::updatePosition(float dt, const sf::FloatRect &confinementRect)
{
    // Instruction pour calculer calculer et appliquer les forces de pression

    // Résoudre les collisions avec les bords du rectangle de confinement
    resolveCollisions(confinementRect);
    // Mettre à jour la position en fonction de la vitesse et du temps écoulé (dt)
    sf::Vector2f currentPosition = shape.getPosition() + m_velocity * dt;

    // Définir la nouvelle position de la particule
    shape.setPosition(currentPosition);
}
*/
// Méthode d'actualisation de la position (Gravity)
void Particle::updatePosition(float dt, float Damping, float force)
{
    sf::Vector2f vector(0.0f, 1.0f);
    sf::Vector2f gravity = vector * force;

    // Ajouter le vecteur de gravité à la vitesse
    m_velocity += gravity * dt;

    // Résoudre les collisions avec les bords du rectangle de confinement
    resolveCollisions(Damping);
    // Mettre à jour la position en fonction de la vitesse et du temps écoulé (dt)
    sf::Vector2f currentPosition = shape.getPosition() + m_velocity * dt;

    // Définir la nouvelle position de la particule
    shape.setPosition(currentPosition);
}

void Particle::resolveCollisions(float Damping)
{
    sf::Vector2f position = shape.getPosition();
    sf::Vector2f velocity = m_velocity;
    float radius = shape.getRadius();

    // Vérifier les collisions avec les bords du rectangle de confinement
    if (position.x - radius < 295 && velocity.x < 0)
    {
        // Collision avec le bord gauche, inverser la vitesse horizontale
        velocity.x *= -Damping;
        velocity.y *= 0.99;
    }
    else if (position.x + radius > 1100 && velocity.x > 0)
    {
        // Collision avec le bord droit, inverser la vitesse horizontale
        velocity.x *= -Damping;
        velocity.y *= 0.99;
    }

    if (position.y - radius < 100 && velocity.y < 0)
    {
        // Collision avec le bord supérieur, inverser la vitesse verticale
        velocity.y *= -Damping;
        velocity.x *= 0.99;
    }
    else if (position.y + radius > 700 && velocity.y > 0)
    {
        // Collision avec le bord inférieur, inverser la vitesse verticale
        velocity.y *= -Damping;
        velocity.x *= 0.99;
    }

    // Appliquer les nouvelles vitesses après la collision
    m_velocity = velocity;
}

void Particle::draw(sf::RenderWindow &window) const
{
    window.draw(shape);
}

/*   Accesseurs   */ 
// shape
sf::CircleShape Particle::getShape() const {
    return this->shape;
}
// Position
sf::Vector2f Particle::getPosition() const 
{
    return this->m_position;
}

void Particle::setPosition(const sf::Vector2f &position) {
    this->shape.setPosition(position);
}

// Velocity
void Particle::setVelocity(const sf::Vector2f &velocity) {
    this->m_velocity = velocity;
}

sf::Vector2f Particle::getVelocity() const {
    return this->m_velocity;
}

// Mass
float Particle::getMass() const
{
    return this->m_mass;
}

// Radius
float Particle::getRadius() const {
    return this->radius;
}


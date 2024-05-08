#include "../include/PressureForce.h"
#include <SFML/System/Vector2.hpp>
#include <cmath>


/*   Pressure Methods   */
float PressureForce::SmoothingKernel(float dst, float radius)
{
    float volume = PI * std::pow(radius, 8) / 4;
    float value = std::max(0.0f, radius * radius - dst * dst);
    return value * value * value / volume;
}

float PressureForce::SmoothingKernelDerivative(float dst, float radius)
{
    if (dst >= radius)
        return 0;
    float f = radius * radius - dst * dst;
    float scale = -24 / (PI * std::pow(radius, 8));
    return scale * dst * f * f;
}

float PressureForce::CalculateDensity(FluidSimulation fluidSimulation, sf::Vector2f samplePoint, float SmoothingRadius)
{
    float density = 0;
    const float mass = 1;
    std::vector<Particle> particles = fluidSimulation.getParticles();

    // Loop over all particles
    for (const Particle &particle : particles)
    {
        sf::Vector2f position = particle.getPosition();
        sf::Vector2f vector = position - samplePoint;
        float dst = sqrt(vector.x * vector.x + vector.y * vector.y);
        float influence = SmoothingKernel(SmoothingRadius, dst);
        density += mass * influence;
    }

    return density;
}
/*
sf::Vector2f PressureForce::CalculateGradient(const FluidSimulation fluidSimulation, const sf::Vector2f samplePoint, float SmoothingRadius)
{
    sf::Vector2f propertyGradient(0.0f, 0.0f);

    const std::vector<sf::Vector2f *> &positions = fluidSimulation.getPositions();

    for (const auto &positionPtr : positions)
    {
        sf::Vector2f position = *positionPtr;
        sf::Vector2f vdst = *positionPtr - samplePoint;
        float dst = std::sqrt(vdst.x * vdst.x + vdst.y * vdst.y); // Norme de vdst
        sf::Vector2f dir = vdst / dst;
        float slope = SmoothingKernelDerivative(dst, SmoothingRadius);
        float density = densities[position]; // Utiliser *positionPtr pour accéder à la position
        float influence = SmoothingKernel(dst, SmoothingRadius);
        sf::Vector2f gradient = slope * dir * density * influence;
        propertyGradient += gradient;
    }

    return propertyGradient;
}
*/
sf::Vector2f PressureForce::CalculateGradient(FluidSimulation fluidSimulation, const sf::Vector2f samplePoint, float SmoothingRadius)
{
    sf::Vector2f propertyGradient(0.0f, 0.0f);

    const std::vector<sf::Vector2f *> &positions = fluidSimulation.getPositions();

    for (const auto &positionPtr : positions)
    {
        sf::Vector2f vdst = *positionPtr - samplePoint;
        float dst = std::sqrt(vdst.x * vdst.x + vdst.y * vdst.y); // Norme de vdst

        if (dst != 0)
        {
            sf::Vector2f dir = vdst / dst;
            float slope = SmoothingKernelDerivative(dst, SmoothingRadius);
            float density = CalculateDensity(fluidSimulation, samplePoint, SmoothingRadius);
            propertyGradient += -dir * slope / density;
        }
    }

    return propertyGradient;
}

/*
void PressureForce::UpdateDensities(FluidSimulation fluidSimulation, sf::Vector2f position, float SmoothingRadius, int numParticles)
{
//#pragma omp parallel for
    const std::vector<sf::Vector2f *> &positions = fluidSimulation.getPositions();
    float densities[] = 

    for (int i = 0; i < numParticles; ++i)
    {
        sf::Vector2f position = *positions[i];
        densities[i] = CalculateDensity(fluidSimulation, position, SmoothingRadius, numParticles);
    }
}*/
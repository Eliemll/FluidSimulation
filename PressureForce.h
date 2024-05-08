#ifndef PRESSUREFORCE_h
#define PRESSUREFORCE_h

#include "SFML/Graphics.hpp"
#include "../include/FluidSimulation.h"
#include "../include/Particle.h"
#include <cmath>
// #include <omp.h>

// Valeur de PI
static const double PI = std::acos(-1.0);

class PressureForce {
public:
    /*   Pressure Methods   */
    static float SmoothingKernel(float dst, float radius);
    static float SmoothingKernelDerivative(float dst, float radius);
    static float CalculateDensity(FluidSimulation fluidSimulation, sf::Vector2f samplePoint, float SmoothingRadius);
    static sf::Vector2f CalculateGradient(FluidSimulation fluidSimulation, sf::Vector2f samplePoint, float SmoothingRadius);
    // void UpdateDensities(FluidSimulation fluidSimulation, sf::Vector2f position, float SmoothingRadius, int numParticles);
};

#endif
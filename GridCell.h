// GridCell.h

#ifndef GRIDCELL_H
#define GRIDCELL_H

#include <vector>
#include "Particle.h"

class GridCell
{
private:
    // Liste des particule se trouvant dans la cellule
    std::vector<Particle *> particles;

public:
    // Constructeur/Destructeur
    GridCell(){}
    ~GridCell(){}

    // Méthode d'ajout d'une particule
    void addParticle(Particle *particle) 
    {
        particles.push_back(particle);
    }

    // Méthode de supression d'une particule
    void removeParticle(Particle *particle) 
    {
        // Recherchez la particule dans le vecteur
        auto it = std::find(particles.begin(), particles.end(), particle);
        // Si la particule est trouvée, on l'efface.
        if (it != particles.end()) 
        {
            particles.erase(it);
        }
    }
};
#endif

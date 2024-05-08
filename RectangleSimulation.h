#ifndef RECTANGLESIMULATION_H
#define RECTANGLESIMULATION_H

#include <SFML/Graphics.hpp>

class RectangleSimulation {
private:
    sf::RectangleShape m_rectangle;
    float x, y, width, height;

public:
    // Constructeur
    RectangleSimulation(float x, float y, float width, float height);

    // Dessiner le rectangle
    void draw(sf::RenderWindow &window) const;

    /*   Accesseurs   */
    float getLeft() const;
    float getRight() const;
    float getTop() const;
    float getBottom() const;
    sf::RectangleShape getRectangle() const;
};
#endif
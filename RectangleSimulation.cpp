#include "../include/RectangleSimulation.h"

RectangleSimulation::RectangleSimulation(float x, float y, float width, float height)
{
    m_rectangle.setSize(sf::Vector2f(width, height));
    m_rectangle.setPosition(x, y);
    m_rectangle.setFillColor(sf::Color::Transparent);
    m_rectangle.setOutlineThickness(2);
    m_rectangle.setOutlineColor(sf::Color::White);
}

void RectangleSimulation::draw(sf::RenderWindow &window) const
{
    window.draw(m_rectangle);
}

float RectangleSimulation::getLeft() const {
    return this->x;
}

float RectangleSimulation::getRight() const 
{
    return this->x + this->width;
}

float RectangleSimulation::getTop() const
{
    return this->y;
}

float RectangleSimulation::getBottom() const
{
    return this->y + this->height;
}

sf::RectangleShape RectangleSimulation::getRectangle() const{
    return this->m_rectangle;
}
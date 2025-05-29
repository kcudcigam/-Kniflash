#pragma once
#include <cmath>
#include "SFML/Graphics.hpp"

class EllipseShape : public sf :: Shape {
public:
    explicit EllipseShape(sf::Vector2f radius = {0, 0}) : m_radius(radius) {
        update();
    }
    void setRadius(sf::Vector2f radius) {
        m_radius = radius;
        update();
    }
    sf::Vector2f getRadius() const {
        return m_radius;
    }
    std::size_t getPointCount() const override {
        return 30; // fixed, but could be an attribute of the class if needed
    }
    sf :: Vector2f getPoint(std :: size_t index) const override {
        static constexpr float pi = 3.141592654f;
        float angle = index * 2 * pi / getPointCount() - pi / 2;
        float x     = std :: cos(angle) * m_radius.x;
        float y     = std :: sin(angle) * m_radius.y;
        return m_radius + sf::Vector2f(x, y);
    }
private:
    sf :: Vector2f m_radius;
};
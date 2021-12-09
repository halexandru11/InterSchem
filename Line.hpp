#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Node.hpp"

class Line {
public:
    Line(const Node& parent, const Node& child) {
        m_parent = &parent;
        m_child = &child;
        m_coordA = m_parent->coordOut;
        m_coordB = m_child->coordIn;
    }

    std::vector<sf::Vertex> getLine() {
        if(m_coordA == sf::Vector2f{-1, -1} or m_coordB == sf::Vector2f{-1, -1}) {
            throw std::invalid_argument("You did not set the coordinates for this line");
        }

        setLine();
        return m_line;
    }

private:
    void setLine() {
        m_coordA = m_parent->coordOut;
        m_coordB = m_child->coordIn;
        float midY = (m_coordA.y + m_coordB.y) / 2;

        m_line.clear();
        m_line.push_back(sf::Vertex(sf::Vector2f{m_coordA.x, m_coordA.y}));
        m_line.push_back(sf::Vertex(sf::Vector2f{m_coordA.x, midY}));
        m_line.push_back(sf::Vertex(sf::Vector2f{m_coordA.x, midY}));
        m_line.push_back(sf::Vertex(sf::Vector2f{m_coordB.x, midY}));
        m_line.push_back(sf::Vertex(sf::Vector2f{m_coordB.x, midY}));
        m_line.push_back(sf::Vertex(sf::Vector2f{m_coordB.x, m_coordB.y}));
    }

private:
    sf::Vector2f m_coordA = sf::Vector2f{-1, -1};
    sf::Vector2f m_coordB = sf::Vector2f{-1, -1};
    std::vector<sf::Vertex> m_line;
    const Node* m_parent;
    const Node* m_child;
};

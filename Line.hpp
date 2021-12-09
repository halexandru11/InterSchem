#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Node.hpp"

struct Line {
public:
    Line(sf::Vector2f coordA, sf::Vector2f coordB) {
        m_coordA = coordA;
        m_coordB = coordB;
    }

//    Line(Node& parent, Node& child) {
//        m_parent = parent;
//        m_child = child;
//    }

    void update(sf::Vector2f coordA, sf::Vector2f coordB) {
        m_coordA = coordA;
        m_coordB = coordB;
        m_line = setLine();
    }

//    void update() {
//        m_coordA = m_parent.coordOut;
//        m_coordB = m_child.coordIn;
//        m_line = setLine();
//    }

    std::vector<sf::Vertex> getLine() {
        if(m_coordA == sf::Vector2f{-1, -1} or m_coordB == sf::Vector2f{-1, -1}) {
            throw std::invalid_argument("You did not set the coordinates for this line");
        }

        if(!m_lineAssigned) {
            m_lineAssigned = true;
            m_line = setLine();
        }
        return m_line;
    }

private:
     std::vector<sf::Vertex> setLine() {
        std::vector<sf::Vertex> vertices;
        vertices.clear();
        float midY = (m_coordA.y + m_coordB.y) / 2;
        vertices.push_back(sf::Vertex(sf::Vector2f{m_coordA.x, m_coordA.y}));
        vertices.push_back(sf::Vertex(sf::Vector2f{m_coordA.x, midY}));
        vertices.push_back(sf::Vertex(sf::Vector2f{m_coordA.x, midY}));
        vertices.push_back(sf::Vertex(sf::Vector2f{m_coordB.x, midY}));
        vertices.push_back(sf::Vertex(sf::Vector2f{m_coordB.x, midY}));
        vertices.push_back(sf::Vertex(sf::Vector2f{m_coordB.x, m_coordB.y}));

        return vertices;
     }

private:
    sf::Vector2f m_coordA = sf::Vector2f{-1, -1};
    sf::Vector2f m_coordB = sf::Vector2f{-1, -1};
    std::vector<sf::Vertex> m_line;
    bool m_lineAssigned = false;
//    Node& m_parent = NULL;
//    Node& m_child = NULL;
};

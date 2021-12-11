#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Node.hpp"

class Line {
public:
    Line(Node& parent, Node& child, Constants::CoordType parentCoordType, Constants::CoordType childCoordType) {
        m_parent = &parent;
        m_child = &child;
        m_parentCoordType = parentCoordType;
        m_childCoordType = childCoordType;
        m_coordParent = m_parent->getNodeCoordonates(m_parentCoordType);
        m_coordChild = m_child->getNodeCoordonates(m_childCoordType);
        connected = true;
    }

    Line(Node& parent, sf::Vector2f mousePos, Constants::CoordType parentCoordType) {
        m_parent = &parent;
        m_parentCoordType = parentCoordType;
        m_coordParent = m_parent->getNodeCoordonates(m_parentCoordType);
        m_coordChild = mousePos;
        connected = false;
    }

    std::vector<sf::Vertex> getLine() {
//        if(m_coordParent == sf::Vector2f{-1, -1} or m_coordChild == sf::Vector2f{-1, -1}) {
//            throw std::invalid_argument("You did not set the coordinates for this line");
//        }

        setLine();
        return m_line;
    }

private:
    void setLine(sf::Vector2f mousePos = sf::Vector2f{0, 0}) {
        m_coordParent = m_parent->getNodeCoordonates(m_parentCoordType);
        m_coordChild = (connected ? m_child->getNodeCoordonates(m_childCoordType) : mousePos);
        float midY = (m_coordParent.y + m_coordChild.y) / 2;

        m_line.clear();
        m_line.push_back(sf::Vertex(sf::Vector2f{m_coordParent.x, m_coordParent.y}));
        m_line.push_back(sf::Vertex(sf::Vector2f{m_coordParent.x, midY}));
        m_line.push_back(sf::Vertex(sf::Vector2f{m_coordParent.x, midY}));
        m_line.push_back(sf::Vertex(sf::Vector2f{m_coordChild.x, midY}));
        m_line.push_back(sf::Vertex(sf::Vector2f{m_coordChild.x, midY}));
        m_line.push_back(sf::Vertex(sf::Vector2f{m_coordChild.x, m_coordChild.y}));
    }

private:
    sf::Vector2f m_coordParent = sf::Vector2f{-1, -1};
    sf::Vector2f m_coordChild = sf::Vector2f{-1, -1};
    std::vector<sf::Vertex> m_line;
    Constants::CoordType m_parentCoordType;
    Constants::CoordType m_childCoordType;
    Node* m_parent;
    Node* m_child;
    bool connected = false;
};

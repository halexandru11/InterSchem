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
        m_connected = true;
    }

    Line(Node*& parent, Constants::CoordType parentCoordType, sf::RenderWindow& window) {
        m_parent = *&parent;
        m_parentCoordType = parentCoordType;
        m_coordParent = m_parent->getNodeCoordonates(m_parentCoordType);
        sf::Vector2f mousePos = sf::Vector2f{sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y};
        m_coordChild = mousePos;
        m_connected = false;
    }

    std::vector<sf::Vertex> getLine(sf::RenderWindow& window) {
        setLine(window);
        return m_line;
    }

    void connectToNode(Node*& node, Constants::CoordType nodeCoordType) {
        m_connected = true;
        m_child = *&node;
        m_childCoordType = nodeCoordType;
        switch(m_parentCoordType) {
        case Constants::CoordOut:
            m_parent->urm = m_child;
            break;
        case Constants::CoordOutTrue:
            m_parent->urmTrue = m_child;
            break;
        case Constants::CoordOutFalse:
            m_parent->urmFalse = m_child;
            break;
        }
    }

    void print() {
        if(m_connected) {
            std::cout << (m_parent == NULL ? "no " : "   ") << "parent | ";
            std::cout << (m_child == NULL ? "no " : "   ") << "child\n";
        }
//        std::cout << m_parent->getNodeCoordonates(m_parentCoordType).x << " " << m_parent->getNodeCoordonates(m_parentCoordType).y << "; ";
//        std::cout << m_child->getNodeCoordonates(m_childCoordType).x << " " << m_child->getNodeCoordonates(m_childCoordType).y << "\n";
    }

    Node* getParent() {
        return m_parent;
    }

    Node* getChild() {
        return m_child;
    }

private:
    void setLine(sf::RenderWindow& window) {
        if(m_connected and (m_child == NULL or m_parent == NULL)) {
            std::cout << "I am missing a node\n";
        }
        sf::Vector2f mousePos = sf::Vector2f{sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y};
        m_coordParent = m_parent->getNodeCoordonates(m_parentCoordType);
        m_coordChild = (m_connected ? m_child->getNodeCoordonates(m_childCoordType) : mousePos);
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
    Node* m_parent = NULL;
    Node* m_child = NULL;
    bool m_connected = false;
};

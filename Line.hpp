#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Node.hpp"

class Line {
public:
    Line(Node& parent, Node& child, Constants::CoordType parentCoordType, Node* childAdress) {
        m_parent = &parent;
        m_child = &child;
        m_parentCoordType = parentCoordType;
        m_coordParent = m_parent->getNodeCoordonates(m_parentCoordType);
        connectToNode(childAdress);
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
        sf::Vector2f mousePos = sf::Vector2f{sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y};
        m_coordChild = (m_connected ? m_child->getNodeCoordonates(Constants::CoordIn) : mousePos);
        m_coordParent = m_parent->getNodeCoordonates(m_parentCoordType);
        setLine();
        return m_line;
    }

    void connectToNode(Node*& node) {
        m_connected = true;
        m_child = *&node;
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
        default:
            break;
        }
    }

    void updateLineColor() {
        if(m_connected == false) {
            throw std::invalid_argument("No line to update");
        }
        m_coordChild = m_child->getNodeCoordonates(Constants::CoordIn);
        setLine();
        m_accentColorPosition += 2;
        if(m_accentColorPosition >= int(m_line.size())) {
            m_accentColorPosition = 0;
        }
    }

    Node* getParent() {
        return m_parent;
    }

    Node* getChild() {
        return m_child;
    }

    size_t getLineSize() {
        return m_line.size();
    }

private:
    void setLineColor() {
        for(size_t index = 0; index < m_line.size(); ++index) {
            m_line[index].color = m_mainColor;
        }
        if(m_accentColorPosition < int(m_line.size())) {
            m_line[m_accentColorPosition].color = m_accentColor;
        }
    }

    void setLine() {
        if(m_connected and (m_child == NULL or m_parent == NULL)) {
            std::cout << "I am missing a node\n";
        }

        m_line.clear();
        if(m_coordChild.y > m_coordParent.y-1) {
            if(fabs(m_coordChild.x - m_coordParent.x) < 1) {
                straightLine();
            }
            else if(fabs(m_coordChild.x - m_coordParent.x) < 5) {
                almostStraightLine();
                if(m_accentColorPosition == 5) {
                    m_accentColorPosition += 2;
                }
            }
            else {
                cabLine();
            }
        }
        else {
            detourCabLine();
        }
        setLineColor();
    }

    void straightLine() {
        float deltaY = (m_coordChild.y - m_coordParent.y) * 0.33f;
        for(int mul = 0; mul < 3; ++mul) {
            m_line.push_back(sf::Vertex(sf::Vector2f(m_coordParent.x, m_coordParent.y + mul*deltaY)));
            m_line.push_back(sf::Vertex(sf::Vector2f(m_coordParent.x, m_coordParent.y + (mul+1)*deltaY)));
        }
        m_line.back().position = m_coordChild;
    }

    void almostStraightLine() {
        float deltaY = (m_coordChild.y - m_coordParent.y) * 0.25f;
        for(int mul = 0; mul < 2; ++mul) {
            m_line.push_back(sf::Vertex(sf::Vector2f(m_coordParent.x, m_coordParent.y + mul*deltaY)));
            m_line.push_back(sf::Vertex(sf::Vector2f(m_coordParent.x, m_coordParent.y + (mul+1)*deltaY)));
        }
        m_line.push_back(sf::Vertex(sf::Vector2f(m_coordParent.x, m_coordParent.y + 2*deltaY)));
        m_line.push_back(sf::Vertex(sf::Vector2f(m_coordChild.x,  m_coordParent.y  + 2*deltaY)));
        for(int mul = 2; mul < 4; ++mul) {
            m_line.push_back(sf::Vertex(sf::Vector2f(m_coordChild.x, m_coordParent.y + mul*deltaY)));
            m_line.push_back(sf::Vertex(sf::Vector2f(m_coordChild.x, m_coordParent.y + (mul+1)*deltaY)));
        }
        m_line.back().position = m_coordChild;
    }

    void cabLine() {
        float midY = (m_coordParent.y + m_coordChild.y) * 0.5f;

        m_line.push_back(sf::Vertex(sf::Vector2f{m_coordParent.x, m_coordParent.y}));
        m_line.push_back(sf::Vertex(sf::Vector2f{m_coordParent.x, midY}));

        m_line.push_back(sf::Vertex(sf::Vector2f{m_coordParent.x, midY}));
        m_line.push_back(sf::Vertex(sf::Vector2f{m_coordChild.x,  midY}));

        m_line.push_back(sf::Vertex(sf::Vector2f{m_coordChild.x,  midY}));
        m_line.push_back(sf::Vertex(sf::Vector2f{m_coordChild.x,  m_coordChild.y}));
    }

    void detourCabLine() {
        float childMargin = (m_child ? 10 : 0);
        float parentMargin = 10;
        float parentWidth  = m_parent->width/2  + 10;
        float parentHeight = m_parent->height;
        float childWidth  = (m_child ? m_child->width  : 0) / 2 + childMargin;
        float childHeight = (m_child ? m_child->height : 0) / 2 + 2*childMargin;
        if(m_coordParent.x > m_coordChild.x) {
            parentWidth *= -1;
        }
        else {
            childWidth *= -1;
        }

//            +---------------+
//            |
//            |
//            |
//            |       |
//            +--------+

        float coordLeft   = std::min(m_coordParent.x - parentWidth, m_coordChild.x - childWidth);
        float coordTop    = std::min(m_coordParent.y - parentHeight, m_coordChild.y);
        float coordBottom = std::max(m_coordParent.y, m_coordChild.y + childHeight);

        m_line.push_back(sf::Vertex(sf::Vector2f(m_coordParent.x, m_coordParent.y)));
        m_line.push_back(sf::Vertex(sf::Vector2f(m_coordParent.x, coordBottom + parentMargin)));

        m_line.push_back(sf::Vertex(sf::Vector2f(m_coordParent.x,       coordBottom + parentMargin)));
        m_line.push_back(sf::Vertex(sf::Vector2f(coordLeft-childMargin, coordBottom + parentMargin)));

        m_line.push_back(sf::Vertex(sf::Vector2f(coordLeft-childMargin, coordBottom + parentMargin)));
        m_line.push_back(sf::Vertex(sf::Vector2f(coordLeft-childMargin, coordTop - childMargin)));

        if(m_child != NULL) {
            m_line.push_back(sf::Vertex(sf::Vector2f(coordLeft-childMargin, coordTop - childMargin)));
            m_line.push_back(sf::Vertex(sf::Vector2f(m_coordChild.x,        coordTop - childMargin)));

            m_line.push_back(sf::Vertex(sf::Vector2f(m_coordChild.x, coordTop - childMargin)));
            m_line.push_back(sf::Vertex(sf::Vector2f(m_coordChild.x, m_coordChild.y)));
        }
    }

private:
    sf::Vector2f m_coordParent = sf::Vector2f(-1, -1);
    sf::Vector2f m_coordChild  = sf::Vector2f(-1, -1);
    std::vector<sf::Vertex> m_line;
    Constants::CoordType m_parentCoordType;
    Node* m_parent = NULL;
    Node* m_child = NULL;
    bool m_connected = false;
    sf::Color m_mainColor   = sf::Color( 33,  33,  33);
    sf::Color m_accentColor = sf::Color(233, 233, 233);
    int m_accentColorPosition = -1;
};

std::vector<Line> lines{};

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
        m_triangle.setOrigin(m_triangle.getRadius()-0.5f, m_triangle.getRadius()-0.5f);
        m_triangle.setRotation(180);
        m_triangle.setFillColor(sf::Color::Black);
    }

    Line(Node*& parent, Constants::CoordType parentCoordType, sf::RenderWindow& window) {
        m_parent = *&parent;
        m_parentCoordType = parentCoordType;
        m_coordParent = m_parent->getNodeCoordonates(m_parentCoordType);
        sf::Vector2f mousePos = sf::Vector2f{sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y};
        m_coordChild = mousePos;
        m_connected = false;
        m_triangle.setOrigin(m_triangle.getRadius()-0.5f, m_triangle.getRadius()-0.5f);
        m_triangle.setRotation(180);
        m_triangle.setFillColor(sf::Color::Black);
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

    void setErrorLineColor() {
        m_mainColor = sf::Color(255, 100, 0);
        m_accentColor = sf::Color(255, 100, 0);
        m_triangle.setFillColor(sf::Color(255, 100, 0));
    }

    void resetLineColor() {
        m_mainColor   = sf::Color( 33,  33,  33);
        m_accentColor = sf::Color(233, 233, 233);
        m_triangle.setFillColor(sf::Color::Black);
    }

    void draw(sf::RenderWindow& window) {
        getLine(window);
        window.draw(&m_line[0], m_line.size(), Lines);
        for(size_t index = 0; index < m_trianglePositions.size(); ++index) {
            m_triangle.setPosition(m_trianglePositions[index]);
            m_triangle.setRotation(m_triangleRotations[index]);
            if(m_mainColor != sf::Color(255, 100, 0)) {
                if(index == m_triangleAccentColorPosition) {
                    m_triangle.setFillColor(sf::Color(127, 127, 127));
                }
                else {
                    m_triangle.setFillColor(sf::Color::Black);
                }
            }
            window.draw(m_triangle);
        }
    }

    Node* getParent() {
        return m_parent;
    }

    Node* getChild() {
        return m_child;
    }

    size_t getRepTimes() {
        setLine();
        return m_repTimes;
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
                if(m_trianglePositions.size() == 1) {
                    m_triangleAccentColorPosition = m_accentColorPosition == 3 ? 0 : -1;
                }
                else {
                    switch(m_accentColorPosition) {
                    case 1:
                        m_triangleAccentColorPosition = 0;
                        break;
                    case 3:
                        m_triangleAccentColorPosition = 1;
                        break;
                    default:
                        m_triangleAccentColorPosition = -1;
                    }
                }
            }
            else if(fabs(m_coordChild.x - m_coordParent.x) < 15) {
                almostStraightLine();
                if(m_accentColorPosition == 5) {
                    m_accentColorPosition += 2;
                }
                switch(m_accentColorPosition) {
                case 1:
                    m_triangleAccentColorPosition = 0;
                    break;
                case 7:
                    m_triangleAccentColorPosition = 1;
                    break;
                default:
                    m_triangleAccentColorPosition = -1;
                }
            }
            else {
                cabLine();
                if(m_accentColorPosition > 0) {
                    m_triangleAccentColorPosition = m_accentColorPosition / 2;
                }
                else {
                    m_triangleAccentColorPosition = -1;
                }
            }
        }
        else {
            detourCabLine();
            switch(m_accentColorPosition) {
            case 3:
                m_triangleAccentColorPosition = 0;
                break;
            case 5:
                m_triangleAccentColorPosition = 1;
                break;
            case 7:
                m_triangleAccentColorPosition = 2;
                break;
            default:
                m_triangleAccentColorPosition = -1;
            }
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
        m_repTimes = 3;

        m_trianglePositions.clear();
        m_triangleRotations.clear();
        if(m_coordChild.y - m_coordParent.y > 15.0f) {
            if(m_coordChild.y - m_coordParent.y < 100.0f) {
                m_trianglePositions.push_back(sf::Vector2f(m_coordParent.x, m_coordParent.y + (m_coordChild.y - m_coordParent.y) * 0.5f));
                m_triangleRotations.push_back(180);
            }
            else {
                m_trianglePositions.push_back(sf::Vector2f(m_coordParent.x, m_coordParent.y + deltaY));
                m_trianglePositions.push_back(sf::Vector2f(m_coordParent.x, m_coordParent.y + 2*deltaY));
                m_triangleRotations.push_back(180);
                m_triangleRotations.push_back(180);
            }
        }
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
        m_repTimes = 4;

        m_trianglePositions.clear();
        m_triangleRotations.clear();
        if(m_coordChild.y - m_coordParent.y > 15.0f) {
            m_trianglePositions.push_back(sf::Vector2f(m_coordParent.x, m_coordParent.y + deltaY));
            m_trianglePositions.push_back(sf::Vector2f(m_coordChild.x,  m_coordChild.y  - deltaY));
            m_triangleRotations.push_back(180);
            m_triangleRotations.push_back(180);
        }
    }

    void cabLine() {
        float midY = (m_coordParent.y + m_coordChild.y) * 0.5f;

        m_line.push_back(sf::Vertex(sf::Vector2f{m_coordParent.x, m_coordParent.y}));
        m_line.push_back(sf::Vertex(sf::Vector2f{m_coordParent.x, midY}));

        m_line.push_back(sf::Vertex(sf::Vector2f{m_coordParent.x, midY}));
        m_line.push_back(sf::Vertex(sf::Vector2f{m_coordChild.x,  midY}));

        m_line.push_back(sf::Vertex(sf::Vector2f{m_coordChild.x,  midY}));
        m_line.push_back(sf::Vertex(sf::Vector2f{m_coordChild.x,  m_coordChild.y}));

        m_repTimes = 3;

        float deltaY = (m_coordChild.y - m_coordParent.y) * 0.25f;
        m_trianglePositions.clear();
        m_triangleRotations.clear();
        if(m_coordChild.y - m_coordParent.y > 15.0f) {
            m_trianglePositions.push_back(sf::Vector2f(m_coordParent.x, m_coordParent.y + deltaY));
            m_trianglePositions.push_back(sf::Vector2f((m_coordParent.x + m_coordChild.x)/2, midY));
            m_trianglePositions.push_back(sf::Vector2f(m_coordChild.x,  m_coordChild.y  - deltaY));
            m_triangleRotations.push_back(180);
            m_triangleRotations.push_back(150 + 60*(m_coordParent.x < m_coordChild.x));
            m_triangleRotations.push_back(180);
        }
        else {
            m_trianglePositions.push_back(sf::Vector2f((m_coordParent.x + m_coordChild.x)/2, midY));
            m_triangleRotations.push_back(150 + 60*(m_coordParent.x < m_coordChild.x));
        }
    }

    void detourCabLine() {
        float childMargin = (m_child ? 10 : 0);
        float parentMargin = 10;
        float parentWidth  = m_parent->width/2;
        float parentHeight = m_parent->height;
        float childWidth  = (m_child ? m_child->width  : 0) / 2;
        float childHeight = (m_child ? m_child->height : 0) / 2 + 2*childMargin;

        float coordLeft   = std::min(m_coordParent.x - parentWidth, m_coordChild.x - childWidth);
        float coordTop    = std::min(m_coordParent.y - parentHeight, m_coordChild.y);
        float coordBottom = std::max(m_coordParent.y, m_coordChild.y + childHeight);

        m_line.push_back(sf::Vertex(sf::Vector2f(m_coordParent.x, m_coordParent.y)));
        m_line.push_back(sf::Vertex(sf::Vector2f(m_coordParent.x, coordBottom + parentMargin)));

        m_line.push_back(sf::Vertex(sf::Vector2f(m_coordParent.x,        coordBottom + parentMargin)));
        m_line.push_back(sf::Vertex(sf::Vector2f(coordLeft-parentMargin, coordBottom + parentMargin)));

        m_line.push_back(sf::Vertex(sf::Vector2f(coordLeft-parentMargin, coordBottom + parentMargin)));
        m_line.push_back(sf::Vertex(sf::Vector2f(coordLeft-parentMargin, coordTop - childMargin)));

        m_line.push_back(sf::Vertex(sf::Vector2f(coordLeft-parentMargin, coordTop - childMargin)));
        m_line.push_back(sf::Vertex(sf::Vector2f(m_coordChild.x,        coordTop - childMargin)));

        m_line.push_back(sf::Vertex(sf::Vector2f(m_coordChild.x, coordTop - childMargin)));
        m_line.push_back(sf::Vertex(sf::Vector2f(m_coordChild.x, m_coordChild.y)));

        m_repTimes = 5;

        m_trianglePositions.clear();
        m_trianglePositions.push_back(sf::Vector2f((coordLeft-parentMargin + m_coordParent.x)/2, coordBottom + parentMargin));
        m_trianglePositions.push_back(sf::Vector2f(coordLeft-parentMargin, (coordTop + coordBottom)/2));
        m_trianglePositions.push_back(sf::Vector2f((coordLeft-parentMargin + m_coordChild.x)/2, coordTop - childMargin));
        m_triangleRotations.clear();
        m_triangleRotations.push_back(150);
        m_triangleRotations.push_back(240);
        m_triangleRotations.push_back(210);
    }

private:
    sf::Vector2f m_coordParent = sf::Vector2f(-1, -1);
    sf::Vector2f m_coordChild  = sf::Vector2f(-1, -1);
    std::vector<sf::Vertex> m_line;
    sf::CircleShape m_triangle = sf::CircleShape(5, 3);
    std::vector<sf::Vector2f> m_trianglePositions;
    std::vector<float> m_triangleRotations;
    Constants::CoordType m_parentCoordType;
    Node* m_parent = NULL;
    Node* m_child = NULL;
    bool m_connected = false;
    sf::Color m_mainColor   = sf::Color( 33,  33,  33);
    sf::Color m_accentColor = sf::Color(233, 233, 233);
    sf::Color m_triangleColor = sf::Color(127, 127, 127);
    int m_accentColorPosition = -1;
    int m_triangleAccentColorPosition = -1;
    size_t m_repTimes = 0;
};

std::vector<Line> lines{};

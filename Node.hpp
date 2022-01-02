#pragma once

#include <string>
#include <cstring>
#include <bits/stdc++.h>

#include "Constants.hpp"
using namespace std;

struct Node {
public:
    Node(Constants::NodeType nodeType_, const sf::Font& font) {
        nodeType = nodeType_;

        text.setFont(font);
        text.setCharacterSize(16);
        text.setFillColor(sf::Color::Black);
        setTextString("");
    }

    void setNodeCoordonates(sf::Vector2f coord) {
        m_coord = coord;
        m_shape = setShape();

        setCoordonates();
    }

    sf::Vector2f getNodeCoordonates(Constants::CoordType coordType) {
        switch(coordType) {
        case Constants::CoordIn:
            return m_coordIn;
        case Constants::CoordOut:
            return m_coordOut;
        case Constants::CoordOutTrue:
            return m_coordOutTrue;
        case Constants::CoordOutFalse:
            return m_coordOutFalse;
        case Constants::CoordNode:
            return m_coord;
        }
        return sf::Vector2f{-1, -1};
    }

    void setTextString(std::string textString) {
        text.setString(textString);
        for(int i = 0; i < textString.size(); ++i)
            content[i] = textString[i];
        content[textString.size()] = NULL;
        // determin dimensiunile nodului
        width = text.getGlobalBounds().width + 2*m_padding;
        height = text.getGlobalBounds().height + 2*m_padding;
        width = std::max(width, 30.0f);
        height = std::max(height, 30.0f);
        if(nodeType == Constants::ConditionalNode) {
            height *= 1.5f;
            width = std::max(width, 40.0f);
            if(width > 100) {
                height += (width - 100) * 0.2;
            }
        }
        setCoordonates();
        m_shape = setShape();
    }

    sf::ConvexShape getShape() {
        if(m_coord == sf::Vector2f{-1, -1}) {
            throw std::invalid_argument("You did not set the coordinates for this shape");
        }
        if(!m_shapeAssigned) {
            m_shapeAssigned = true;
            m_shape = setShape();
        }
        return m_shape;
    }

    bool collides(Node* other) {
        if(other == NULL) {
            return false;
        }

        sf::Vector2f meTL = hitbox.getPosition();
        sf::Vector2f meBR = meTL + hitbox.getSize();

        sf::Vector2f otherTL = other->hitbox.getPosition();
        sf::Vector2f otherBR = otherTL + other->hitbox.getSize();

        return (meTL.x < otherBR.x) * (otherTL.x < meBR.x) * (meTL.y < otherBR.y) * (otherTL.y < meBR.y);
    }

    bool collides(sf::Vector2i mousePosition, sf::Vector2f hitboxSize) {
        sf::Vector2f meTL = hitbox.getPosition();
        sf::Vector2f meBR = meTL + hitbox.getSize();

        sf::Vector2f otherTL = sf::Vector2f{mousePosition.x, mousePosition.y} - hitboxSize*0.5f;
        sf::Vector2f otherBR = sf::Vector2f{mousePosition.x, mousePosition.y} + hitboxSize*0.5f;

        if(meTL.x > otherBR.x or otherTL.x > meBR.x) {
            return false;
        }
        if(meTL.y > otherBR.y or otherTL.y > meBR.y) {
            return false;
        }
        return true;
    }

public:
    Constants::NodeType nodeType;
    float height = 30;
    float width = 100;
    int vizT = 0;
    int vizF = 0;
    sf::RectangleShape hitbox;
    sf::Text text;
    Node* urm = NULL;
    Node* urmTrue = NULL;
    Node* urmFalse = NULL;
    char content[500];

private:
    void setCoordonates() {
        if(nodeType == Constants::ConditionalNode) {
            m_coordIn        = m_coord + sf::Vector2f{       0, -2*height/3};
            m_coordOut       = m_coord + sf::Vector2f{       0,    height/3};
            m_coordOutTrue   = m_coord + sf::Vector2f{-width/2,    height/3};
            m_coordOutFalse  = m_coord + sf::Vector2f{ width/2,    height/3};
        }
        else {
            m_coordIn        = m_coord + sf::Vector2f{       0, -height/2};
            m_coordOut       = m_coord + sf::Vector2f{       0,  height/2};
            m_coordOutTrue   = m_coord + sf::Vector2f{-width/2,  height/2};
            m_coordOutFalse  = m_coord + sf::Vector2f{ width/2,  height/2};
        }
    }

    sf::ConvexShape setShape() {
        hitbox = sf::RectangleShape(sf::Vector2f{width-1, height-1});
        hitbox.setPosition(m_coord - sf::Vector2f{width/2, height/2});
        hitbox.setFillColor(sf::Color::Transparent);
        hitbox.setOutlineColor(sf::Color::Green);
        hitbox.setOutlineThickness(2);

        float textH = text.getGlobalBounds().height;
        float textW = text.getGlobalBounds().width;
        text.setPosition(m_coord - sf::Vector2f{textW/2, 4*textH/5});

        switch(nodeType) {
        case Constants::StartNode:
            return startNodeShape();
        case Constants::AssignNode:
            return assignNodeShape();
        case Constants::ConditionalNode:
            return conditionalNodeShape();
        case Constants::StopNode:
            return stopNodeShape();
        case Constants::OutputNode:
            return outputNodeShape();
        case Constants::ReadNode:
            return readNodeShape();
        default:
            return sf::ConvexShape(0);
        }
    }

    sf::ConvexShape startNodeShape() {
        sf::ConvexShape convexShape;
        convexShape.setPointCount(4);
        convexShape.setOutlineThickness(2);
        convexShape.setOutlineColor(sf::Color::Red);

        convexShape.setPoint(0, m_coord + sf::Vector2f{-width/2, -height/2});
        convexShape.setPoint(1, m_coord + sf::Vector2f{ width/2, -height/2});
        convexShape.setPoint(2, m_coord + sf::Vector2f{ width/2,  height/2});
        convexShape.setPoint(3, m_coord + sf::Vector2f{-width/2,  height/2});

        return convexShape;
    }

    sf::ConvexShape assignNodeShape() {
        sf::ConvexShape convexShape;
        convexShape.setPointCount(4);
        convexShape.setOutlineThickness(2);
        convexShape.setOutlineColor(sf::Color::Red);

        convexShape.setPoint(0, m_coord + sf::Vector2f{-width/2-5, -height/2});
        convexShape.setPoint(1, m_coord + sf::Vector2f{ width/2+5, -height/2});
        convexShape.setPoint(2, m_coord + sf::Vector2f{ width/2-5,  height/2});
        convexShape.setPoint(3, m_coord + sf::Vector2f{-width/2+5,  height/2});

        return convexShape;
    }

    sf::ConvexShape conditionalNodeShape() {
        hitbox.setSize(sf::Vector2f{width, height});
        hitbox.setPosition(m_coord - sf::Vector2f{width/2, height-20});

        sf::ConvexShape convexShape;
        convexShape.setPointCount(6);
        convexShape.setOutlineThickness(2);
        convexShape.setOutlineColor(sf::Color::Red);

        convexShape.setPoint(0, m_coord + sf::Vector2f{     -10, -height+20});  // -2*height/3});
        convexShape.setPoint(1, m_coord + sf::Vector2f{      10, -height+20});  // -2*height/3});
        convexShape.setPoint(2, m_coord + sf::Vector2f{ width/2,  0});  //    height/3-10});
        convexShape.setPoint(3, m_coord + sf::Vector2f{ width/2,  20});  //    height/3});
        convexShape.setPoint(4, m_coord + sf::Vector2f{-width/2,  20});  //    height/3});
        convexShape.setPoint(5, m_coord + sf::Vector2f{-width/2,  0});  //    height/3-10});

        m_coordIn        = m_coord + sf::Vector2f{       0, -height+20};
        m_coordOut       = m_coord + sf::Vector2f{       0,  20};
        m_coordOutTrue   = m_coord + sf::Vector2f{-width/2,  20};
        m_coordOutFalse  = m_coord + sf::Vector2f{ width/2,  20};

        return convexShape;
    }

    sf::ConvexShape stopNodeShape() {
        sf::ConvexShape convexShape;
        convexShape.setPointCount(4);
        convexShape.setOutlineThickness(2);
        convexShape.setOutlineColor(sf::Color::Red);

        convexShape.setPoint(0, m_coord + sf::Vector2f{-width/2, -height/2});
        convexShape.setPoint(1, m_coord + sf::Vector2f{ width/2, -height/2});
        convexShape.setPoint(2, m_coord + sf::Vector2f{ width/2,  height/2});
        convexShape.setPoint(3, m_coord + sf::Vector2f{-width/2,  height/2});

        return convexShape;
    }

    sf::ConvexShape outputNodeShape() {
        sf::ConvexShape convexShape;
        convexShape.setPointCount(4);
        convexShape.setOutlineThickness(2);
        convexShape.setOutlineColor(sf::Color::Red);

        convexShape.setPoint(0, m_coord + sf::Vector2f{-width/2+5, -height/2});
        convexShape.setPoint(1, m_coord + sf::Vector2f{ width/2-5, -height/2});
        convexShape.setPoint(2, m_coord + sf::Vector2f{ width/2+5,  height/2});
        convexShape.setPoint(3, m_coord + sf::Vector2f{-width/2-5,  height/2});

        return convexShape;
    }

    sf::ConvexShape readNodeShape() {
        sf::ConvexShape convexShape;
        convexShape.setPointCount(4);
        convexShape.setOutlineThickness(2);
        convexShape.setOutlineColor(sf::Color::Red);

        convexShape.setPoint(0, m_coord + sf::Vector2f{-width/2-5, -height/2});
        convexShape.setPoint(1, m_coord + sf::Vector2f{ width/2+5, -height/2});
        convexShape.setPoint(2, m_coord + sf::Vector2f{ width/2-5,  height/2});
        convexShape.setPoint(3, m_coord + sf::Vector2f{-width/2+5,  height/2});

        return convexShape;
    }

private:
    sf::Vector2f m_coord = sf::Vector2f{-1, -1};
    sf::Vector2f m_coordIn;
    sf::Vector2f m_coordOut;
    sf::Vector2f m_coordOutTrue;
    sf::Vector2f m_coordOutFalse;
    sf::ConvexShape m_shape;
    bool m_shapeAssigned = false;
    int m_padding = 10;
};

int q;
vector<Node*> nodes;

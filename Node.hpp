#pragma once

#include <string>
#include <cstring>

#include "Constants.hpp"

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

        coordIn        = m_coord + sf::Vector2f{       0, -height/2};
        coordInRec     = m_coord + sf::Vector2f{-width/2, -height/2};
        coordOut       = m_coord + sf::Vector2f{       0,  height/2};
        coordOutTrue   = m_coord + sf::Vector2f{-width/2,  height/2};
        coordOutFalse  = m_coord + sf::Vector2f{ width/2,  height/2};
    }

    sf::Vector2f getNodeCoordonates() {
        return m_coord;
    }

    void setTextString(std::string textString) {
        text.setString(textString);
        for(int i = 0; i < textString.size(); ++i)
            content[i] = textString[i];
        content[textString.size()] = NULL;
        // determin dimensiunile nodului
        width = text.getGlobalBounds().width + 2*m_padding;
        height = text.getGlobalBounds().height + 2*m_padding;
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

public:
    Constants::NodeType nodeType;
    float height = 30;
    float width = 100;
    sf::RectangleShape hitbox;
    sf::Text text;
    sf::Vector2f coordIn;
    sf::Vector2f coordInRec;
    sf::Vector2f coordOut;
    sf::Vector2f coordOutTrue;
    sf::Vector2f coordOutFalse;
    Node* urm;
    Node* urmTrue;
    Node* urmFalse;
    char content[500];

private:
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
            return StartNodeShape();
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

    sf::ConvexShape StartNodeShape() {
        sf::ConvexShape convexShape;
        convexShape.setPointCount(4);

        convexShape.setPoint(0, m_coord + sf::Vector2f{-width/2, -height/2});
        convexShape.setPoint(1, m_coord + sf::Vector2f{ width/2, -height/2});
        convexShape.setPoint(2, m_coord + sf::Vector2f{ width/2,  height/2});
        convexShape.setPoint(3, m_coord + sf::Vector2f{-width/2,  height/2});

        return convexShape;
    }

    sf::ConvexShape assignNodeShape() {
        sf::ConvexShape convexShape;
        convexShape.setPointCount(4);

        convexShape.setPoint(0, m_coord + sf::Vector2f{-width/2, -height/2});
        convexShape.setPoint(1, m_coord + sf::Vector2f{ width/2, -height/2});
        convexShape.setPoint(2, m_coord + sf::Vector2f{ width/2,  height/2});
        convexShape.setPoint(3, m_coord + sf::Vector2f{-width/2,  height/2});

        return convexShape;
    }

    sf::ConvexShape conditionalNodeShape() {
        sf::ConvexShape convexShape;
        convexShape.setPointCount(4);

        convexShape.setPoint(0, m_coord + sf::Vector2f{-width/2, -height/2});
        convexShape.setPoint(1, m_coord + sf::Vector2f{ width/2, -height/2});
        convexShape.setPoint(2, m_coord + sf::Vector2f{ width/2,  height/2});
        convexShape.setPoint(3, m_coord + sf::Vector2f{-width/2,  height/2});

        return convexShape;
    }

    sf::ConvexShape stopNodeShape() {
        sf::ConvexShape convexShape;
        convexShape.setPointCount(4);

        convexShape.setPoint(0, m_coord + sf::Vector2f{-width/2, -height/2});
        convexShape.setPoint(1, m_coord + sf::Vector2f{ width/2, -height/2});
        convexShape.setPoint(2, m_coord + sf::Vector2f{ width/2,  height/2});
        convexShape.setPoint(3, m_coord + sf::Vector2f{-width/2,  height/2});

        return convexShape;
    }

    sf::ConvexShape outputNodeShape() {
        sf::ConvexShape convexShape;
        convexShape.setPointCount(4);

        convexShape.setPoint(0, m_coord + sf::Vector2f{-width/2, -height/2});
        convexShape.setPoint(1, m_coord + sf::Vector2f{ width/2, -height/2});
        convexShape.setPoint(2, m_coord + sf::Vector2f{ width/2,  height/2});
        convexShape.setPoint(3, m_coord + sf::Vector2f{-width/2,  height/2});

        return convexShape;
    }

    sf::ConvexShape readNodeShape() {
        sf::ConvexShape convexShape;
        convexShape.setPointCount(4);

        convexShape.setPoint(0, m_coord + sf::Vector2f{-width/2, -height/2});
        convexShape.setPoint(1, m_coord + sf::Vector2f{ width/2, -height/2});
        convexShape.setPoint(2, m_coord + sf::Vector2f{ width/2,  height/2});
        convexShape.setPoint(3, m_coord + sf::Vector2f{-width/2,  height/2});

        return convexShape;
    }

private:
    sf::Vector2f m_coord = sf::Vector2f{-1, -1};
    sf::ConvexShape m_shape;
    bool m_shapeAssigned = false;
    int m_padding = 10;
};

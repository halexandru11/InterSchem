#pragma once

#include <string>
#include <cstring>
#include <bits/stdc++.h>
#include "Constants.hpp"

static const sf::Color BACKGROUND_COLOR          = sf::Color(198, 255,  0);
static const sf::Color BACKGROUND_COLOR_ACTIVE   = sf::Color(238, 255, 65);
static const sf::Color BACKGROUND_COLOR_INACTIVE = sf::Color(175, 180, 43);

static const sf::Color OUTLINE_COLOR             = sf::Color(55, 55, 55);
static const sf::Color OUTLINE_COLOR_ACTIVE      = sf::Color(66, 66, 66);
static const sf::Color OUTLINE_COLOR_INACTIVE    = sf::Color(33, 33, 33);

struct Node {
public:
    Node(Constants::NodeType nodeType_, const sf::Font& font) {
        nodeType = nodeType_;

        text.setFont(font);
        text.setCharacterSize(16);
        text.setFillColor(sf::Color::Black);
        setTextString("");

        hitbox = sf::RectangleShape();
    }

    void setNodeCoordonates(sf::Vector2f coord) {
        m_coord = coord;
        setShape();

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
                height += (width - 100) * 0.1 ;
            }
        }
        setCoordonates();
        setShape();
    }

    sf::ConvexShape getShape() {
        if(m_coord == sf::Vector2f{-1, -1}) {
            throw std::invalid_argument("You did not set the coordinates for this shape");
        }
        if(!m_shapeAssigned) {
            m_shapeAssigned = true;
            setShape();
        }
        return m_shape;
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

    void resetNode() {
        m_isActive = false;
        m_backgroundColor = BACKGROUND_COLOR;
        m_outlineColor = OUTLINE_COLOR;
        m_shape.setFillColor(m_backgroundColor);
        m_shape.setOutlineColor(m_outlineColor);
    }

    void activateNode() {
        m_isActive = true;
        m_backgroundColor = BACKGROUND_COLOR_ACTIVE;
        m_outlineColor = OUTLINE_COLOR_ACTIVE;
        m_shape.setFillColor(m_backgroundColor);
        m_shape.setOutlineColor(m_outlineColor);
    }

    void deactivateNode() {
        m_backgroundColor = BACKGROUND_COLOR_INACTIVE;
        m_outlineColor = OUTLINE_COLOR_INACTIVE;
        m_shape.setFillColor(m_backgroundColor);
        m_shape.setOutlineColor(m_outlineColor);
    }

    bool isActive() {
        return m_isActive;
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
        m_coordIn       = m_coord + sf::Vector2f{       0, -height/2};
        m_coordOut      = m_coord + sf::Vector2f{       0,  height/2};
        m_coordOutTrue  = m_coord + sf::Vector2f{-width/2,  height/2};
        m_coordOutFalse = m_coord + sf::Vector2f{ width/2,  height/2};

        float textH = text.getGlobalBounds().height;
        float textW = text.getGlobalBounds().width;
        text.setPosition(m_coordOut - sf::Vector2f{0.5f*textW, textH + 15});
    }

    void setShape() {
        switch(nodeType) {
        case Constants::StartNode:
            m_shape = startNodeShape();
            break;
        case Constants::AssignNode:
            m_shape = assignNodeShape();
            break;
        case Constants::ConditionalNode:
            m_shape = conditionalNodeShape();
            break;
        case Constants::StopNode:
            m_shape = stopNodeShape();
            break;
        case Constants::OutputNode:
            m_shape = outputNodeShape();
            break;
        case Constants::ReadNode:
            m_shape = readNodeShape();
            break;
        default:
            m_shape = sf::ConvexShape(0);
        }
        m_shape.setFillColor(m_backgroundColor);
        setHitbox();
    }

    sf::ConvexShape startNodeShape() {
        sf::ConvexShape convexShape;
        convexShape.setPointCount(8);
        convexShape.setOutlineThickness(-2);
        convexShape.setFillColor(m_backgroundColor);
        convexShape.setOutlineColor(m_outlineColor);

        convexShape.setPoint(0, m_coord + sf::Vector2f{-width/2,   -height/2+5});
        convexShape.setPoint(1, m_coord + sf::Vector2f{-width/2+5, -height/2});
        convexShape.setPoint(2, m_coord + sf::Vector2f{ width/2-5, -height/2});
        convexShape.setPoint(3, m_coord + sf::Vector2f{ width/2,   -height/2+5});
        convexShape.setPoint(4, m_coord + sf::Vector2f{ width/2,    height/2-5});
        convexShape.setPoint(5, m_coord + sf::Vector2f{ width/2-5,  height/2});
        convexShape.setPoint(6, m_coord + sf::Vector2f{-width/2+5,  height/2});
        convexShape.setPoint(7, m_coord + sf::Vector2f{-width/2,    height/2-5});

        return convexShape;
    }

    sf::ConvexShape assignNodeShape() {
        sf::ConvexShape convexShape;
        convexShape.setPointCount(4);
        convexShape.setOutlineThickness(-2);
        convexShape.setFillColor(m_backgroundColor);
        convexShape.setOutlineColor(m_outlineColor);

        convexShape.setPoint(0, m_coord + sf::Vector2f{-width/2-5, -height/2});
        convexShape.setPoint(1, m_coord + sf::Vector2f{ width/2+5, -height/2});
        convexShape.setPoint(2, m_coord + sf::Vector2f{ width/2-5,  height/2});
        convexShape.setPoint(3, m_coord + sf::Vector2f{-width/2+5,  height/2});

        return convexShape;
    }

    sf::ConvexShape conditionalNodeShape() {
        hitbox.setSize(sf::Vector2f{width, height});
        hitbox.setPosition(m_coord - sf::Vector2f{width/2, height});

        sf::ConvexShape convexShape;
        convexShape.setPointCount(6);
        convexShape.setOutlineThickness(-2);
        convexShape.setFillColor(m_backgroundColor);
        convexShape.setOutlineColor(m_outlineColor);

        convexShape.setPoint(0, m_coord + sf::Vector2f{     -10, -height/2});  // -2*height/3});
        convexShape.setPoint(1, m_coord + sf::Vector2f{      10, -height/2});  // -2*height/3});
        convexShape.setPoint(2, m_coord + sf::Vector2f{ width/2,  height/2-20});  //    height/3-10});
        convexShape.setPoint(3, m_coord + sf::Vector2f{ width/2,  height/2});  //    height/3});
        convexShape.setPoint(4, m_coord + sf::Vector2f{-width/2,  height/2});  //    height/3});
        convexShape.setPoint(5, m_coord + sf::Vector2f{-width/2,  height/2-20});  //    height/3-10});

        return convexShape;
    }


    sf::ConvexShape outputNodeShape() {
        sf::ConvexShape convexShape;
        convexShape.setPointCount(4);
        convexShape.setOutlineThickness(-2);
        convexShape.setFillColor(m_backgroundColor);
        convexShape.setOutlineColor(m_outlineColor);

        convexShape.setPoint(0, m_coord + sf::Vector2f{-width/2+5, -height/2});
        convexShape.setPoint(1, m_coord + sf::Vector2f{ width/2-5, -height/2});
        convexShape.setPoint(2, m_coord + sf::Vector2f{ width/2+5,  height/2});
        convexShape.setPoint(3, m_coord + sf::Vector2f{-width/2-5,  height/2});

        return convexShape;
    }

    sf::ConvexShape readNodeShape() {
        sf::ConvexShape convexShape;
        convexShape.setPointCount(4);
        convexShape.setOutlineThickness(-2);
        convexShape.setFillColor(m_backgroundColor);
        convexShape.setOutlineColor(m_outlineColor);

        convexShape.setPoint(0, m_coord + sf::Vector2f{-width/2-5, -height/2});
        convexShape.setPoint(1, m_coord + sf::Vector2f{ width/2+5, -height/2});
        convexShape.setPoint(2, m_coord + sf::Vector2f{ width/2-5,  height/2});
        convexShape.setPoint(3, m_coord + sf::Vector2f{-width/2+5,  height/2});

        return convexShape;
    }

    sf::ConvexShape stopNodeShape() {
        sf::ConvexShape convexShape;
        convexShape.setPointCount(8);
        convexShape.setOutlineThickness(-2);
        convexShape.setFillColor(m_backgroundColor);
        convexShape.setOutlineColor(m_outlineColor);

        convexShape.setPoint(0, m_coord + sf::Vector2f{-width/2,   -height/2+5});
        convexShape.setPoint(1, m_coord + sf::Vector2f{-width/2+5, -height/2});
        convexShape.setPoint(2, m_coord + sf::Vector2f{ width/2-5, -height/2});
        convexShape.setPoint(3, m_coord + sf::Vector2f{ width/2,   -height/2+5});
        convexShape.setPoint(4, m_coord + sf::Vector2f{ width/2,    height/2-5});
        convexShape.setPoint(5, m_coord + sf::Vector2f{ width/2-5,  height/2});
        convexShape.setPoint(6, m_coord + sf::Vector2f{-width/2+5,  height/2});
        convexShape.setPoint(7, m_coord + sf::Vector2f{-width/2,    height/2-5});

        return convexShape;
    }

    void setHitbox() {
        hitbox.setSize(sf::Vector2f{width-1, height-1});
        hitbox.setPosition(m_coord - sf::Vector2f{width/2, height/2});
        hitbox.setFillColor(sf::Color::Transparent);
        hitbox.setOutlineColor(sf::Color::Green);
        hitbox.setOutlineThickness(2);
    }

private:
    sf::Vector2f m_coord = sf::Vector2f{-1, -1};
    sf::Vector2f m_coordIn;
    sf::Vector2f m_coordOut;
    sf::Vector2f m_coordOutTrue;
    sf::Vector2f m_coordOutFalse;
    sf::ConvexShape m_shape;
    sf::Color m_backgroundColor = BACKGROUND_COLOR;
    sf::Color m_outlineColor = OUTLINE_COLOR;
    bool m_shapeAssigned = false;
    bool m_isActive = false;
    int m_padding = 10;
};

int q;
std::vector<Node*> nodes;

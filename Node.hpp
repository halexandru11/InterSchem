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

        m_coordIn        = m_coord + sf::Vector2f{       0, -height/2};
        m_coordOut       = m_coord + sf::Vector2f{       0,  height/2};
        m_coordOutTrue   = m_coord + sf::Vector2f{-width/2,  height/2};
        m_coordOutFalse  = m_coord + sf::Vector2f{ width/2,  height/2};
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
        float meLeft = m_coord.x - width/2;
        float meTop = m_coord.y - height/2;

        float otherWidth = other->hitbox.getGlobalBounds().width;
        float otherHeight = other->hitbox.getGlobalBounds().height;
        float otherLeft = other->hitbox.getGlobalBounds().left;
        float otherTop = other->hitbox.getGlobalBounds().top;

        std::vector<sf::Vector2f> otherCoords; otherCoords.clear();
        otherCoords.push_back(sf::Vector2f{otherLeft, otherTop});
        otherCoords.push_back(sf::Vector2f{otherLeft+otherWidth, otherTop});
        otherCoords.push_back(sf::Vector2f{otherLeft+otherWidth, otherTop+otherHeight});
        otherCoords.push_back(sf::Vector2f{otherLeft, otherTop+otherHeight});

        for(const sf::Vector2f& c : otherCoords) {
            if(meLeft < c.x and c.x < meLeft+width and
               meTop < c.y and c.y < meTop+height) {
                return true;
            }
        }
        return false;
    }

public:
    Constants::NodeType nodeType;
    float height = 30;
    float width = 100;
    sf::RectangleShape hitbox;
    sf::Text text;
    Node* urm = NULL;
    Node* urmTrue = NULL;
    Node* urmFalse = NULL;
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
        hitbox.setSize(sf::Vector2f{width, 3*height/2});
        hitbox.setPosition(m_coord - sf::Vector2f{width/2, height});

        sf::ConvexShape convexShape;
        convexShape.setPointCount(6);
        convexShape.setOutlineThickness(2);
        convexShape.setOutlineColor(sf::Color::Red);

        convexShape.setPoint(0, m_coord + sf::Vector2f{     -10, -height});
        convexShape.setPoint(1, m_coord + sf::Vector2f{      10, -height});
        convexShape.setPoint(2, m_coord + sf::Vector2f{ width/2,  height/2-10});
        convexShape.setPoint(3, m_coord + sf::Vector2f{ width/2,  height/2});
        convexShape.setPoint(4, m_coord + sf::Vector2f{-width/2,  height/2});
        convexShape.setPoint(5, m_coord + sf::Vector2f{-width/2,  height/2-10});
        height *= 3/2;

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

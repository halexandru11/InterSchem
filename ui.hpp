#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#include "Buttons.hpp"
#include "Line.hpp"
#include "Node.hpp"

using namespace sf;
using namespace std;

RectangleShape leftBanner(Vector2f(125, 720));
RectangleShape rightBanner(Vector2f(270, 720));
RectangleShape workbench (Vector2f(900.0f,720.0f));

void afiseazaNoduri(RenderWindow &window, const vector<Node*>& nodes)
{
    for(size_t index = 0; index < nodes.size(); ++index) {
            nodes[index]->draw(window);

//            circle.setPosition(nodes[index]->getNodeCoordonates(Constants::CoordIn));
//            window.draw(circle);
//            circle.setPosition(nodes[index]->getNodeCoordonates(Constants::CoordOut));
//            window.draw(circle);
//            circle.setPosition(nodes[index]->getNodeCoordonates(Constants::CoordOutTrue));
//            window.draw(circle);
//            circle.setPosition(nodes[index]->getNodeCoordonates(Constants::CoordOutFalse));
//            window.draw(circle);
//            window.draw(nodes[index]->hitbox); /// DEBUG
        }
}

void afiseazaLinii(RenderWindow &window, const vector<Line>& lines)
{
    for(Line line : lines) {
        line.draw(window);
    }
}

void DeseneazaPeEcran(RenderWindow &window, const vector<Node*>& nodes, const vector<Line>& lines)
{
    leftBanner.setPosition(0, 0);
    workbench.setFillColor(Color(90,120,50));
    workbench.setPosition(125.0f, 0.0f);
    rightBanner.setPosition(1025, 0);
    window.draw(workbench);
    afiseazaNoduri(window, nodes);
    afiseazaLinii(window, lines);
    window.draw(leftBanner);
    window.draw(rightBanner);
    afisareButoane(window);
}

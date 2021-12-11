#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Buttons.hpp"
#include "Constants.hpp"
using namespace sf;
using namespace std;

void afiseazaNoduri(RenderWindow &window, const vector<Node*>& nodes)
{
//    Line line = Line(*nodes[0], *nodes[1], Constants::CoordOut, Constants::CoordIn);
//    Line line = Line(*nodes[0], Constants::CoordOut, window);
//    window.draw(&line.getLine(window)[0], line.getLine(window).size(), sf::Lines);
    for(size_t index = 0; index < nodes.size(); ++index) {
            window.draw(nodes[index]->getShape());
            window.draw(nodes[index]->text);

            circle.setPosition(nodes[index]->getNodeCoordonates(Constants::CoordIn));
            window.draw(circle);
            circle.setPosition(nodes[index]->getNodeCoordonates(Constants::CoordInRec));
            window.draw(circle);
            circle.setPosition(nodes[index]->getNodeCoordonates(Constants::CoordOut));
            window.draw(circle);
            circle.setPosition(nodes[index]->getNodeCoordonates(Constants::CoordOutTrue));
            window.draw(circle);
            circle.setPosition(nodes[index]->getNodeCoordonates(Constants::CoordOutFalse));
            window.draw(circle);
//            window.draw(nodes[index]->hitbox); /// DEBUG
        }
}

void DeseneazaPeEcran(RenderWindow &window, vector<Node*> nodes)
{
    afisareButoane(window);
    afiseazaNoduri(window, nodes);
}

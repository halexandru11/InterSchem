#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Buttons.hpp"
#include "Constants.hpp"
#include "Line.hpp"
using namespace sf;
using namespace std;

void afiseazaNoduri(RenderWindow &window, const vector<Node*>& nodes)
{
    Line line = Line(*nodes[0], *nodes[1], Constants::CoordOut, Constants::CoordIn);
    window.draw(&line.getLine()[0], line.getLine().size(), sf::Lines);
    for(size_t index = 0; index < nodes.size(); ++index) {
            window.draw(nodes[index]->getShape());
            window.draw(nodes[index]->text);

//            circle.setPosition(nodes[index]->coordIn);
//            window.draw(circle);
//            circle.setPosition(nodes[index]->coordInRec);
//            window.draw(circle);
//            circle.setPosition(nodes[index]->coordOut);
//            window.draw(circle);
//            circle.setPosition(nodes[index]->coordOutTrue);
//            window.draw(circle);
//            circle.setPosition(nodes[index]->coordOutFalse);
//            window.draw(circle);
//            window.draw(nodes[index]->hitbox); /// DEBUG
        }
}

void DeseneazaPeEcran(RenderWindow &window, vector<Node*> nodes)
{
    afisareButoane(window);
    afiseazaNoduri(window, nodes);
}

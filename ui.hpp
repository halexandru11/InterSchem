#pragma once

#include "Buttons.hpp"

using namespace sf;
using namespace std;

void afiseazaNoduri(RenderWindow &window, const vector<Node*>& nodes)
{
    for(size_t index = 0; index < nodes.size(); ++index) {
            window.draw(nodes[index]->getShape());
            window.draw(nodes[index]->text);

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
        auto shape = line.getLine(window);
        window.draw(&shape[0], shape.size(), Lines);
    }
}

void DeseneazaPeEcran(RenderWindow &window, const vector<Node*>& nodes, const vector<Line>& lines)
{
    afisareButoane(window);
    afiseazaNoduri(window, nodes);
    afiseazaLinii(window, lines);
}

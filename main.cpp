#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#include "Constants.hpp"
#include "Line.hpp"
#include "Node.hpp"
#include "EvaluareSchema.hpp"
#include "ui.hpp"
#include "functiiAuxiliare.hpp"
#include "inputText.hpp"
#include "import_export.hpp"

using namespace sf;
using namespace std;
int cnt;
int main()
{
    sf::ContextSettings settings = ContextSettings();
    settings.antialiasingLevel = 10;
    RenderWindow window(VideoMode(Constants::Width, Constants::Height), "Interschem", Style::Close | Style::Titlebar);
    initializareButoane(font);
    vector<Node*> nodes; nodes.clear();
    font.loadFromFile("Fonts\\Poppins\\Poppins-Regular.ttf");

    /** TEST EXPRESIE
    */

    bool hold = false;
    Vector2i oldPos;
    int target = -1;
    int emptyRectangle = -1;
    bool lineStarted = false;
    vector<Line> lines; lines.clear();
    int lineParentNode = -1;
    while (window.isOpen())
    {
        Event evnt;
        while (window.pollEvent(evnt))
        {
            if(evnt.type == Event::Closed)
            {
                window.close();
            }
            else if(evnt.type == Event::TextEntered)
            {
                if(actWritting != -1)
                    getInput(evnt,nodes);

            }
            else if(evnt.type == Event::MouseButtonPressed)
            {
                if(evnt.mouseButton.button == Mouse::Left and Keyboard::isKeyPressed(Keyboard::LControl)) {
                    Vector2f mousePos{Mouse::getPosition(window).x, Mouse::getPosition(window).y};
                    if(lineStarted == false) {
                        for(int i = 0; i < nodes.size(); ++i) {
                            if(isInside(mousePos, nodes[i])) {
                                lineParentNode = i;
                                if(nodes[i]->nodeType != Constants::ConditionalNode) {
                                    stergeLinie(lines, nodes[i], Constants::CoordOut);
                                    lines.push_back(Line(nodes[i], Constants::CoordOut, window));
                                }
                                else {
                                    if(Mouse::getPosition(window).x < nodes[i]->getNodeCoordonates(Constants::CoordNode).x) {
                                        stergeLinie(lines, nodes[i], Constants::CoordOutTrue);
                                        lines.push_back(Line(nodes[i], Constants::CoordOutTrue, window));
                                    }
                                    else {
                                        stergeLinie(lines, nodes[i], Constants::CoordOutFalse);
                                        lines.push_back(Line(nodes[i], Constants::CoordOutFalse, window));
                                    }
                                }
                                lineStarted = true;
                                break;
                            }
                        }
                    }
                    else {
                        for(int i = 0; i < nodes.size(); ++i) {
                            if(isInside(mousePos, nodes[i])) {
                                if(i != lineParentNode) {
                                    lines.back().connectToNode(nodes[i]);
                                    lineStarted = false;
                                    break;
                                }
                            }
                        }
                        if(lineStarted) {
                            lines.pop_back();
                        }
                        lineStarted = false;
                        lineParentNode = -1;
                    }
                }
                else if(evnt.mouseButton.button == Mouse::Left)
                {
                    hold = true;
                    oldPos = Mouse::getPosition(window);
                    Vector2f pos;
                    pos.x = static_cast<float>(oldPos.x);
                    pos.y = static_cast<float>(oldPos.y);
                    for(size_t i = 0; i < nodes.size(); ++i)
                        if(isInside(pos, nodes[i]))
                        {
                            target = i;
                            break;
                        }

                    if(isInsideButton(pos, buttonStart))
                        adauga_nod(nodes, Constants::StartNode);
                    if(isInsideButton(pos, buttonAssign))
                        adauga_nod(nodes, Constants::AssignNode);
                    if(isInsideButton(pos, buttonCond))
                        adauga_nod(nodes, Constants::ConditionalNode);
                    if(isInsideButton(pos, buttonOut))
                        adauga_nod(nodes, Constants::OutputNode);
                    if(isInsideButton(pos, buttonEnd))
                        adauga_nod(nodes, Constants::StopNode);
                    if(isInsideButton(pos, buttonRead))
                        adauga_nod(nodes, Constants::ReadNode);

                    if(isInsideButton(pos, buttonRun))
                        RunSchema(StartSchema);


                    if(isInsideButton(pos, buttonExport))
                        ExportToFile(nodes);
                    if(isInsideButton(pos, buttonImport))
                        ImportFromFile(nodes,lines);
                }
                else if(evnt.mouseButton.button == Mouse::Right)
                {
                    oldPos = Mouse::getPosition(window);
                    Vector2f pos;
                    pos.x = static_cast<float>(oldPos.x);
                    pos.y = static_cast<float>(oldPos.y);
                    for(size_t i = 0; i < nodes.size(); ++i)
                        if(isInside(pos, nodes[i]))
                        {
                            if(nodes[i]->nodeType == 1 || nodes[i]->nodeType == 5)
                                break;
                            actWritting = i;
                            nodes[actWritting]->setTextString(buffer);
                            break;
                        }
                }
                else if(evnt.mouseButton.button == Mouse::Middle)
                {
                    oldPos = Mouse::getPosition(window);
                    Vector2f pos;
                    pos.x = static_cast<float>(oldPos.x);
                    pos.y = static_cast<float>(oldPos.y);
                    bool deletee = 0;
                    for(size_t i = 0; i < nodes.size(); ++i)
                    {
                        if(isInside(pos,nodes[i]))
                        {
                            swap(nodes[i], nodes[ nodes.size() - 1 ]);
                            deletee = 1;
                            break;
                        }
                    }
                    if(deletee)
                    {
                        if(strcmp(nodes[ nodes.size() - 1 ]->content, "Start") == 0)
                        {
                           StartSchema = nullptr;
                           isStartNode = false;
                        }
                        if(strcmp(nodes[ nodes.size() - 1 ]->content, "Stop") == 0)
                           isStopNode = false;

                        stergeToateLiniile(lines, nodes.back());
                        delete nodes.back();
                        nodes.pop_back();
                    }
                }
            }
            else if(evnt.type == Event::MouseButtonReleased)
            {
                target = -1;
                hold = false;
            }
        }
        if(hold && target != -1)
        {
            Vector2i pozitieMouse = Mouse::getPosition(window);
            Vector2f coordMe = Vector2f{float(pozitieMouse.x), float(pozitieMouse.y)};
            for(size_t i = 0; i < nodes.size(); ++i) {
                if(i != target and nodes[i]->collides(pozitieMouse, nodes[target]->hitbox.getSize())) {
                    Vector2f coordOther = nodes[i]->getNodeCoordonates(Constants::CoordNode);
                    Vector2f var = coordMe;
                    Vector2f delta{nodes[i]->width + nodes[target]->width, nodes[i]->height + nodes[target]->height};
                    if(coordMe.x > coordOther.x) {
                        var.x = max(coordMe.x, coordOther.x + delta.x/2);
                    }
                    else {
                        var.x = min(coordMe.x, coordOther.x - delta.x/2);
                    }
                    if(coordMe.y > coordOther.y) {
                        var.y = max(coordMe.y, coordOther.y + delta.y/2);
                    }
                    else {
                        var.y = min(coordMe.y, coordOther.y - delta.y/2);
                    }

                    if(fabs(var.x - coordMe.x) * delta.y < fabs(var.y - coordMe.y) * delta.x) {
                        coordMe.x = var.x;
                    }
                    else {
                        coordMe.y = var.y;
                    }
                }
            }
            nodes[target]->setNodeCoordonates(coordMe);
        }
        window.clear();
        DeseneazaPeEcran(window,nodes, lines);
        window.display();
    }
    return 0;
}

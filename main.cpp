#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#include "Constants.hpp"
#include "Line.hpp"
#include "Node.hpp"
#include "EvaluareSchema.hpp"
#include "ui.hpp"
#include "functiiAuxiliare.hpp"
#include "inputText.hpp"

using namespace sf;
using namespace std;

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
    initializare();

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
                if(isPOPup)
                    getInputPop(evnt);

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
//                                        if(nodes[i]->urmFalse != NULL) {
////                                            cout << "3 ";
//                                            stergeLinie(lines, nodes[i], true, Constants::CoordOutFalse);
//                                        }
//                                        lines.push_back(Line(nodes[i], Constants::CoordOutFalse, window));
                                lineStarted = true;
                                break;
                            }
                        }
                    }
                    else {
                        for(int i = 0; i < nodes.size(); ++i) {
                            if(isInside(mousePos, nodes[i])) {
                                if(i != lineParentNode) {
                                    lines.back().connectToNode(nodes[i], Constants::CoordIn);
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
            Vector2f coordMe = Vector2f{float(Mouse::getPosition(window).x), float(Mouse::getPosition(window).y)};
            for(size_t i = 0; i < nodes.size(); ++i) {
                if(i != target) {
                    if(nodes[target]->collides(nodes[i])) {
                        Vector2f coordOther = nodes[i]->getNodeCoordonates(Constants::CoordNode);
                        if(coordMe.x > coordOther.x) {
                            coordMe.x = max(coordMe.x, coordOther.x + (nodes[i]->width + nodes[target]->width)/2);
                        }
                        else {
                            coordMe.x = min(coordMe.x, coordOther.x - (nodes[i]->width + nodes[target]->width)/2);
                        }
                    }
                }
            }
            nodes[target]->setNodeCoordonates(coordMe);
        }
        window.clear();
        DeseneazaPeEcran(window,nodes, lines);
        window.display();

//        for(Node* node : nodes) {
//            cout << int(node->nodeType) << ": ";
//            if(node->nodeType == Constants::ConditionalNode) {
//                if(node->urmTrue) {
//                    cout << int(node->urmTrue->nodeType) << " ";
//                }
//                else {
//                    cout << "NULL ";
//                }
//                if(node->urmFalse) {
//                    cout << int(node->urmFalse->nodeType) << "\n";
//                }
//                else {
//                    cout << "NULL\n";
//                }
//            }
//            else {
//                if(node->urm) {
//                    cout << int(node->urm->nodeType) << "\n";
//                }
//                else {
//                    cout << "NULL\n";
//                }
//            }
//        }
    }

    return 0;
}

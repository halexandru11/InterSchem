#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#include "Constants.hpp"
#include "Line.hpp"
#include "Node.hpp"
#include "Evaluare.hpp"
#include "ui.hpp"
#include "functiiAuxiliare.hpp"
#include "inputText.hpp"

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode(Constants::Width, Constants::Height), "Interschem", Style::Close | Style::Titlebar);
    initializareButoane(font);
    vector<Node*> nodes;
    nodes.clear();
    font.loadFromFile("Fonts\\Poppins\\Poppins-Regular.ttf");



//    sf::Vector2f coordA = sf::Vector2f{300, 300};
//    sf::Vector2f coordB = sf::Vector2f{500, 500};
//    adauga_nod(nodes, Constants::StartNode);
//    adauga_nod(nodes, Constants::ConditionalNode);
//    nodes[0]->setNodeCoordonates(sf::Vector2f{300, 300});
//    nodes[1]->setNodeCoordonates(sf::Vector2f{500, 500});

//    Line line = Line(*nodes[0], *nodes[1], Constants::CoordOut, Constants::CoordIn);
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
            }
            else if(evnt.type == Event::MouseButtonPressed)
            {
                if(evnt.mouseButton.button == Mouse::Left and Keyboard::isKeyPressed(Keyboard::LControl)) {
                    Vector2f mousePos{Mouse::getPosition(window).x, Mouse::getPosition(window).y};
                    if(lineStarted == false) {
                        for(int i = 0; i < nodes.size(); ++i) {
                            if(isInside(mousePos, nodes[i])) {
                                lineParentNode = i;
                                lines.push_back(Line(*nodes[i], Constants::CoordOut, window));
                                lineStarted = true;
                                break;
                            }
                        }
                    }
                    else {
                        for(int i = 0; i < nodes.size(); ++i) {
                            if(isInside(mousePos, nodes[i])) {
                                if(i != lineParentNode) {
                                    lines.back().connectToNode(*nodes[i], Constants::CoordIn);
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
                        adauga_nod(nodes,1);
                    if(isInsideButton(pos, buttonAssign))
                        adauga_nod(nodes,2);
                    if(isInsideButton(pos, buttonCond))
                        adauga_nod(nodes,3);
                    if(isInsideButton(pos, buttonOut))
                        adauga_nod(nodes,4);
                    if(isInsideButton(pos, buttonEnd))
                        adauga_nod(nodes,5);
                    if(isInsideButton(pos, buttonRead))
                        adauga_nod(nodes,6);
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
                           isStartNode = false;
                        if(strcmp(nodes[ nodes.size() - 1 ]->content, "Stop") == 0)
                           isStopNode = false;
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
            nodes[target]->setNodeCoordonates(sf::Vector2f{static_cast<float>(pozitieMouse.x), static_cast<float>(pozitieMouse.y)});
        }
        window.clear();
        DeseneazaPeEcran(window,nodes);
        for(Line l : lines) {
            window.draw(&l.getLine(window)[0], l.getLine(window).size(), Lines);
        }
        window.display();
    }

    return 0;
}

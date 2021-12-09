#if 0

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

#include "Constants.hpp"
#include "Node.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(Constants::Width, Constants::Height), "InterSchem", sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    sf::Font font;
    if (!font.loadFromFile("Fonts\\Poppins\\Poppins-Regular.ttf")) {
        std::cout << "Could not load the font\n";
        exit(1);
    }

    std::vector<Node*> nodes;
    nodes.clear();
    nodes.push_back(new Node(Constants::StartNode, font));
    nodes.push_back(new Node(Constants::AssignNode, font));
    nodes.push_back(new Node(Constants::ConditionalNode, font));
    nodes.push_back(new Node(Constants::OutputNode, font));
    nodes.push_back(new Node(Constants::StopNode, font));

    nodes[0]->setNodeCoordonates(sf::Vector2f{80,  50});
    nodes[1]->setNodeCoordonates(sf::Vector2f{80, 100});
    nodes[2]->setNodeCoordonates(sf::Vector2f{80, 150});
    nodes[3]->setNodeCoordonates(sf::Vector2f{80, 200});
    nodes[4]->setNodeCoordonates(sf::Vector2f{80, 250});

    nodes[0]->setTextString("Start");
    nodes[1]->setTextString("Assign");
    nodes[2]->setTextString("If");
    nodes[3]->setTextString("Output");
    nodes[4]->setTextString("Stop");

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:  // window closed
                    window.close();
                    break;
                case sf::Event::TextEntered: // key pressed
                    std::cout << char(event.text.unicode);
                    break;

                // we don't process other types of events
                default:
                    break;
            }
        }

        window.clear(sf::Color(255, 128, 0, 100));

        for(std::size_t index = 0; index < nodes.size(); ++index) {
            window.draw(nodes[index]->getShape());
            window.draw(nodes[index]->text);
//            window.draw(nodes[index]->hitbox);  // Pentru debug
        }
        window.display();
    }

    return 0;
}

#else

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <stdio.h>

#include "Constants.hpp"
#include "Line.hpp"
#include "Node.hpp"
#include "Evaluare.hpp"
#include "ui.hpp"

using namespace sf;
using namespace std;
sf::Font font;
bool isStartNode, isStopNode;
bool isInsideButton(Vector2f MousePos, RectangleShape q)
{
    Vector2f qOrigin = q.getPosition();
    Vector2f qSize = q.getSize();
    Vector2f susStanga = qOrigin;
    Vector2f josDreapta = qOrigin;
    susStanga.x -= qSize.x / 2;
    susStanga.y -= qSize.y / 2;
    josDreapta.x += qSize.x / 2;
    josDreapta.y += qSize.y / 2;
    cout << MousePos.x << ' ' << MousePos.y << '\n';
    cout << susStanga.x << ' ' << susStanga.y << '\n';
    cout << josDreapta.x << ' ' << josDreapta.y << '\n';
    cout << "\n\n";
    if(josDreapta.x >= MousePos.x && MousePos.x >= susStanga.x &&
        josDreapta.y >= MousePos.y && MousePos.y >= susStanga.y)
        {
            cout << "GOOD\n";
            return 1;
        }
    return 0;
}
/*
*/
bool isInside(Vector2f MousePos, Node *q)
{
    Vector2f qOrigin = q->getNodeCoordonates();
    Vector2f qSize = q->hitbox.getSize();
    Vector2f susStanga = qOrigin;
    Vector2f josDreapta = qOrigin;
    susStanga.x -= qSize.x / 2;
    susStanga.y -= qSize.y / 2;
    josDreapta.x += qSize.x / 2;
    josDreapta.y += qSize.y / 2;
    cout << MousePos.x << ' ' << MousePos.y << '\n';
    cout << susStanga.x << ' ' << susStanga.y << '\n';
    cout << josDreapta.x << ' ' << josDreapta.y << '\n';
    cout << "\n\n";
    if(josDreapta.x >= MousePos.x && MousePos.x >= susStanga.x &&
        josDreapta.y >= MousePos.y && MousePos.y >= susStanga.y)
        {
            cout << "GOOD\n";
            return 1;
        }
    return 0;
}
void adauga_nod_old(vector <RectangleShape> &D)
{
    RectangleShape patrat2(Vector2f(100.0f,100.0f));
    patrat2.setFillColor(Color::Green);
    patrat2.setOrigin(50.0f, 50.0f);
    patrat2.setPosition(200.0f, 200.f);
    D.push_back(patrat2);
}
void adauga_nod(vector <Node*> &D, int type)
{
    if(type == 1)
    {
        if(isStartNode)
            return;
        D.push_back(new Node(Constants::StartNode, font));
        D[D.size() - 1]->setTextString("Start");
        isStartNode = 1;
    }
    if(type == 2)
    {
        D.push_back(new Node(Constants::AssignNode, font));
        D[D.size() - 1]->setTextString("Assign");
    }
    if(type == 3)
    {
        D.push_back(new Node(Constants::ConditionalNode, font));
        D[D.size() - 1]->setTextString("Conditional");
    }
    if(type == 4)
    {
        D.push_back(new Node(Constants::OutputNode, font));
        D[D.size() - 1]->setTextString("Output");
    }
    if(type == 5)
    {
        if(isStopNode)
            return;
        D.push_back(new Node(Constants::StopNode, font));
        D[D.size() - 1]->setTextString("Stop");
        isStopNode = 1;
    }

    if(type == 6)
    {
        D.push_back(new Node(Constants::ReadNode, font));
        D[D.size() - 1]->setTextString("Read");
    }

    D[D.size() - 1]->setNodeCoordonates(sf::Vector2f{1000, 200});

}
int main()
{
    RenderWindow window(VideoMode(Constants::Width, Constants::Height), "Interschem", Style::Close | Style::Titlebar);
    initializareButoane(font);
    vector<Node*> nodes;
    nodes.clear();
    font.loadFromFile("Fonts\\Poppins\\Poppins-Regular.ttf");



//    sf::Vector2f coordA = sf::Vector2f{300, 300};
//    sf::Vector2f coordB = sf::Vector2f{500, 500};
    adauga_nod(nodes, Constants::StartNode);
    adauga_nod(nodes, Constants::ConditionalNode);
    nodes[0]->setNodeCoordonates(sf::Vector2f{300, 300});
    nodes[1]->setNodeCoordonates(sf::Vector2f{500, 500});



    bool hold = false;
    Vector2i oldPos;
    int target = -1;
    int emptyRectangle = -1;


    /** TEST EXPRESIE
    */
    initializare();
    char expresiDeTest[500];
    strcpy(expresiDeTest, "(    (       30*(-1)+ 9 /r A d( 9 ))) ^(32/(15 +1)) < 700 && cos(pi) < 0");
    cout << setprecision(5) << fixed;
    cout << Evalueaza_Expresie(expresiDeTest) << '\n';



    while (window.isOpen())
    {
        Event evnt;
        while (window.pollEvent(evnt))
        {
            if(evnt.type == Event::Closed)
            {
                window.close();
            }
            else if(evnt.type == Event::MouseButtonPressed)
            {
                if(evnt.mouseButton.button == Mouse::Left)
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
            nodes[target]->setNodeCoordonates(sf :: Vector2f{static_cast<float>(pozitieMouse.x), static_cast<float>(pozitieMouse.y)});
        }
        window.clear();
        DeseneazaPeEcran(window,nodes);
        window.display();
    }


    return 0;
}

#endif

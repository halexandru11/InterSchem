#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Constants.hpp"
using namespace sf;
using namespace std;

#define eps 0.000001
#define PI 3.14159265

sf::Font font;
bool isStartNode, isStopNode;

bool isInside(Vector2f MousePos, Node *q)
{
    Vector2f qOrigin = q->getNodeCoordonates(Constants::CoordNode);
    Vector2f qSize = q->hitbox.getSize();
    Vector2f susStanga = qOrigin;
    Vector2f josDreapta = qOrigin;
    susStanga.x -= qSize.x / 2;
    susStanga.y -= qSize.y / 2;
    josDreapta.x += qSize.x / 2;
    josDreapta.y += qSize.y / 2;
   // cout << MousePos.x << ' ' << MousePos.y << '\n';
    //cout << susStanga.x << ' ' << susStanga.y << '\n';
    //cout << josDreapta.x << ' ' << josDreapta.y << '\n';
    //cout << "\n\n";
    if(josDreapta.x >= MousePos.x && MousePos.x >= susStanga.x &&
        josDreapta.y >= MousePos.y && MousePos.y >= susStanga.y)
        {
            //cout << "GOOD\n";
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

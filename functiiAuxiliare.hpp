#pragma once

#include "Buttons.hpp"

using namespace sf;
using namespace std;

#define eps 0.000001
#define PI 3.14159265

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
    if(type == Constants::StartNode)
    {
        if(isStartNode)
            return;
        D.push_back(new Node(Constants::StartNode, font));
        D.back()->setTextString("Start");
        D.back()->setNodeCoordonates({180, 275});
        isStartNode = 1;
        StartSchema = D[D.size() - 1];
    }
    if(type == Constants::AssignNode)
    {
        D.push_back(new Node(Constants::AssignNode, font));
        D[D.size() - 1]->setTextString("Assign");
        D.back()->setNodeCoordonates({180, 330});
    }
    if(type == Constants::ConditionalNode)
    {
        D.push_back(new Node(Constants::ConditionalNode, font));
        D[D.size() - 1]->setTextString("Conditional");
        D.back()->setNodeCoordonates({200, 385});
    }
    if(type == Constants::ReadNode)
    {
        D.push_back(new Node(Constants::ReadNode, font));
        D[D.size() - 1]->setTextString("Read");
        D.back()->setNodeCoordonates({180, 440});
    }
    if(type == Constants::OutputNode)
    {
        D.push_back(new Node(Constants::OutputNode, font));
        D[D.size() - 1]->setTextString("Output");
        D.back()->setNodeCoordonates({180, 495});
    }
    if(type == Constants::StopNode)
    {
        if(isStopNode)
            return;
        D.push_back(new Node(Constants::StopNode, font));
        D[D.size() - 1]->setTextString("Stop");
        D.back()->setNodeCoordonates({180, 550});
        isStopNode = 1;
    }
}

void stergeToateLiniile(vector<Line>& lines, Node*& node) {
    for(int index = 0; index < int(lines.size()); ++index) {
        Node* parent = lines[index].getParent();
        Node* child = lines[index].getChild();
        if(child == node) {
            if(parent->urm == child) {
                parent->urm = NULL;
            }
            if(parent->urmTrue == child) {
                parent->urmTrue = NULL;
            }
            if(parent->urmFalse == child) {
                parent->urmFalse = NULL;
            }
        }
        if(parent == node or child == node) {
            lines.erase(lines.begin() + index);
            --index;
        }
    }
}

void stergeLinie(vector<Line>& lines, Node*& node, Constants::CoordType coordType) {
    for(int index = 0; index < int(lines.size()); ++index) {
        Node* parent = lines[index].getParent();
        Node* child = lines[index].getChild();
        if(node == parent) {
            if(node->urm == child and coordType == Constants::CoordOut) {
                node->urm = NULL;
                lines.erase(lines.begin() + index);
                --index;
            }
            if(node->urmTrue == child and coordType == Constants::CoordOutTrue) {
                node->urmTrue = NULL;
                lines.erase(lines.begin() + index);
                --index;
            }
            if(node->urmFalse == child and coordType == Constants::CoordOutFalse) {
                node->urmFalse = NULL;
                lines.erase(lines.begin() + index);
                --index;
            }
        }
    }
}

void ClearScreen(vector <Node*> &v, vector<Line>& lines)
{
    lines.clear();
    v.clear();
    isStartNode = false;
    isStopNode = false;
    StartSchema = NULL;
}

int isOkToRun()
{
    if(isStartNode == false and isStopNode == false) {
        return 0;
    }
    if(isStartNode == false) {
        return 1;
    }
    if(isStopNode == false) {
        return 2;
    }
    return 3;
}

void changeTab(int tab) {
    buttonOutPut.setBgColor(Color(44, 61, 27));
    buttonVariabile.setBgColor(Color(44, 61, 27));
    buttonCode.setBgColor(Color(44, 61, 27));
    switch(tab) {
    case 1:
        buttonOutPut.setBgColor(Color(163, 184, 81));
        break;
    case 2:
        buttonVariabile.setBgColor(Color(163, 184, 81));
        break;
    case 3:
        buttonCode.setBgColor(Color(163, 184, 81));
        break;
    }
    open_tab = tab;
}

pair<Node*, Node*> loopCorect() {
    for(Node*& node : nodes) {
        node->viz = false;
    }
    Node* n = StartSchema;
    while(n != NULL and n->viz == false) {
        n->viz = true;
        if(n->urm != NULL) {
            if(n->urm->viz == true and n->urm->nodeType != Constants::ConditionalNode) {
                cout << "Dead end\n";
                return {n, n->urm};
            }
            n = n->urm;
        }
    }

    cout << "Am ajuns la final\n";
    return {NULL, NULL};
}

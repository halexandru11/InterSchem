#pragma once

#include <bits/stdc++.h>
#include "Constants.hpp"
#include "Node.hpp"
#include "functiiAuxiliare.hpp"
#include "Line.hpp"
#define Dad v[i]
#define Kid v[a]
#define caracter E.text.unicode
string filePath = "output.txt";

void PrintNode(Node* p, ofstream &g)
{
    g << p->nodeType << '\n';
    g << p->getNodeCoordonates(Constants::CoordNode).x << ' ' << p->getNodeCoordonates(Constants::CoordNode).y << '\n';
    g << p->content << '\n';

}

void PrintEdges(vector <Node*> v, ofstream &g)
{
    for(auto p : v)
    {
        int q = -1;
        for(int i = 0; i < v.size(); ++i)
            if(p->urm == v[i])
            {
                q = i;
                break;
            }
        g << q << ' ';

        q = -1;
        for(int i = 0; i < v.size(); ++i)
            if(p->urmTrue == v[i])
            {
                q = i;
                break;
            }
        g << q << ' ';

        q = -1;
        for(int i = 0; i < v.size(); ++i)
            if(p->urmFalse == v[i])
            {
                q = i;
                break;
            }
        g << q << '\n';
    }
}


void ExportToFile(vector <Node*> v)
{
    RenderWindow fereastra_citire(VideoMode(1000, 150), "Export", Style::Close | Style::Titlebar);
    isPOPup = true;
    filePath = "";
    string taskk = "Introduceti numele fisierului + extenisa(optional si Path-ul acestuia):";
    setPopupText(taskk);
    while(fereastra_citire.isOpen())
    {
        Event E;
        while(fereastra_citire.pollEvent(E))
        {
            if(E.type == Event::Closed)
            {
                fereastra_citire.close();
            }
            else if(E.type == Event::TextEntered)
            {
                getInputPop(E);
                if(caracter == 13)
                {
                    filePath = inputPopUp.getString();
                    setPopupInputText("");
                    fereastra_citire.close();
                }
            }
        }
        fereastra_citire.clear();
        afiseazaPopup(fereastra_citire);
        fereastra_citire.display();
    }
    isPOPup = false;

    ofstream g(filePath);
    g << v.size() << '\n';
    for(int i = 0; i < v.size(); ++i)
        PrintNode(v[i],g);
    PrintEdges(v,g);
    g.close();
}

void EnterNode(ifstream &f, vector <Node*> &v)
{
    int type;
    float x,y;
    char buff[502];
    string ct;
    f >> type >> x >> y;
    f.get();
    f.get(buff, 501);
    for(int i = 0; i < strlen(buff); ++i)
        ct.push_back(buff[i]);
    Node*p;
    if(type == Constants::StartNode)
    {
        p = new Node(Constants::StartNode, font);
    }
    else if(type == Constants::AssignNode)
        p = new Node(Constants::AssignNode, font);
    else if(type == Constants::ConditionalNode)
        p = new Node(Constants::ConditionalNode, font);
    else if(type == Constants::OutputNode)
        p = new Node(Constants::OutputNode, font);
    else if(type == Constants::StopNode)
    {
        isStopNode = true;
        p = new Node(Constants::StopNode, font);
    }
    else if(type == Constants::ReadNode)
        p = new Node(Constants::ReadNode, font);
    p->setNodeCoordonates(Vector2f(x,y));
    p->setTextString(ct);
    //cout << type << ' ' << ' ' << y << ct << '\n';
    v.push_back(p);

    if(type == Constants::StartNode)
    {
        isStartNode = true;
        StartSchema = v.back();
    }
}

void setLines(ifstream &f, vector <Node*> &v, vector<Line>& linii)
{
    for(int i = 0; i < v.size(); ++i)
    {
        int a;
        f >> a ;
//        cout << a  << ' ';
        /*

        */
        if(a != -1)
        {
//        cout << v[i]->content << ' ' << v[a]->content << '\n';
            linii.push_back(Line(*Dad, *Kid, Constants::CoordType::CoordOut, Kid));
        }

        f >> a ;
//        cout << a  << ' ';
        if(a != -1)
        {
//        cout << v[i]->content << ' ' << v[a]->content << '\n';
            linii.push_back(Line(*Dad,*Kid,Constants::CoordType::CoordOutTrue,Kid));
        }

        f >> a ;
//        cout << a  << ' ';
        if(a != -1)
        {
//        cout << v[i]->content << ' ' << v[a]->content << '\n';
            linii.push_back(Line(*Dad,*Kid,Constants::CoordType::CoordOutFalse,Kid));
        }
//        cout << '\n';
    }
}



void ImportFromFile(vector <Node*> &v, vector<Line>& linii)
{
    RenderWindow fereastra_citire(VideoMode(1000, 150), "Import", Style::Close | Style::Titlebar);
    isPOPup = true;
    filePath = "";
    string taskk = "Introduceti numele fisierului + extenisa(optional si Path-ul acestuia):";
    setPopupText(taskk);
    while(fereastra_citire.isOpen())
    {
        Event E;
        while(fereastra_citire.pollEvent(E))
        {
            if(E.type == Event::Closed)
            {
                fereastra_citire.close();
            }
            else if(E.type == Event::TextEntered)
            {
                getInputPop(E);
                if(caracter == 13)
                {
                    filePath = inputPopUp.getString();
                    setPopupInputText("");
                    fereastra_citire.close();
                }
            }
        }
        fereastra_citire.clear();
        afiseazaPopup(fereastra_citire);
        fereastra_citire.display();
    }
    isPOPup = false;

    ifstream f(filePath);
    ClearScreen(v, linii);
    int lg;
    f >> lg;
    for(int i = 0; i < lg; ++i)
        EnterNode(f,v);
    setLines(f,v,linii);

    f.close();
}

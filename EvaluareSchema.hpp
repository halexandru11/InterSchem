#pragma once

#include "Evaluare.hpp"
#include "ui.hpp"
#include "functiiAuxiliare.hpp"
#include "code.hpp"


#define caracter E.text.unicode


using namespace std;
using namespace sf;

string OutputContent;
string OutputVariabile;

Node* RunStartNode(Node* p)
{
    OutputContent = "Output:\n";
    initializare();
    return p->urm;
}
Node* RunReadNode(Node* p)
{
    char s[500];
    strcpy(s, p->content);
    string variabilaNoua;
    for(int i = 0; i < int(strlen(s)) ; ++i)
        variabilaNoua.push_back(s[i]);
    datatype valoare = -1.234;

    //cout << "DESCHID FEREASTRA\n";
    RenderWindow fereastra_citire(VideoMode(1000, 150), "Citire", Style::Close | Style::Titlebar);
    isPOPup = true;
    string taskk = "Introduceti valoarea variabilei " + variabilaNoua + " :";
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
                    valoare = to_nr(inputPopUp.getString());
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


    adaugaVariabila(variabilaNoua, valoare);
    return p->urm;
}

Node* RunAssignNode(Node*p)
{
    char s[500];
    string variabila;
    char *w;
    strcpy(s, p->content);
    char q[strlen(s) + 50];
    int nq = 0;
    for(int i = 0; i < int(strlen(s)); ++i)
    {
        if(s[i] == ' ') continue;
        q[nq++] = s[i];
    }
    w = q;
    while(*w != '=' && *w != NULL)
    {
        variabila.push_back(*w);
        w++;
    }
    w++;
    char exp[500];
    strcpy(exp, w);
    datatype rezultat = Evalueaza_Expresie(exp);
    atribuieVariabila(variabila,rezultat);
    return p->urm;
}

Node* RunIfNode(Node*p)
{
    char s[500];
    string variabila;
    char *w;
    strcpy(s, p->content);
    w = s;
    datatype rezulatat =  Evalueaza_Expresie(w);
    if(rezulatat != 0)
        return p->urmTrue;
    return p->urmFalse;
}

Node* RunPrintNode(Node*p)
{
    char s[500];
    strcpy(s, p->content);
    if(s[0] ==  '\"')
    {
        int i = 1;
        while(s[i] !=  '\"')
        {
            OutputContent += s[i];
            i++;
        }
        OutputContent += '\n';
        OutputText.setString(OutputContent);
    }
    else
    {
        datatype rezz = Evalueaza_Expresie(s);
        long long q =  rezz;
        cout << rezz << ' ' <<  q << '\n';
        if(abs(abs(rezz) - 1.0000 * abs(q) )< eps)
            OutputContent += to_string(q) + '\n';
        else
            OutputContent += to_string(rezz) + '\n';
        OutputText.setString(OutputContent);
    }
    return p->urm;
}

Node* RunNode(Node *p)
{
    if(p->nodeType == Constants::StartNode)
        return RunStartNode(p);
    if(p->nodeType == Constants::AssignNode)
        return RunAssignNode(p);
    if(p->nodeType == Constants::ConditionalNode)
        return RunIfNode(p);
    if(p->nodeType == Constants::OutputNode)
        return RunPrintNode(p);
    if(p->nodeType == Constants::ReadNode)
        return RunReadNode(p);
    return nullptr;
}

void clearSchema(Node* p) {
    if(p->isActive() == false) {
        return;
    }
    p->resetNode();
    if(p->urm) clearSchema(p->urm);
    if(p->urmTrue) clearSchema(p->urmTrue);
    if(p->urmFalse) clearSchema(p->urmFalse);
}

int delay = 400;

void RunSchema(Node *p, RenderWindow& window, const vector<Node*>& nodes, const vector<Line>& lines)
{
    if(!isOkToRun())
    {
        cout << "NU SUNT START/STOP\n";
        return;
    }
    Node *dublura = p;
    clearSchema(p);
    Clock myclock;
    Time mytime;
    int target = -1;
    bool hold = false;
    while(p != NULL) {
        p->activateNode();
        window.clear(Color(38, 43, 19));
        DeseneazaPeEcran(window, nodes, lines);
        window.display();
        if(p->nodeType == Constants::StopNode) {
            mytime = microseconds(0);
            while(mytime.asMilliseconds() < delay) {
                mytime += myclock.restart();
            }
            p->deactivateNode();
            window.clear(Color(38, 43, 19));
            DeseneazaPeEcran(window, nodes, lines);
            window.display();
            return;
        }
        ///colorez nodul curent cumva
        Node* child = RunNode(p);

        OutputVariabile = "Variabile:\n";
        for(auto it : variabileCod)
        {
            OutputVariabile += it.first + " = ";
            cout << it.first << ' ' << to_string(variabile[it.second])  << '\n';
            OutputVariabile += to_string(variabile[it.second]) + "\n";
        }
        VariabileText.setString(OutputVariabile);

        Line line(p, Constants::CoordOut, window);
        if(child == p->urm) {
            line = Line(*p, *child, Constants::CoordOut, child);
        }
        else if(child == p->urmTrue) {
            line = Line(*p, *child, Constants::CoordOutTrue, child);
        }
        else if(child == p->urmFalse) {
            line = Line(*p, *child, Constants::CoordOutFalse, child);
        }

        for(size_t times = 0; times < line.getRepTimes(); ++times) {
            mytime = microseconds(0);
            while(mytime.asMilliseconds() < delay) {
                Event evnt;
                while (window.pollEvent(evnt)) {
                    if(evnt.type == Event::Closed) {
                        window.close();
                        return;
                    }
                    else if(evnt.type == Event::MouseButtonPressed) {
                        if(evnt.mouseButton.button == Mouse::Left) {
                            Vector2f pos(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
                            hold = true;
                            for(size_t i = 0; i < nodes.size(); ++i) {
                                if(isInside(pos, nodes[i])) {
                                    target = i;
                                    break;
                                }
                            }

                            if(isInsideButton(pos, buttonDelay200)) {
                                buttonDelay200.setBgColor(Color(163, 184, 81));
                                buttonDelay400.setBgColor(Color(95, 107, 47));
                                buttonDelay700.setBgColor(Color(95, 107, 47));
                                buttonDelay1200.setBgColor(Color(95, 107, 47));
                                delay = 200;
                            }
                            else if(isInsideButton(pos, buttonDelay400)) {
                                buttonDelay200.setBgColor(Color(95, 107, 47));
                                buttonDelay400.setBgColor(Color(163, 184, 81));
                                buttonDelay700.setBgColor(Color(95, 107, 47));
                                buttonDelay1200.setBgColor(Color(95, 107, 47));
                                delay = 400;
                            }
                            else if(isInsideButton(pos, buttonDelay700)) {
                                buttonDelay200.setBgColor(Color(95, 107, 47));
                                buttonDelay400.setBgColor(Color(95, 107, 47));
                                buttonDelay700.setBgColor(Color(163, 184, 81));
                                buttonDelay1200.setBgColor(Color(95, 107, 47));
                                delay = 700;
                            }
                            else if(isInsideButton(pos, buttonDelay1200)) {
                                buttonDelay200.setBgColor(Color(95, 107, 47));
                                buttonDelay400.setBgColor(Color(95, 107, 47));
                                buttonDelay700.setBgColor(Color(95, 107, 47));
                                buttonDelay1200.setBgColor(Color(163, 184, 81));
                                delay = 1200;
                            }
                            else if(isInsideButton(pos, buttonOutPut)) {
                                buttonOutPut.setBgColor(Color(163, 184, 81));
                                buttonVariabile.setBgColor(Color(44, 61, 27));
                                buttonCode.setBgColor(Color(44, 61, 27));
                                open_tab = 1;
                            }
                            else if(isInsideButton(pos, buttonVariabile)) {
                                buttonOutPut.setBgColor(Color(44, 61, 27));
                                buttonVariabile.setBgColor(Color(163, 184, 81));
                                buttonCode.setBgColor(Color(44, 61, 27));
                                open_tab = 2;
                            }
                            else if(isInsideButton(pos, buttonCode)) {
                                buttonOutPut.setBgColor(Color(44, 61, 27));
                                buttonVariabile.setBgColor(Color(44, 61, 27));
                                buttonCode.setBgColor(Color(163, 184, 81));
                                writeCode(StartSchema);
                                open_tab = 3;
                            }
                            else if(isInsideButton(pos, buttonRun)) {
                                return;
                            }
                        }

                    }
                    else if(evnt.type == Event::MouseButtonReleased)
                    {
                        target = -1;
                        hold = false;
                    }
                }
                if(target != -1 and hold == true) {
                    float horOffset = nodes[target]->hitbox.getLocalBounds().width / 2;
                    float verOffset = nodes[target]->hitbox.getLocalBounds().height / 2;

                    Vector2i pozitieMouse = Mouse::getPosition(window);
                    Vector2f coordMe = Vector2f{float(pozitieMouse.x), float(pozitieMouse.y)};
                    coordMe.x = max(coordMe.x, Constants::BenchLeft + horOffset);
                    coordMe.x = min(coordMe.x, Constants::BenchLeft + Constants::BenchWidth - horOffset);
                    coordMe.y = max(coordMe.y, verOffset);
                    coordMe.y = min(coordMe.y, Constants::Height - verOffset);
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
                mytime += myclock.restart();
            }
            p->deactivateNode();
            if(child != NULL)
                line.updateLineColor();
            window.clear(Color(38, 43, 19));
            DeseneazaPeEcran(window, nodes, lines);
            if(child != NULL)
                window.draw(&line.getLine(window)[0], line.getLine(window).size(), Lines);
            window.display();
        }
        mytime = microseconds(0);
        while(mytime.asMilliseconds() < delay) {
            mytime += myclock.restart();
        }
        p = child;
//        cout << p->nodeType << '\n';
        /// + delay de cateva secunde + modificare delay
    }

    p = dublura;
}

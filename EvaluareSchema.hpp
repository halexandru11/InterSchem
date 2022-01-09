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
map<string, bool> modificat;

Node* RunStartNode(Node* p)
{
    if(abandon) {
        p->setColor(Color::Red, Color::White);
        return nullptr;
    }
    OutputContent = "";
    initializare();
    return p->urm;
}
Node* RunReadNode(Node* p)
{

    if(abandon) {
        p->setColor(Color::Red, Color::White);
        return nullptr;
    }
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
    modificat[variabilaNoua] = true;

    adaugaVariabila(variabilaNoua, valoare);
    return p->urm;
}

Node* RunAssignNode(Node*p)
{

    if(abandon) {
        p->setColor(Color::Red, Color::White);
        return nullptr;
    }
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
    while(*w != '=' && *w != NULL) {
        variabila.push_back(*w);
        w++;
    }
    modificat[variabila] = true;
    w++;
    char exp[500];
    strcpy(exp, w);
    datatype rezultat = Evalueaza_Expresie(exp);
    atribuieVariabila(variabila, rezultat);
    return p->urm;
}

Node* RunIfNode(Node*p)
{

    if(abandon) {
        p->setColor(Color::Red, Color::White);
        return nullptr;
    }
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

    if(abandon) {
        p->setColor(Color::Red, Color::White);
        return nullptr;
    }
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

    if(abandon) {
        p->setColor(Color::Red, Color::White);
        return nullptr;
    }
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

int delay = 400;

void RunSchema(Node *p, RenderWindow& window, vector<Node*>& nodes, vector<Line>& lines)
{
    OutputText.setString("");
    OutputText.setFillColor(Color::White);
    VariabileText.clear();
    nrVariabile = 0;
    switch(isOkToRun()) {
    case 0:
        changeTab(1);
        OutputText.setString("EROARE:\nLipsesc nodurile de Start\nsi de Stop.");
        OutputText.setFillColor(Color(255, 160, 0));
        buttonStart.setBgColor(sf::Color(200, 100, 0));
        buttonEnd.setBgColor(sf::Color(200, 100, 0));
        colorSchema(Color(240, 80, 80), Color(220, 220, 220));
        setAllErrorLines();
        return;
    case 1:
        changeTab(1);
        OutputText.setString("EROARE:\nLipseste nodul de Start.");
        OutputText.setFillColor(Color(255, 160, 0));
        buttonStart.setBgColor(sf::Color(200, 100, 0));
        colorSchema(Color(240, 80, 80), Color(220, 220, 220));
        setAllErrorLines();
        return;
    case 2:
        changeTab(1);
        OutputText.setString("EROARE:\nLipseste nodul de Stop.");
        OutputText.setFillColor(Color(255, 160, 0));
        buttonEnd.setBgColor(sf::Color(200, 100, 0));
        colorSchema(Color(240, 80, 80), Color(220, 220, 220));
        setAllErrorLines();
        return;
    }
    pair<Node*, Node*> res = loopCorect();
    if(res.first != NULL) {
        changeTab(1);
        OutputText.setString("EROARE:\nDaca doriti sa creati o\nstructura repetitiva trebuie\nsa faceti legatura catre un\nNod Conditional.");
        OutputText.setFillColor(Color(255, 160, 0));
        setErrorLine(res.first, res.second);
        return;
    }
    if(!ajungeLaStop(StartSchema)) {
        changeTab(1);
        OutputText.setString("EROARE:\nToate drumurile trebuie sa\najunga in nodul Stop.");
        OutputText.setFillColor(Color(255, 160, 0));
        colorSchema(Color(240, 80, 80), Color(220, 220, 220));
        setAllErrorLines();
        return;
    }
    Node *dublura = p;
    clearSchema();
    Clock myclock;
    Time mytime;
    int target = -1;
    bool hold = false;
    while(p != NULL) {
        p->activateNode();
        window.clear(Color(38, 43, 19));
        leftBanner.setFillColor(Color(38, 43, 19));
        rightBanner.setFillColor(Color(38, 43, 19));
        DeseneazaPeEcran(window, nodes, lines);
        window.display();
        if(p->nodeType == Constants::StopNode) {
            mytime = microseconds(0);
            while(mytime.asMilliseconds() < delay) {
                mytime += myclock.restart();
            }
            p->deactivateNode();
            window.clear(Color(38, 43, 19));
            leftBanner.setFillColor(Color(38, 43, 19));
            rightBanner.setFillColor(Color(38, 43, 19));
            DeseneazaPeEcran(window, nodes, lines);
            window.display();
            return;
        }
        ///colorez nodul curent cumva
        Node* child = RunNode(p);
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

            VariabileText.clear();
            float yPos = 50.0f;
            for(auto it : variabileCod) {
                OutputVariabile = "";
                OutputVariabile += it.first + "=";
                double val = variabile[it.second];
                int flr = val;
                if( abs(val - flr)  < eps)
                    OutputVariabile += to_string(flr) + "\n";
                else
                    OutputVariabile += to_string(variabile[it.second]) + "\n";

                Text var;
                var.setFont(font);
                var.setCharacterSize(17);
                var.setPosition(Vector2f(1040.0f, yPos));
                var.setString(OutputVariabile);
                if(modificat[it.first]) {
                    var.setFillColor(Color(255, 160, 0));
                }
                else {
                    var.setFillColor(Color::White);
                }
                yPos += 20;
                VariabileText.push_back(var);
            }

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
                }
                mytime += myclock.restart();
            }
            p->deactivateNode();
            if(child != NULL)
                line.updateLineColor();

            for(auto& [var, state] : modificat) {
                state = false;
            }

            window.clear(Color(38, 43, 19));
            leftBanner.setFillColor(Color(38, 43, 19));
            rightBanner.setFillColor(Color(38, 43, 19));
            DeseneazaPeEcran(window, nodes, lines);
            if(child != NULL)
                line.draw(window);
            window.display();
            if(abandon) {
                OutputText.setString(errorString);
                OutputText.setFillColor(Color(255, 160, 0));
                changeTab(1);
                p->setColor(Color(240, 80, 80), Color(220, 220, 220));
                return;
            }
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

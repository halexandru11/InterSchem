#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Constants.hpp"
#include "Evaluare.hpp"
#include "Node.hpp"
#include "pop_ups.hpp"

using namespace std;
using namespace sf;

Node* RunStartNode(Node* p)
{
    return p->urm;
}
Node* RunReadNode(Node* p)
{
    char s[500];
    strcpy(s, p->content);
    string variabilaNoua;
    for(int i = 0; i < strlen(s) ; ++i)
        variabilaNoua.push_back(s[i]);
    datatype valoare = -1.234;



    string q =

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
    for(int i = 0; i < strlen(s); ++i)
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
            cout << s[i];
            i++;
        }
    }
    else
        cout << Evalueaza_Expresie(s);
    cout << '\n';
    return p->urm;
}

Node* RunNode(Node *p)
{
    if(p->nodeType == 1)
        return RunStartNode(p);
    if(p->nodeType == 2)
        return RunAssignNode(p);
    if(p->nodeType == 3)
        return RunIfNode(p);
    if(p->nodeType == 4)
        return RunPrintNode(p);
    return nullptr;
}

void RunSchema(Node *p)
{
    while(p != NULL)
    {
        ///colorez nodul curent cumva
        cout << p->nodeType << '\n';
        p = RunNode(p);
        /// + delay de cateva secunde + modificare delay
    }
}

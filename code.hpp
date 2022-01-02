#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Constants.hpp"
#include "Evaluare.hpp"
#include "Node.hpp"
#include "EvaluareSchema.hpp"
#include "Buttons.hpp"
using namespace sf;
using namespace std;

string code = "Code:\n";
string tabb =  "   ";
int nr_tabs = 1;
Node* common;

void putTabs()
{
    for(int i = 1; i <= nr_tabs; ++i)
        code += tabb;
}

void CodeSchema(Node *p, Node *stopp);
void DFS(Node *p, int q)
{
    if(p == NULL || (q == 0 && p->vizT == 1) || (q == 1 && p->vizF == 1) || common!= NULL)
        return;
    if(q == 0)
        p->vizT = 1;
    else
        p->vizF = 1;

    if(p->vizT && p->vizF)
    {
        common = p;
        return;
    }
    if(p->nodeType == Constants::NodeType::ConditionalNode)
    {
        DFS(p->urmTrue, q);
        DFS(p->urmFalse, q);
    }
    else
        DFS(p->urm, q);

}

Node* PrintStartNode(Node *p)
{
    return p->urm;
}
Node* PrintAssignNode(Node *p)
{
    putTabs();
    for(int i = 0; i < strlen(p->content); ++i)
        code += p->content[i];
    code += ";\n";
    return p->urm;
}
Node* PrintIfNode(Node *p)
{
    for(int i = 0; i < nodes.size(); ++i)
    {
        nodes[i]->vizF = 0;
        nodes[i]->vizT = 0;
    }
    common = NULL;
    DFS(p->urmTrue, 0);
    common = NULL;
    DFS(p->urmFalse, 1);
    putTabs();
    code += "if(";
    for(int i = 0; i < strlen(p->content); ++i)
        code += p->content[i];
    code += ")\n";
    putTabs();
    code += "{\n";
    nr_tabs++;
    CodeSchema( p->urmTrue, common);
    nr_tabs--;
    putTabs();
    code += "}\n";

    putTabs();
    code+= "else{\n";
    nr_tabs++;
    CodeSchema( p->urmFalse, common);
    nr_tabs--;
    putTabs();
    code += "}\n";

    return common;
}
Node* PrintPrintNode(Node *p)
{
    putTabs();
    code += "cout << ";

    for(int i = 0; i < strlen(p->content); ++i)
        code += p->content[i];
    code += " << '\\n';\n";
    return p->urm;}
Node* PrintReadNode(Node *p)
{
    putTabs();
    code += "cin >> ";

    for(int i = 0; i < strlen(p->content); ++i)
        code += p->content[i];
    code += ";\n";
    return p->urm;
}


Node* RunNode2(Node *p)
{
    if(p->nodeType == 1)
        return PrintStartNode(p);
    if(p->nodeType == 2)
        return PrintAssignNode(p);
    if(p->nodeType == 3)
        return PrintIfNode(p);
    if(p->nodeType == 4)
        return PrintPrintNode(p);
    if(p->nodeType == 6)
        return PrintReadNode(p);
    return nullptr;
}

void CodeSchema(Node *p, Node *stopp)
{
    while(p != stopp)
    {
        p = RunNode2(p);
    }
}
void writeCode(Node *p)
{
    CodText.setCharacterSize(10);
    code = "Cod:\n";
    code += "#include<iostream>\nusing namespace std;\n";
    if(is_expo)
        code += "double logpow(double a, double b)\n{\n    double r = 1;\n    int b_floored = b;\n    if(b - b_floored >= eps)\n    {\n        perror(\"Exponentiala cu exponent real\");        exit(1);\n    }\n    if(b_floored < 0)\n    {\n        a = 1 / a;\n        b_floored = -b_floored;\n    }\n    while(b_floored)\n    {\n        if(b_floored & 1) r *= a;\n        a *= a;\n        b_floored >>= 1;\n    }\n    return r;\n}";
    if(variabileCod.size() > 0)
    {
        code += "double";
        map <string, bool> isIn;
        for(auto it : nodes)
            if(it->nodeType == Constants::NodeType::ReadNode || it->nodeType == Constants::NodeType::AssignNode )
            {
                string varr;
                for(int i = 0; i < strlen(it->content); ++i)
                {
                    if(it->content[i] == '=') break;
                    if(it->content[i] != ' ')
                        varr += it->content[i];
                }
                if(isIn.find(varr) == isIn.end())
                {
                    isIn[varr] = 1;
                    code += " " + varr + ",";
                }

            }
        /*
        for(auto it : variabileCod)
            code += " " + it.first + ",";
        */
        code.pop_back();
        code += ";";
    }
    code += "\nint main()\n{\n";
    CodeSchema(StartSchema, NULL);
    code += "   return 0;\n}";
    CodText.setString(code);
    is_expo = 0;
    ofstream CodeFile("CodC++.cpp");
    CodeFile << code.substr(5);
    CodeFile.close();
}

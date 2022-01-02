#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Constants.hpp"
#include "Node.hpp"
#include "pop_ups.hpp"
using namespace sf;
using namespace std;

Node * StartSchema;
vector <Text> ButtonText;
RectangleShape workbench(Vector2f(900.0f,720.0f));
RectangleShape buttonStart(Vector2f(125.0f,50.0f));

Text OutputText;
Text VariabileText;
Text CodText;
CircleShape circle = CircleShape(3, 14);
RectangleShape buttonAssign(Vector2f(125.0f,50.0f));


RectangleShape buttonCond(Vector2f(125.0f,50.0f));

RectangleShape buttonRead(Vector2f(125.0f,50.0f));

RectangleShape buttonOut(Vector2f(125.0f,50.0f));

RectangleShape buttonEnd(Vector2f(125.0f,50.0f));

RectangleShape buttonRun(Vector2f(125.0f,50.0f));

RectangleShape buttonImport(Vector2f(125.0f,50.0f));

RectangleShape buttonExport(Vector2f(125.0f,50.0f));
RectangleShape buttonClear(Vector2f(125.0f,30.0f));

RectangleShape buttonOutPut(Vector2f(80.0f,30.0f));
RectangleShape buttonVariabile(Vector2f(80.0f,30.0f));
RectangleShape buttonCode(Vector2f(80.0f,30.0f));

void initializareButoane(Font &font)
{

    OutputText.setFont(font);
    OutputText.setCharacterSize(17);
    OutputText.setFillColor(Color::White);
    OutputText.setPosition(Vector2f(1040.0f,50.0f));
    VariabileText = OutputText;
    CodText = OutputText;
    OutputText.setString("Output:\n");
    VariabileText.setString("Variabile:\n");
    CodText.setString("Cod:\n");


    popupSetup();
    circle.setFillColor(Color::Cyan);
    circle.setOrigin(circle.getRadius(), circle.getRadius());


    workbench.setFillColor(Color(59,71,57,255));
    workbench.setOrigin(0.0f, 0.0f);
    workbench.setPosition(125.0f, 0.0f);

    buttonClear.setFillColor(Color::Red);
    buttonClear.setOrigin(62.5f, 15.0f);
    buttonClear.setPosition(62.5f, 15.0f);

    buttonStart.setFillColor(Color::Blue);
    buttonStart.setOrigin(62.5f, 25.0f);
    buttonStart.setPosition(62.5f, 75.0f);

    buttonAssign.setFillColor(Color::Blue);
    buttonAssign.setOrigin(62.5f, 25.0f);
    buttonAssign.setPosition(62.5f, 150.0f);

    buttonCond.setFillColor(Color::Blue);
    buttonCond.setOrigin(62.5f, 25.0f);
    buttonCond.setPosition(62.5f, 225.0f);

    buttonRead.setFillColor(Color::Blue);
    buttonRead.setOrigin(62.5f, 25.0f);
    buttonRead.setPosition(62.5f, 300.0f);

    buttonOut.setFillColor(Color::Blue);
    buttonOut.setOrigin(62.5f, 25.0f);
    buttonOut.setPosition(62.5f, 375.0f);

    buttonEnd.setFillColor(Color::Blue);
    buttonEnd.setOrigin(62.5f, 25.0f);
    buttonEnd.setPosition(62.5f, 450.0f);


    buttonRun.setFillColor(Color::Red);
    buttonRun.setOrigin(62.5f, 25.0f);
    buttonRun.setPosition(62.5f, 525.0f);

    buttonExport.setFillColor(Color::Red);
    buttonExport.setOrigin(62.5f, 25.0f);
    buttonExport.setPosition(62.5f, 600.0f);

    buttonImport.setFillColor(Color::Red);
    buttonImport.setOrigin(62.5f, 25.0f);
    buttonImport.setPosition(62.5f, 675.0f);


    buttonOutPut.setFillColor(Color::Red);
    buttonOutPut.setOrigin(40.0f, 15.0f);
    buttonOutPut.setPosition(1025.0f + 40.0f, 15.0f);

    buttonVariabile.setFillColor(Color::Green);
    buttonVariabile.setOrigin(40.0f, 15.0f);
    buttonVariabile.setPosition(1025.0f + 120.0f, 15.0f);

    buttonCode.setFillColor(Color::Blue);
    buttonCode.setOrigin(40.0f, 15.0f);
    buttonCode.setPosition(1025.0f + 200.0f, 15.0f);

    Text text;
    text.setFont(font);
    text.setCharacterSize(17);
    text.setFillColor(Color::White);

    text.setPosition(35.0f, 7.0f);
    text.setString("Clear");
    ButtonText.push_back(text);

    text.setPosition(10.0f, 63.0f);
    text.setString("Nod Start");
    ButtonText.push_back(text);

    text.setPosition(10.0f, 138.0f);
    text.setString("Nod Assign");
    ButtonText.push_back(text);

    text.setPosition(10.0f, 213.0f);
    text.setString("Nod Cond");
    ButtonText.push_back(text);

    text.setPosition(10.0f, 288.0f);
    text.setString("Nod Read");
    ButtonText.push_back(text);

    text.setPosition(10.0f, 363.0f);
    text.setString("Nod Output");
    ButtonText.push_back(text);


    text.setPosition(10.0f, 438.0f);
    text.setString("Nod Stop");
    ButtonText.push_back(text);


    text.setPosition(10.0f, 513.0f);
    text.setString("RUN");
    ButtonText.push_back(text);

    text.setPosition(10.0f, 588.0f);
    text.setString("Export");
    ButtonText.push_back(text);

    text.setPosition(10.0f, 663.0f);
    text.setString("Import");
    ButtonText.push_back(text);


    text.setPosition(1035.0f, 3.5f);
    text.setString("Output");
    ButtonText.push_back(text);


    text.setPosition(1026.0f + 80.0f, 3.5f);
    text.setString("Variabile");
    ButtonText.push_back(text);
    ///cout << ButtonText.size()<< '


    text.setPosition(1046.0f + 160.0f, 3.5f);
    text.setString("Cod");
    ButtonText.push_back(text);
}

void afisareButoane(RenderWindow &window)
{
        window.draw(workbench);
        window.draw(buttonStart);
        window.draw(buttonAssign);
        window.draw(buttonCond);
        window.draw(buttonOut);
        window.draw(buttonEnd);
        window.draw(buttonRead);
        window.draw(buttonRun);
        if(open_tab == 1)
            window.draw(OutputText);
        else if(open_tab == 2)
            window.draw(VariabileText);
        else if(open_tab == 3)
            window.draw(CodText);        window.draw(buttonExport);
        window.draw(buttonImport);
        window.draw(buttonClear);
        window.draw(buttonOutPut);
        window.draw(buttonVariabile);
        window.draw(buttonCode);
        for(int i = 0; i < ButtonText.size(); ++i)
            window.draw(ButtonText[i]);
}

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
    //cout << MousePos.x << ' ' << MousePos.y << '\n';
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

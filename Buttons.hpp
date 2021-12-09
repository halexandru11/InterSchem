#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Constants.hpp"
using namespace sf;
using namespace std;

vector <Text> ButtonText;
RectangleShape workbench(Vector2f(900.0f,720.0f));
RectangleShape buttonStart(Vector2f(125.0f,50.0f));

CircleShape circle = CircleShape(3, 14);
RectangleShape buttonAssign(Vector2f(125.0f,50.0f));


RectangleShape buttonCond(Vector2f(125.0f,50.0f));

RectangleShape buttonRead(Vector2f(125.0f,50.0f));

RectangleShape buttonOut(Vector2f(125.0f,50.0f));

RectangleShape buttonEnd(Vector2f(125.0f,50.0f));

void initializareButoane(Font &font)
{

    circle.setFillColor(Color::Cyan);
    circle.setOrigin(circle.getRadius(), circle.getRadius());


    workbench.setFillColor(Color(59,71,57,255));
    workbench.setOrigin(0.0f, 0.0f);
    workbench.setPosition(125.0f, 0.0f);

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
    buttonOut.setPosition(62.5f, 374.0f);

    buttonEnd.setFillColor(Color::Blue);
    buttonEnd.setOrigin(62.5f, 25.0f);
    buttonEnd.setPosition(62.5f, 450.0f);

    Text text;
    text.setFont(font);
    text.setCharacterSize(17);
    text.setFillColor(Color::White);

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

    cout << ButtonText.size()<< '\n';
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
        for(int i = 0; i < ButtonText.size(); ++i)
            window.draw(ButtonText[i]);
}

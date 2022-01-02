#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#define caracter evnt.text.unicode

using namespace std;
using namespace sf;

bool isPOPup = false;
int PopType;

RectangleShape popUpBG(Vector2f(1000.0f,150.0f));;
Text popupText;
Text inputPopUp;
string bufferp;

void setPopupText(string s)
{
    popupText.setString(s);
    float h = popupText.getGlobalBounds().height;
    float w = popupText.getGlobalBounds().width;
    popupText.setOrigin(w / 2, h / 2);
    popupText.setPosition( Vector2f(1000.0f / 2.0f, 150.0f / 2.0f - 50.0f)  );

}

void setPopupInputText(string s)
{
    inputPopUp.setString(s);
    float h = inputPopUp.getGlobalBounds().height;
    float w = inputPopUp.getGlobalBounds().width;
    inputPopUp.setOrigin(w / 2, h / 2);
    inputPopUp.setPosition( Vector2f(1000.0f / 2.0f, 150.0f / 2.0f )  );

}

void popupSetup()
{
    popupText.setFont(font);
    popupText.setCharacterSize(17);
    popupText.setFillColor(Color::Black);

    inputPopUp.setFont(font);
    inputPopUp.setCharacterSize(17);
    inputPopUp.setFillColor(Color::Black);

    popUpBG.setOrigin(Vector2f(500.0f,75.0f));
    popUpBG.setPosition(Vector2f(1000.0f/ 2.0f , 150.0f / 2.0f ));
}

void afiseazaPopup(RenderWindow &window)
{
    window.draw(popUpBG);
    window.draw(popupText);
    window.draw(inputPopUp);
}



inline void getInputPop(Event &evnt)
{
    if(isPOPup == false)
        return;
    if(caracter == 8)
    {
        if(bufferp.size() > 0)
            bufferp.pop_back();
        setPopupInputText(bufferp);
    }
    else if(caracter == 13)
    {
        setPopupInputText(bufferp);
        bufferp.clear();
        isPOPup = 0;
    }
    else
    {
        bufferp.push_back(caracter);
        setPopupInputText(bufferp);
    }
    //cout << bufferp << '\n';
}

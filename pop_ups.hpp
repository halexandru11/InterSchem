#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#define caracter evnt.text.unicode

using namespace std;
using namespace sf;

bool isPOPup = false;
int PopType;

RectangleShape popUpBG(Vector2f(1000.0f,150.0f));
RectangleShape border;
Text popupText;
Text inputPopUp;
string bufferp;

void setBorder() {
    border = RectangleShape(Vector2f(600, 40));
    border.setPosition(200, 60);
}

void setPopupText(string s)
{
    popupText.setString(s);
    float h = popupText.getGlobalBounds().height;
    float w = popupText.getGlobalBounds().width;
    popupText.setOrigin(w / 2, h / 2);
    popupText.setPosition( Vector2f(1000.0f / 2.0f, 150.0f / 2.0f - 50.0f) );

    setBorder();
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
    popupText.setFillColor(Color::White);

    inputPopUp.setFont(font);
    inputPopUp.setCharacterSize(17);
    inputPopUp.setFillColor(Color::Black);

    popUpBG.setOrigin(Vector2f(500.0f,75.0f));
    popUpBG.setPosition(Vector2f(1000.0f/ 2.0f , 150.0f / 2.0f ));
    popUpBG.setFillColor(Color(77, 157, 36));
}

void afiseazaPopup(RenderWindow &window)
{
    window.draw(popUpBG);
    window.draw(border);
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

void HelpPopUp()
{
    RenderWindow windowHelp(VideoMode(1000, 800), "Help", Style::Close | Style::Titlebar);

    auto imageIcon = sf::Image{};
    imageIcon.loadFromFile("ICON3.png");
    windowHelp.setIcon(imageIcon.getSize().x, imageIcon.getSize().y, imageIcon.getPixelsPtr());

    Text helpText;
    Text Trademarkk;
    helpText.setFont(font);
    helpText.setCharacterSize(17);
    helpText.setFillColor(Color::White);
    helpText.setPosition(Vector2f(150.0f, 430.0f));
///    helpText.setStyle(sf::Text::Bold);
    Texture imagineBG;
    imagineBG.loadFromFile("ICON2.png");
    sf :: Sprite imag(imagineBG);
    imag.setPosition(Vector2f(280.0f, 0.0f));
    imag.setOrigin(Vector2f(0.0f, 0.0f));
    imag.scale(Vector2f(0.7f, 0.7f));
    Trademarkk = helpText;
    string message ="                                                                  Help\n";
    message += "Butoanele se actioneaza cu Click Stanga\n";
    message += "Nodurile se misca cu drag&drop\n";
    message += "Conectarea acestora se face astfel: Ctrl+Click Stanga(se selecteaza primul nod,\n";
    message += "apoi nodul urmator; selectia se anuleaza daca se face click pe spatiul gol)\n";
    message += "Pentru a edita un nod se apasa Click Dreapta pe el, si apoi se poate tasta\n";
    message += "Pentru a termina editarea se apasa tasta Enter\n";
    message += "Pentru a sterge un nod se foloseste Click3(click-ul de pe Scroll)\n";
    helpText.setString(message);
    Trademarkk.setString("Proiect realizat de Hritcan Alexandru & Vamanu Petru");
    Trademarkk.setPosition(Vector2f(270,780));
    while(windowHelp.isOpen())
    {
        Event E;
        while(windowHelp.pollEvent(E))
        {
            if(E.type == Event::Closed)
            {
                windowHelp.close();
            }
        }
        windowHelp.clear(Color(90,120,50));
        windowHelp.draw(imag);
        windowHelp.draw(helpText);
        windowHelp.draw(Trademarkk);
        windowHelp.display();
    }
}


#pragma once

#include "pop_ups.hpp"

using namespace sf;
using namespace std;

struct Button {
public:
    Button(Vector2f size) {
        shape.setSize(size);
        text.setFont(font);
        text.setCharacterSize(17);
        text.setFillColor(Color::White);
    }

    void init(Vector2f size = Vector2f(0, 0),
              Vector2f pos = Vector2f(0, 0),
              Vector2f textPos = Vector2f(0, 0),
              string textString = "",
              unsigned int textSize = 17,
              float outlineThiskness = -2,
              Color backgroundColor = Color::Blue,
              Color outlineColor = Color::White,
              Color textColor = Color::White) {
        shape.setSize(size);
        shape.setPosition(pos);
        shape.setFillColor(backgroundColor);
        shape.setOutlineColor(outlineColor);
        shape.setOutlineThickness(outlineThiskness);
        text.setString(textString);
        text.setCharacterSize(textSize);
        text.setFillColor(textColor);
        setTextPosition(pos);
    }

    void draw(RenderWindow& window) {
        window.draw(shape);
        window.draw(text);
    }
public:
    RectangleShape shape;
    Text text;

private:
    void setTextPosition(Vector2f pos) {
        pos += Vector2f(10, shape.getLocalBounds().height/2 - 10);
        text.setPosition(pos);
    }
};

Node* StartSchema;
Text OutputText;

RectangleShape workbench    (Vector2f(900.0f,720.0f));

Button buttonStart  (Vector2f(125.0f, 50.0f));
Button buttonAssign (Vector2f(125.0f, 50.0f));
Button buttonCond   (Vector2f(125.0f, 50.0f));
Button buttonRead   (Vector2f(125.0f, 50.0f));
Button buttonOut    (Vector2f(125.0f, 50.0f));
Button buttonEnd    (Vector2f(125.0f, 50.0f));
Button buttonRun    (Vector2f(125.0f, 50.0f));
Button buttonImport (Vector2f(125.0f, 50.0f));
Button buttonExport (Vector2f(125.0f, 50.0f));
Button buttonClear  (Vector2f(125.0f, 30.0f));

void initializareButoane(Font &font)
{
    OutputText.setFont(font);
    OutputText.setCharacterSize(17);
    OutputText.setFillColor(Color::White);
    OutputText.setPosition(Vector2f(1040.0f,30.0f));
    OutputText.setString("Output:\n");


    popupSetup();

//    workbench.setFillColor(Color(59,71,57,255));
    workbench.setFillColor(Color(90,120,50));
    workbench.setOrigin(0.0f, 0.0f);
    workbench.setPosition(125.0f, 0.0f);

    buttonClear.init(Vector2f(125.0f, 50.0f),
                    Vector2f(0.0f, 0.0f),
                    Vector2f(10.0f, 213.0f),
                    "CLEAR", 17, -2,
                    Color(87, 80, 15));

    buttonRun.init(Vector2f(125.0f, 50.0f),
                    Vector2f(0, 55.0f),
                    Vector2f(10.0f, 213.0f),
                    "RUN", 17, -2,
                    Color(87, 80, 15));

    buttonImport.init(Vector2f(125.0f, 50.0f),
                    Vector2f(0, 110.0f),
                    Vector2f(10.0f, 213.0f),
                    "IMPORT", 17, -2,
                    Color(87, 80, 15));

    buttonExport.init(Vector2f(125.0f, 50.0f),
                    Vector2f(0, 165.0f),
                    Vector2f(10.0f, 213.0f),
                    "EXPORT", 17, -2,
                    Color(87, 80, 15));

    buttonStart.init(Vector2f(125.0f, 50.0f),
                    Vector2f(0, 250.0f),
                    Vector2f(10.0f, 213.0f),
                    "Start Nod", 17, -2,
                    Color(158, 157, 36));

    buttonAssign.init(Vector2f(125.0f, 50.0f),
                    Vector2f(0, 305.0f),
                    Vector2f(10.0f, 213.0f),
                    "Assign Nod", 17, -2,
                    Color(158, 157, 36));

    buttonCond.init(Vector2f(125.0f, 50.0f),
                    Vector2f(0, 360.0f),
                    Vector2f(10.0f, 213.0f),
                    "Cond Nod", 17, -2,
                    Color(158, 157, 36));

    buttonRead.init(Vector2f(125.0f, 50.0f),
                    Vector2f(0, 415.0f),
                    Vector2f(10.0f, 213.0f),
                    "Read Nod", 17, -2,
                    Color(158, 157, 36));

    buttonOut.init(Vector2f(125.0f, 50.0f),
                    Vector2f(0, 470.0f),
                    Vector2f(10.0f, 213.0f),
                    "Output Nod", 17, -2,
                    Color(158, 157, 36));

    buttonEnd.init(Vector2f(125.0f, 50.0f),
                    Vector2f(0, 525.0f),
                    Vector2f(10.0f, 213.0f),
                    "Stop Nod", 17, -2,
                    Color(158, 157, 36));

}

void afisareButoane(RenderWindow &window)
{
    window.draw(workbench);
    window.draw(OutputText);
    buttonClear.draw(window);
    buttonStart.draw(window);
    buttonAssign.draw(window);
    buttonCond.draw(window);
    buttonRead.draw(window);
    buttonOut.draw(window);
    buttonEnd.draw(window);
    buttonRun.draw(window);
    buttonExport.draw(window);
    buttonImport.draw(window);
}

bool isInsideButton(Vector2f MousePos, Button q)
{
    return q.shape.getGlobalBounds().left < MousePos.x
       and MousePos.x < q.shape.getGlobalBounds().left + q.shape.getGlobalBounds().width
       and q.shape.getGlobalBounds().top < MousePos.y
       and MousePos.y < q.shape.getGlobalBounds().top + q.shape.getGlobalBounds().height;
}

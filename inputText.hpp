#pragma once

#define caracter evnt.text.unicode
using namespace sf;
using namespace std;

int actWritting = -1;
string buffer;

inline void getInput(Event &evnt, vector <Node*> &D)
{
    if(actWritting == -1)
        return;
    if(caracter == 8)
    {
        if(buffer.size() > 0)
            buffer.pop_back();
        D[actWritting]->setTextString(buffer);
    }
    else if(caracter == 13)
    {
        ///cout << buffer << '!' << '\n';
        D[actWritting]->setTextString(buffer);
        buffer.clear();
        actWritting = -1;
    }
    else
    {
        buffer.push_back(caracter);
        D[actWritting]->setTextString(buffer);
    }
}

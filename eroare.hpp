#pragma once

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


bool abandon = false;

Text OutputText;
string error_text;
void throwError(string q)
{
    error_text = "EROARE:\n" + q;
    abandon = true;
}

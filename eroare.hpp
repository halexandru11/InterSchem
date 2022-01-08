#pragma once

#include <bits/stdc++.h>

using namespace std;
using namespace sf;

bool abandon = false;
string errorString = "";

void throwError(string q)
{
    errorString = "EROARE:\n" + q;
    abandon = true;
}

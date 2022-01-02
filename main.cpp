#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#include "Brain.hpp"

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode(Constants::Width, Constants::Height), "Interschem", Style::Close | Style::Titlebar);
    initializareButoane(font);
    nodes.clear();
    font.loadFromFile("Fonts\\Poppins\\Poppins-Regular.ttf");

    eventHandlerBrain(window);
    return 0;
}

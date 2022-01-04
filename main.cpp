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

    auto imageIcon = sf::Image{};
    imageIcon.loadFromFile("ICON3.png");
    window.setIcon(imageIcon.getSize().x, imageIcon.getSize().y, imageIcon.getPixelsPtr());
    eventHandlerBrain(window);
    return 0;
}

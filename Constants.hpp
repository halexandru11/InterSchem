#pragma once
#include "eroare.hpp"
class Constants {
public:
    static constexpr float Width = 1295;
    static constexpr float Height = 720;
    static constexpr float BenchLeft = 125;
    static constexpr float BenchWidth = 900;

    enum NodeType {
        StartNode = 1,
        AssignNode,
        ConditionalNode,
        OutputNode,
        StopNode,
        ReadNode
    };

    enum CoordType {
        CoordIn = 1,
        CoordOut,
        CoordOutTrue,
        CoordOutFalse,
        CoordNode
    };
};

sf::Font font;
int open_tab = 1;
bool is_expo = 0;

#pragma once

class Constants {
public:
    static const int Width = 1295;
    static const int Height = 720;

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

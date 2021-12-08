#pragma once

class Constants {
public:
    static const int Width = 1280;
    static const int Height = 720;

    enum NodeType {
        StartNode = 1,
        AssignNode,
        ConditionalNode,
        OutputNode,
        StopNode
    };
};

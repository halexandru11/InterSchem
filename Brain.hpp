#pragma once

#include "code.hpp"
#include "Constants.hpp"
#include "EvaluareSchema.hpp"
#include "functiiAuxiliare.hpp"
#include "Line.hpp"
#include "import_export.hpp"
#include "inputText.hpp"
#include "Node.hpp"
#include "ui.hpp"

using namespace sf;
using namespace std;

void eventHandlerBrain(RenderWindow& window,
                        bool all = true,
                        bool funcButtons = false,
                        bool nodeButtons = false,
                        bool delayButtons = false,
                        bool tabButtons = false,
                        bool benchEdit = false,
                        bool nodeTextEdit = false,
                        bool nodeDelete = false) {

    bool hold = false;
    Vector2i oldPos;
    int target = -1;
    bool lineStarted = false;
    int lineParentNode = -1;

    while (window.isOpen())
    {
        Event evnt;
        while (window.pollEvent(evnt))
        {
            if(evnt.type == Event::Closed)
            {
                window.close();
            }
            else if(evnt.type == Event::TextEntered)
            {
                if(actWritting != -1)
                    getInput(evnt,nodes);

            }
            else if(evnt.type == Event::MouseButtonPressed)
            {
                if(evnt.mouseButton.button == Mouse::Left and Keyboard::isKeyPressed(Keyboard::LControl)) {
                    if(all or benchEdit) {
                        Vector2f mousePos{Mouse::getPosition(window).x, Mouse::getPosition(window).y};
                        if(lineStarted == false) {
                            for(int i = 0; i < int(nodes.size()); ++i) {
                                if(isInside(mousePos, nodes[i])) {
                                    lineParentNode = i;
                                    if(nodes[i]->nodeType != Constants::ConditionalNode) {
                                        stergeLinie(lines, nodes[i], Constants::CoordOut);
                                        lines.push_back(Line(nodes[i], Constants::CoordOut, window));
                                    }
                                    else {
                                        if(Mouse::getPosition(window).x < nodes[i]->getNodeCoordonates(Constants::CoordNode).x) {
                                            stergeLinie(lines, nodes[i], Constants::CoordOutTrue);
                                            lines.push_back(Line(nodes[i], Constants::CoordOutTrue, window));
                                        }
                                        else {
                                            stergeLinie(lines, nodes[i], Constants::CoordOutFalse);
                                            lines.push_back(Line(nodes[i], Constants::CoordOutFalse, window));
                                        }
                                    }
                                    lineStarted = true;
                                    break;
                                }
                            }
                        }
                        else {
                            for(int i = 0; i < int(nodes.size()); ++i) {
                                if(isInside(mousePos, nodes[i])) {
                                    if(i != lineParentNode) {
                                        lines.back().connectToNode(nodes[i]);
                                        lineStarted = false;
                                        break;
                                    }
                                }
                            }
                            if(lineStarted) {
                                lines.pop_back();
                            }
                            lineStarted = false;
                            lineParentNode = -1;
                        }
                    }
                }
                else if(evnt.mouseButton.button == Mouse::Left) {
                    oldPos = Mouse::getPosition(window);
                    Vector2f pos;
                    pos.x = static_cast<float>(oldPos.x);
                    pos.y = static_cast<float>(oldPos.y);

                    if(all or benchEdit) {
                        hold = true;
                        for(size_t i = 0; i < nodes.size(); ++i) {
                            if(isInside(pos, nodes[i])) {
                                target = i;
                                break;
                            }
                        }
                    }

                    if(all or delayButtons) {
                        if(isInsideButton(pos, buttonDelay200)) {
                            buttonDelay200.setBgColor(Color(163, 184, 81));
                            buttonDelay400.setBgColor(Color(95, 107, 47));
                            buttonDelay700.setBgColor(Color(95, 107, 47));
                            buttonDelay1200.setBgColor(Color(95, 107, 47));
                            delay = 200;
                        }
                        else if(isInsideButton(pos, buttonDelay400)) {
                            buttonDelay200.setBgColor(Color(95, 107, 47));
                            buttonDelay400.setBgColor(Color(163, 184, 81));
                            buttonDelay700.setBgColor(Color(95, 107, 47));
                            buttonDelay1200.setBgColor(Color(95, 107, 47));
                            delay = 400;
                        }
                        else if(isInsideButton(pos, buttonDelay700)) {
                            buttonDelay200.setBgColor(Color(95, 107, 47));
                            buttonDelay400.setBgColor(Color(95, 107, 47));
                            buttonDelay700.setBgColor(Color(163, 184, 81));
                            buttonDelay1200.setBgColor(Color(95, 107, 47));
                            delay = 700;
                        }
                        else if(isInsideButton(pos, buttonDelay1200)) {
                            buttonDelay200.setBgColor(Color(95, 107, 47));
                            buttonDelay400.setBgColor(Color(95, 107, 47));
                            buttonDelay700.setBgColor(Color(95, 107, 47));
                            buttonDelay1200.setBgColor(Color(163, 184, 81));
                            delay = 1200;
                        }
                    }

                    if(all or nodeButtons) {
                        if(isInsideButton(pos, buttonStart))
                            adauga_nod(nodes, Constants::StartNode);
                        if(isInsideButton(pos, buttonAssign))
                            adauga_nod(nodes, Constants::AssignNode);
                        if(isInsideButton(pos, buttonCond))
                            adauga_nod(nodes, Constants::ConditionalNode);
                        if(isInsideButton(pos, buttonOut))
                            adauga_nod(nodes, Constants::OutputNode);
                        if(isInsideButton(pos, buttonEnd))
                            adauga_nod(nodes, Constants::StopNode);
                        if(isInsideButton(pos, buttonRead))
                            adauga_nod(nodes, Constants::ReadNode);
                    }

                    if(all or funcButtons) {
                        if(isInsideButton(pos, buttonClear))
                            ClearScreen(nodes,lines);
                        if(isInsideButton(pos, buttonRun))
                            RunSchema(StartSchema, window, nodes, lines);
                        if(isInsideButton(pos, buttonImport))
                            ImportFromFile(nodes,lines);
                        if(isInsideButton(pos, buttonExport))
                            ExportToFile(nodes);
                        if(isInsideButton(pos, buttonHelp))
                            HelpPopUp();
                    }

                    if(all or tabButtons) {
                        if(isInsideButton(pos, buttonOutPut)) {
                            buttonOutPut.setBgColor(Color(163, 184, 81));
                            buttonVariabile.setBgColor(Color(44, 61, 27));
                            buttonCode.setBgColor(Color(44, 61, 27));
                            open_tab = 1;
                        }
                        if(isInsideButton(pos, buttonVariabile)) {
                            buttonOutPut.setBgColor(Color(44, 61, 27));
                            buttonVariabile.setBgColor(Color(163, 184, 81));
                            buttonCode.setBgColor(Color(44, 61, 27));
                            open_tab = 2;
                        }
                        if(isInsideButton(pos, buttonCode)) {
                            buttonOutPut.setBgColor(Color(44, 61, 27));
                            buttonVariabile.setBgColor(Color(44, 61, 27));
                            buttonCode.setBgColor(Color(163, 184, 81));
                            writeCode(StartSchema);
                            open_tab = 3;
                        }
                    }
                }
                else if(evnt.mouseButton.button == Mouse::Right)
                {
                    if(all or nodeTextEdit) {
                        oldPos = Mouse::getPosition(window);
                        Vector2f pos;
                        pos.x = static_cast<float>(oldPos.x);
                        pos.y = static_cast<float>(oldPos.y);
                        for(size_t i = 0; i < nodes.size(); ++i) {
                            if(isInside(pos, nodes[i])) {
                                if(nodes[i]->nodeType == 1 || nodes[i]->nodeType == 5)
                                    break;
                                actWritting = i;
                                nodes[actWritting]->setTextString(buffer);
                                break;
                            }
                        }
                    }
                }
                else if(evnt.mouseButton.button == Mouse::Middle)
                {
                    if(all or nodeDelete) {
                        oldPos = Mouse::getPosition(window);
                        Vector2f pos;
                        pos.x = static_cast<float>(oldPos.x);
                        pos.y = static_cast<float>(oldPos.y);
                        bool deletee = 0;
                        for(size_t i = 0; i < nodes.size(); ++i)
                        {
                            if(isInside(pos,nodes[i]))
                            {
                                swap(nodes[i], nodes[ nodes.size() - 1 ]);
                                deletee = 1;
                                break;
                            }
                        }
                        if(deletee)
                        {
                            if(strcmp(nodes[ nodes.size() - 1 ]->content, "Start") == 0)
                            {
                               StartSchema = nullptr;
                               isStartNode = false;
                            }
                            if(strcmp(nodes[ nodes.size() - 1 ]->content, "Stop") == 0)
                               isStopNode = false;

                            stergeToateLiniile(lines, nodes.back());
                            delete nodes.back();
                            nodes.pop_back();
                        }
                    }
                }
            }
            else if(evnt.type == Event::MouseButtonReleased)
            {
                target = -1;
                hold = false;
            }
        }
        if(hold && target != -1)
        {
            if(all or benchEdit) {
                float horOffset = nodes[target]->hitbox.getLocalBounds().width / 2;
                float verOffset = nodes[target]->hitbox.getLocalBounds().height / 2;

                Vector2i pozitieMouse = Mouse::getPosition(window);
                Vector2f coordMe = Vector2f{float(pozitieMouse.x), float(pozitieMouse.y)};
                coordMe.x = max(coordMe.x, Constants::BenchLeft + horOffset);
                coordMe.x = min(coordMe.x, Constants::BenchLeft + Constants::BenchWidth - horOffset);
                coordMe.y = max(coordMe.y, verOffset);
                coordMe.y = min(coordMe.y, Constants::Height - verOffset);
                for(size_t i = 0; i < nodes.size(); ++i) {
                    if(i != target and nodes[i]->collides(pozitieMouse, nodes[target]->hitbox.getSize())) {
                        Vector2f coordOther = nodes[i]->getNodeCoordonates(Constants::CoordNode);
                        Vector2f var = coordMe;
                        Vector2f delta{nodes[i]->width + nodes[target]->width, nodes[i]->height + nodes[target]->height};
                        if(coordMe.x > coordOther.x) {
                            var.x = max(coordMe.x, coordOther.x + delta.x/2);
                        }
                        else {
                            var.x = min(coordMe.x, coordOther.x - delta.x/2);
                        }
                        if(coordMe.y > coordOther.y) {
                            var.y = max(coordMe.y, coordOther.y + delta.y/2);
                        }
                        else {
                            var.y = min(coordMe.y, coordOther.y - delta.y/2);
                        }

                        if(fabs(var.x - coordMe.x) * delta.y < fabs(var.y - coordMe.y) * delta.x) {
                            coordMe.x = var.x;
                        }
                        else {
                            coordMe.y = var.y;
                        }
                    }
                }
                nodes[target]->setNodeCoordonates(coordMe);
            }
        }
        window.clear(Color(57, 77, 0));
        DeseneazaPeEcran(window, nodes, lines);
        window.display();
    }
}

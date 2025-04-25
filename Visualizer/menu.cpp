#include "SFML/Graphics.hpp"
#include "knapsack_visualizer.h"
#include "sorting_visualizer.h"
#include "pointer_visualizer.h"
#include "binary_visualizer.h"
#include "graph_visualizer.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Button 
{
    sf::RectangleShape shape;
    sf::Text label;
};

Button createButton(float x, float y, float width, float height, const string& text, sf::Font& font, int fontSize) 
{
    Button button;
    button.shape.setSize(sf::Vector2f(width, height));
    button.shape.setPosition(x, y);
    button.shape.setFillColor(sf::Color(sf::Color::White));

    button.label.setFont(font);
    button.label.setString(text);
    button.label.setCharacterSize(fontSize);
    button.label.setFillColor(sf::Color::Black);

    sf::FloatRect textRect = button.label.getLocalBounds();
    button.label.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    button.label.setPosition(x + width / 2.0f, y + height / 2.0f);

    return button;
}

int main() 
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Algorithm Visualizer Menu");

    sf::Font font;
    if (!font.loadFromFile("fonts/OpenSans-Regular.ttf")) {
        cout << "Error: font not found\n";
        return -1;
    }

    vector<Button> buttons;
    vector<string> options = 
    {
        "Knapsack Visualizer",
        "Sorting Algorithms Visualizer",
        "Pointer Visualizer",
        "Binary Search Visualizer",
        "Graph Algorithms Visualizer"
    };

    float buttonWidth = 400, buttonHeight = 50;
    float startX = 200, startY = 150, spacing = 70;

    for (size_t i = 0; i < options.size(); ++i) 
    {
        buttons.push_back(createButton(startX, startY + i * spacing, buttonWidth, buttonHeight, options[i], font, 20));
    }

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                for (size_t i = 0; i < buttons.size(); ++i) {
                    if (buttons[i].shape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) 
                    {
                        system("cls");
                        switch (i) 
                        {
                        case 0:
                            KnapsackVisualizer();
                            break;
                        case 1:
                            SortingVisualizer();
                            break;
                        case 2:
                            PointerVisualizer();
                            break;
                        case 3:
                            BinaryVisualizer();
                            break;
                        case 4:
                            GraphVisualizer();
                            break;
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::Black);

        for (const auto& button : buttons) 
        {
            window.draw(button.shape);
            window.draw(button.label);
        }

        window.display();
    }

    return 0;
}
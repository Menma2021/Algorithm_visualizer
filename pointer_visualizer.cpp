#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Step {
    vector<int> heights;
    vector<int> water;
    int l, r;
};

void trappingRainWaterSimulation(const vector<int>& height, vector<Step>& steps)
{
    int l = 0, r = height.size() - 1;
    int lMax = height[l], rMax = height[r];
    vector<int> water(height.size(), 0);

    while (l < r)
    {
        if (lMax < rMax)
        {
            l++;
            lMax = max(lMax, height[l]);
            water[l] = lMax - height[l];
        }
        else
        {
            r--;
            rMax = max(rMax, height[r]);
            water[r] = rMax - height[r];
        }
        steps.push_back({ height, water, l, r });
    }
}

void drawText(sf::RenderWindow& window, const string& text, int x, int y, sf::Font& font, int size = 20, sf::Color color = sf::Color::White)
{
    sf::Text sfText;
    sfText.setFont(font);
    sfText.setString(text);
    sfText.setCharacterSize(size);
    sfText.setFillColor(color);
    sfText.setPosition(x, y);
    window.draw(sfText);
}

void drawVisualization(sf::RenderWindow& window, const Step& step, int rectWidth, int offsetX, int offsetY, int maxHeight, sf::Font& font)
{
    for (int i = 0; i < step.heights.size(); i++)
    {
        int height = (static_cast<float>(step.heights[i]) / maxHeight) * 640;
        sf::RectangleShape bar(sf::Vector2f(rectWidth, -height));
        bar.setPosition(offsetX + i * (rectWidth + 2), offsetY);
        bar.setFillColor(sf::Color(150, 150, 150));
        window.draw(bar);

        if (step.water[i] > 0)
        {
            int waterHeight = (static_cast<float>(step.water[i]) / maxHeight) * 640;
            sf::RectangleShape waterBar(sf::Vector2f(rectWidth, -waterHeight));
            waterBar.setPosition(offsetX + i * (rectWidth + 2), offsetY - height);
            waterBar.setFillColor(sf::Color::Cyan);
            window.draw(waterBar);
        }
    }

    // Highlighting pointers
    sf::CircleShape leftPointer(5);
    leftPointer.setFillColor(sf::Color::Red);
    leftPointer.setPosition(offsetX + step.l * (rectWidth + 2) + rectWidth / 2, offsetY + 10);
    window.draw(leftPointer);

    sf::CircleShape rightPointer(5);
    rightPointer.setFillColor(sf::Color::Green);
    rightPointer.setPosition(offsetX + step.r * (rectWidth + 2) + rectWidth / 2, offsetY + 10);
    window.draw(rightPointer);

    // Text information
    drawText(window, "Left pointer: " + to_string(step.l), 10, 10, font, 20, sf::Color::White);
    drawText(window, "Right pointer: " + to_string(step.r), 10, 40, font, 20, sf::Color::White);
    drawText(window, "Step Progress: x", 10, 70, font, 20, sf::Color::White);
}

void PointerVisualizer()
{
    int n;
    cout << "Enter amount of heights: ";
    cin >> n;
    vector<int> height(n);
    cout << "Enter " << n << " heights: ";
    for (int i = 0; i < n; i++) cin >> height[i];

    vector<Step> steps;
    trappingRainWaterSimulation(height, steps);

    // HERE: 1280 - width, 800 - height
    sf::RenderWindow window(sf::VideoMode(1280, 800), "Two Pointer Visualizer");
    sf::Font font;
    if (!font.loadFromFile("fonts/OpenSans-Regular.ttf"))
    {
        cout << "Error: font not found\n";
        return;
    }

    int rectWidth = 1280 / (1.3 * n);
    int maxHeight = *max_element(height.begin(), height.end());

    size_t stepIndex = 0;
    sf::Time delay = sf::milliseconds(500);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (stepIndex >= steps.size())
        {
            cout << "Enter to leave\n" << endl;
            cin.ignore();
            cin.get();
            window.close();
            return;
        }

        window.clear();
        drawVisualization(window, steps[stepIndex], rectWidth, 5, 750, maxHeight, font);
        window.display();
        sf::sleep(delay);
        stepIndex++;
    }
}
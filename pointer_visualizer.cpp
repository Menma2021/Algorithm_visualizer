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

void drawVisualization(sf::RenderWindow& window, const Step& step, int rectWidth, int offsetX, int offsetY, int maxHeight, sf::Font& font, int stepIndex, int totalSteps)
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
    drawText(window, "Step Progress: " + to_string(stepIndex + 1) + " / " + to_string(totalSteps), 10, 70, font, 20, sf::Color::White);
}

void PointerVisualizer()
{
    int n = INT_MAX;
    int maxN = 310;

    // Input validation for number of heights
    while (n > maxN || n < 2)
    {
        cout << "Enter amount of heights (2 to " << maxN << "): ";
        if (cin >> n)
        {
            if (n > maxN || n < 2)
            {
                cout << "n is too large or too small, enter again\n";
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            cout << "Invalid input type, try again\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            n = INT_MAX;
        }
    }

    vector<int> height(n);
    int choice;
    cout << "Enter if values should be randomly generated or manually inputed (0 if generated, any other number if not): ";
    if (cin >> choice)
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        choice = 0;
    }

    if (choice == 0)
    {
        // Generated heights
        int maxVal = 0;
        while (maxVal < 1)
        {
            cout << "Enter max height value (> 0): ";
            if (cin >> maxVal)
            {
                if (maxVal < 1)
                {
                    cout << "Max height must be greater than 0\n";
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else
            {
                cout << "Invalid input type, try again\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                maxVal = 0;
            }
        }

        srand(static_cast<unsigned>(time(0)));
        for (int i = 0; i < n; ++i)
        {
            height[i] = rand() % (maxVal + 1);
        }
    }
    else
    {
        // Manual height input with validation
        for (int i = 0; i < n; ++i)
        {
            int h = INT_MIN;
            while (h < 0)
            {
                cout << "Height " << i + 1 << " (non-negative): ";
                if (cin >> h)
                {
                    if (h < 0)
                    {
                        cout << "Height must be non-negative\n";
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else
                {
                    cout << "Invalid input type, try again\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    h = INT_MIN;
                }
            }
            height[i] = h;
        }
    }

    // Entering visualizing mode with validation
    int test;
    bool timed;
    cout << "Enter if Two-Pointer should work automatically or on left-click (0 if automatically, any other number if on-click): ";
    if (cin >> test)
    {
        timed = test == 0 ? true : false;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        timed = false;
    }

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

    float rectWidth = 1280.0 / (1.5 * double(n));
    int maxHeight = *max_element(height.begin(), height.end());

    size_t stepIndex = 0;
    sf::Time delay = sf::milliseconds(500);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Checking for closing window
            if (event.type == sf::Event::Closed) window.close();

            if (!timed && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                stepIndex++;
            }
        }

        if (stepIndex >= steps.size())
        {
            cout << "Enter to leave\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            window.close();
            return;
        }

        window.clear();
        Step& currentStep = steps[stepIndex];
        drawVisualization(window, steps[stepIndex], rectWidth, 5, 750, maxHeight, font, stepIndex, steps.size());
        window.display();

        if (timed)
        {
            sf::sleep(delay);
            stepIndex++;
        }
    }
}
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

void drawBars(sf::RenderWindow& window, const vector<int>& array, int rectWidth, int offsetX, int offsetY, int maxHeight, int low, int mid, int high, int target) {
    for (int i = 0; i < array.size(); i++) 
    {
        int height = (static_cast<float>(array[i]) / maxHeight) * 525;
        sf::RectangleShape bar(sf::Vector2f(rectWidth, -height));
        bar.setPosition(offsetX + i * (rectWidth + 1), offsetY);

        if (i == mid)
        {
            bar.setFillColor(sf::Color::Yellow); // Highlighting middle
        }
        else if (i == target)
        {
            bar.setFillColor(sf::Color::Red); // Highlighting target
        }
        else if (i >= low && i <= high)
        {
            bar.setFillColor(sf::Color::Green); // Highlighting search range
        }
        else 
        {
            bar.setFillColor(sf::Color::White);
        }

        window.draw(bar);
    }
}

static void drawText(sf::RenderWindow& window, const string& text, int x, int y, sf::Font& font, int size = 20, sf::Color color = sf::Color::White)
{
    sf::Text sfText;
    sfText.setFont(font);
    sfText.setString(text);
    sfText.setCharacterSize(size);
    sfText.setFillColor(color);
    sfText.setPosition(x, y);
    window.draw(sfText);
}

void binarySearch(const vector<int>& array, int target, vector<int>& midStates, vector<int>& lowStates, vector<int>& highStates)
{
    int low = 0, high = array.size() - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        midStates.push_back(mid);
        lowStates.push_back(low);
        highStates.push_back(high);

        if (array[mid] == target)
        {
            break;
        }
        else if (array[mid] < target)
        {
            low = mid + 1;
        }
        else 
        {
            high = mid - 1;
        }
    }
}

void BinaryVisualizer()
{
    srand(static_cast<unsigned>(time(0)));

    int n;
    cout << "Enter the number of elements (n): ";
    cin >> n;

    vector<int> array(n);
    for (int i = 0; i < n; i++) 
    {
        array[i] = i + 1;
    }

    int target;
    cout << "Enter the target element (1 to " << n << "): ";
    cin >> target;

    vector<int> midStates, lowStates, highStates;
    binarySearch(array, target, midStates, lowStates, highStates);

    sf::RenderWindow window(sf::VideoMode(1280, 800), "Binary Search Visualizer");
    sf::Font font;
    if (!font.loadFromFile("fonts/OpenSans-Regular.ttf")) 
    {
        cout << "Error: font not found\n";
        return;
    }

    // Width of rectangles
    float rectWidth = 1280.0 / (1.4 * double(n));
    int maxHeight = n;

    size_t step = 0;
    sf::Time delay = sf::milliseconds(500);

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }
        }

        if (step >= midStates.size()) 
        {
            cout << "Enter to leave\n";
            cin.ignore();
            cin.get();
            window.close();
            return;
        }

        window.clear();

        // Bars drawing
        drawBars(window, array, rectWidth, 0, 800, maxHeight, lowStates[step], midStates[step], highStates[step], target - 1);

        // Text drawing
        drawText(window, "Step: " + to_string(step + 1), 10, 10, font);
        drawText(window, "Low: " + to_string(lowStates[step]), 10, 50, font);
        drawText(window, "Mid: " + to_string(midStates[step]), 10, 90, font);
        drawText(window, "High: " + to_string(highStates[step]), 10, 130, font);
        drawText(window, "Target: " + to_string(target), 10, 170, font);

        window.display();
        sf::sleep(delay);
        step++;
    }
}

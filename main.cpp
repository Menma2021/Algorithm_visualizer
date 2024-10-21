#include "SFML/Graphics.hpp"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// Drawing line between current element and elements that are being checked
void drawLine(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f end, float thickness, sf::Color color)
{
    sf::Vector2f direction = end - start;
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::RectangleShape line(sf::Vector2f(length, thickness));

    line.setFillColor(color);
    line.setPosition(start);

    // Calculating the angle of the line
    float angle = atan2(direction.y, direction.x) * 180 / 3.14159f;
    line.setRotation(angle);

    window.draw(line);
}

void drawTable(sf::RenderWindow& window, const vector<vector<int>>& knapsack,
    int rectSize, int spacing, const sf::Font& font, int cur_i, int cur_j, int prev_i, int prev_j, int prev_i2, int prev_j2, const vector<int>& weight, const vector<int>& price)
{
    sf::Text textBox, infoText;
    textBox.setFont(font);
    textBox.setFillColor(sf::Color::White);

    infoText.setFont(font);
    infoText.setFillColor(sf::Color::White);
    infoText.setCharacterSize(12);

    int tableWidth = knapsack[0].size() * (rectSize + spacing);
    int tableHeight = knapsack.size() * (rectSize + spacing);

    // Space in the window
    int windowWidth = window.getSize().x;
    int windowHeight = window.getSize().y;

    // Space on the right and bottom
    int availableRightSpace = windowWidth - (tableWidth + 50);
    int availableBottomSpace = windowHeight - (tableHeight + 50);

    for (int i = 0; i < knapsack.size(); i++) {
        for (int j = 0; j < knapsack[0].size(); j++) {
            sf::RectangleShape cell(sf::Vector2f(rectSize, rectSize));
            cell.setPosition(j * (rectSize + spacing) + 25, i * (rectSize + spacing) + 25);

            // Color for the current element
            if (i == cur_i && j == cur_j)
            {
                cell.setFillColor(sf::Color::Yellow);
            }
            // Color based on whether changes occured
            else if (i != 0 && j != 0)
            {
                if ((knapsack[i][j] == knapsack[i - 1][j]) || (knapsack[i][j] == 0))
                {
                    cell.setFillColor(sf::Color::Red);
                }
                else
                {
                    cell.setFillColor(sf::Color::Green);
                }
            }
            else
            {
                cell.setFillColor(sf::Color::Red);
            }
            window.draw(cell);

            // Text size adjustments
            if (to_string(knapsack[i][j]).size() < 3) textBox.setCharacterSize(rectSize * 0.8);
            else textBox.setCharacterSize(rectSize / (to_string(knapsack[i][j]).size() * 0.6));

            textBox.setString(to_string(knapsack[i][j]));
            textBox.setPosition(j * (rectSize + spacing) + 25, i * (rectSize + spacing) + 25);

            window.draw(textBox);
        }
    }

    // Information for the current element
    if (cur_i > 0 && cur_j >= 0) {
        int curWeight = weight[cur_i - 1];
        int curPrice = price[cur_i - 1];
        string infoStr = "Item (" + to_string(cur_i) + "):\n";
        infoStr += "Weight: " + to_string(curWeight) + ", Value: " + to_string(curPrice) + "\n";

        infoStr += "knap[" + to_string(cur_i - 1) + "][" + to_string(cur_j) + "] = " + to_string(knapsack[prev_i][prev_j]) + "\n";

        if (prev_i2 >= 0 && prev_j2 >= 0) {
            infoStr += "knap[" + to_string(cur_i - 1) + "][" + to_string(prev_j2) + "] = " + to_string(knapsack[prev_i2][prev_j2]) + "\n";
        }

        // Chosen option
        if (prev_j2 >= 0 && knapsack[cur_i][cur_j] == knapsack[prev_i2][prev_j2] + curPrice) {
            infoStr += "Chosen: knap[" + to_string(prev_i2) + "][" + to_string(prev_j2) + "] + " + to_string(curPrice);
        }
        else {
            infoStr += "Chosen: knap[" + to_string(prev_i) + "][" + to_string(prev_j) + "]";
        }

        // Info placement depending on the free space
        if (availableRightSpace > availableBottomSpace) {
            // Place the info on the right + vertical display
            infoText.setPosition(tableWidth + 50, 25);
            infoText.setString(infoStr);
        }
        else {
            // Place the info at the bottom + splitting for horizontal display
            infoText.setPosition(25, tableHeight + 50);
            infoStr = infoStr;
            stringstream ss(infoStr);
            string line;
            string horizontalStr = "";
            while (getline(ss, line)) {
                horizontalStr += line + "   ";
            }
            infoText.setString(horizontalStr);
        }

        window.draw(infoText);
    }


    // Drawing lines between current element and elements that are being checked
    float thickness = rectSize / 10.0f;

    if (prev_i >= 0 && prev_j >= 0) {
        sf::Vector2f start(cur_j * (rectSize + spacing) + 25 + rectSize / 2, cur_i * (rectSize + spacing) + 25 + rectSize / 2);
        sf::Vector2f end(prev_j * (rectSize + spacing) + 25 + rectSize / 2, prev_i * (rectSize + spacing) + 25 + rectSize / 2);
        drawLine(window, start, end, thickness, sf::Color::Blue);
    }

    if (prev_i2 >= 0 && prev_j2 >= 0) {
        sf::Vector2f start(cur_j * (rectSize + spacing) + 25 + rectSize / 2, cur_i * (rectSize + spacing) + 25 + rectSize / 2);
        sf::Vector2f end(prev_j2 * (rectSize + spacing) + 25 + rectSize / 2, prev_i2 * (rectSize + spacing) + 25 + rectSize / 2);
        drawLine(window, start, end, thickness, sf::Color::Blue);
    }
}

int main()
{
    // Data input
    int n, max_w, test;
    bool timed;
    cout << "Enter max weight and item amount: ";
    cin >> max_w >> n;
    cout << "Enter if DP should work automatically or on left-click (0 if automatically, any other number if on-click): ";
    cin >> test;
    timed = test == 0 ? true : false;

    sf::Time wait = sf::milliseconds(5000 / (n * max_w));
    vector<int> weight(n);
    vector<int> price(n);
    vector<vector<int>> knapsack(n + 1, vector<int>(max_w + 1, 0));

    cout << "Enter " << n << " entries with 2 values: weight and price of item 'n': ";
    for (int i = 0; i < n; i++)
    {
        cin >> weight[i] >> price[i];
    }

    sf::RenderWindow window(sf::VideoMode(1280, 800), "Knapsack Visualizer");

    sf::Font font;
    if (!font.loadFromFile("fonts/OpenSans-Regular.ttf"))
    {
        cout << "Error: font not found\n";
        return -1;
    }

    int rectSize = min(700 / (n + 1), 1150 / (max_w + 1));
    int spacing = rectSize / 10;

    // Text styling
    sf::Text capacityText, weightText, valueText, textInd, selectedItemsText;

    textInd.setFont(font);
    textInd.setCharacterSize(min(int(rectSize * 0.8), 10));
    textInd.setFillColor(sf::Color::White);

    capacityText.setFont(font);
    capacityText.setCharacterSize(12);
    capacityText.setFillColor(sf::Color::White);
    capacityText.setPosition(50, 780);

    weightText.setFont(font);
    weightText.setCharacterSize(12);
    weightText.setFillColor(sf::Color::White);
    weightText.setPosition(350, 780);

    valueText.setFont(font);
    valueText.setCharacterSize(12);
    valueText.setFillColor(sf::Color::White);
    valueText.setPosition(650, 780);

    selectedItemsText.setFont(font);
    selectedItemsText.setCharacterSize(12);
    selectedItemsText.setFillColor(sf::Color::White);
    selectedItemsText.setPosition(930, 780);

    bool nextStep = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Checking for closing window
            if (event.type == sf::Event::Closed)
                window.close();

            // Checking for left-click
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                nextStep = true;
            }
        }

        // Knapsack solving
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= max_w; j++)
            {
                int prev_i = i - 1;
                int prev_j = j;
                int prev_i2 = i - 1;
                int prev_j2 = (j - weight[i - 1] >= 0) ? (j - weight[i - 1]) : -1;

                if (weight[i - 1] <= j)
                {
                    knapsack[i][j] = max(knapsack[i - 1][j], knapsack[i - 1][j - weight[i - 1]] + price[i - 1]);
                }
                else
                {
                    knapsack[i][j] = knapsack[i - 1][j];
                }

                window.clear();

                for (int j1 = 0; j1 <= max_w; j1++)
                {
                    textInd.setString(to_string(j1));
                    textInd.setPosition(j1 * (rectSize + spacing) + 10 + (rectSize / 2), 10);
                    window.draw(textInd);
                }

                for (int i1 = 0; i1 <= n; i1++)
                {
                    textInd.setString(to_string(i1));
                    textInd.setPosition(10, i1 * (rectSize + spacing) + 10 + (rectSize / 2));
                    window.draw(textInd);
                }

                drawTable(window, knapsack, rectSize, spacing, font, i, j, prev_i, prev_j, prev_i2, prev_j2, weight, price);
                window.display();

                if (timed) sf::sleep(wait);
                else
                {
                    nextStep = false;
                    while (!nextStep)
                    {
                        while (window.pollEvent(event))
                        {
                            if (event.type == sf::Event::Closed)
                            {
                                window.close();
                                return 0;
                            }

                            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                            {
                                nextStep = true;
                            }
                        }
                    }
                }
            }
        }

        int totalValue = knapsack[n][max_w];
        int totalWeight = 0;
        int remainingCapacity = max_w;

        vector<int> selectedItems;

        // Checking items for the optimal solution
        for (int i = n; i > 0 && totalValue > 0; i--) {
            if (totalValue != knapsack[i - 1][remainingCapacity]) {
                selectedItems.push_back(i - 1);
                totalWeight += weight[i - 1];
                totalValue -= price[i - 1];
                remainingCapacity -= weight[i - 1];
            }
        }

        // Final results
        capacityText.setString("Capacity: " + to_string(max_w));
        weightText.setString("Total weight: " + to_string(totalWeight));
        valueText.setString("Total value: " + to_string(knapsack[n][max_w]));

        ostringstream selectedItemsStream;
        selectedItemsStream << "Items selected: ";
        for (size_t i = 0; i < selectedItems.size(); ++i) {
            selectedItemsStream << selectedItems[i];
            if (i < selectedItems.size() - 1) {
                selectedItemsStream << ", ";
            }
        }

        selectedItemsText.setString(selectedItemsStream.str());

        window.draw(capacityText);
        window.draw(weightText);
        window.draw(valueText);
        window.draw(selectedItemsText);

        window.display();

        cout << selectedItemsStream.str();

        cout << "Enter to leave" << endl;
        cin.ignore();
        cin.get();

        window.close();
    }

    cout << "Maximum value: " << knapsack[n][max_w] << endl;

    return 0;
}
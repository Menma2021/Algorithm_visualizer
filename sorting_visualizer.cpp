#include "SFML/Graphics.hpp"
#include "sorting_visualizer.h"
#include <iostream>
#include <random>

using namespace std;

void drawBars(sf::RenderWindow& window, const vector<int>& array, int rectWidth, int offsetX, int offsetY, sf::Color color, int maxHeight, int highlight = -1)
{
    for (int i = 0; i < array.size(); i++)
    {
        int height = (static_cast<float>(array[i]) / maxHeight) * 525;
        sf::RectangleShape bar(sf::Vector2f(rectWidth, -height));
        bar.setPosition(offsetX + i * (rectWidth + 1), offsetY);
        bar.setFillColor(i == highlight ? sf::Color::Yellow : color);
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

void bubbleSort(vector<int>& array, vector<vector<int>>& states, vector<int>& highlights)
{
    int n = array.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            highlights.push_back(j);
            states.push_back(array);
            if (array[j] > array[j + 1])
            {
                swap(array[j], array[j + 1]);
                states.push_back(array);
                highlights.push_back(j + 1);
            }
        }
    }
}



void insertionSort(vector<int>& array, vector<vector<int>>& states, vector<int>& highlights)
{
    int n = array.size();
    for (int i = 1; i < n; i++)
    {
        int key = array[i];
        int j = i - 1;

        while (j >= 0 && array[j] > key)
        {
            highlights.push_back(j);
            states.push_back(array);
            array[j + 1] = array[j];
            states.push_back(array);
            highlights.push_back(j + 1);
            j--;
        }
        array[j + 1] = key;
        states.push_back(array);
        highlights.push_back(j + 1);
    }
}


void merge(vector<int>& array, int low, int mid, int high, vector<vector<int>>& states, vector<int>& highlights) 
{
    vector<int> left(array.begin() + low, array.begin() + mid + 1);
    vector<int> right(array.begin() + mid + 1, array.begin() + high + 1);

    int i = 0, j = 0, k = low;

    while (i < left.size() && j < right.size()) 
    {
        highlights.push_back(k);
        states.push_back(array);
        if (left[i] <= right[j]) 
        {
            array[k] = left[i];
            i++;
        }
        else 
        {
            array[k] = right[j];
            j++;
        }
        states.push_back(array);
        highlights.push_back(k);
        k++;
    }

    while (i < left.size()) 
    {
        highlights.push_back(k); 
        states.push_back(array);
        array[k] = left[i];
        i++;
        states.push_back(array);
        highlights.push_back(k);
        k++;
    }

    while (j < right.size()) 
    {
        highlights.push_back(k);
        states.push_back(array);
        array[k] = right[j];
        j++;
        states.push_back(array);
        highlights.push_back(k);
        k++;
    }
}

void mergeSort(vector<int>& array, int low, int high, vector<vector<int>>& states, vector<int>& highlights) {
    if (low < high) 
    {
        int mid = low + (high - low) / 2;
        mergeSort(array, low, mid, states, highlights);
        mergeSort(array, mid + 1, high, states, highlights);
        merge(array, low, mid, high, states, highlights);
    }
}

void quickSort(vector<int>& array, int low, int high, vector<vector<int>>& states, vector<int>& highlights)
{
    if (low < high)
    {
        int pivot = array[high];
        int i = low - 1;
        for (int j = low; j < high; j++)
        {
            highlights.push_back(j);
            states.push_back(array);
            if (array[j] < pivot)
            {
                i++;
                swap(array[i], array[j]);
                states.push_back(array);
                highlights.push_back(i);
            }
        }
        swap(array[i + 1], array[high]);
        states.push_back(array);
        highlights.push_back(i + 1);
        quickSort(array, low, i, states, highlights);
        quickSort(array, i + 2, high, states, highlights);
    }
}

void SortingVisualizer()
{
    srand(static_cast<unsigned>(time(0)));
    int n;
    bool manual;
    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Enter sorting mode (0 for automatic, 1 for manual): ";
    cin >> manual;

    sf::Time delay = sf::milliseconds(250 / n);

    vector<int> originalArray(n);
    for (int i = 0; i < n; i++) originalArray[i] = i + 1;

    random_device rd;
    mt19937 g(rd());
    shuffle(originalArray.begin(), originalArray.end(), g);

    vector<vector<int>> bubbleStates, insertionStates, mergeStates, quickStates;
    vector<int> bubbleHighlights, insertionHighlights, mergeHighlights, quickHighlights;

    vector<int> bubbleArray = originalArray;
    vector<int> insertionArray = originalArray;
    vector<int> mergeArray = originalArray;
    vector<int> quickArray = originalArray;

    bubbleSort(bubbleArray, bubbleStates, bubbleHighlights);
    insertionSort(insertionArray, insertionStates, insertionHighlights);
    mergeSort(mergeArray, 0, n - 1, mergeStates, mergeHighlights);
    quickSort(quickArray, 0, n - 1, quickStates, quickHighlights);

    sf::RenderWindow window(sf::VideoMode(1680, 1050), "Sorting Visualizer");
    sf::Font font;
    if (!font.loadFromFile("fonts/OpenSans-Regular.ttf"))
    {
        cout << "Error: font not found\n";
        return;
    }

    cout << "bubbleStates size: " << bubbleStates.size() << ", bubbleHighlights size: " << bubbleHighlights.size() << endl;
    cout << "bubbleStates size: " << insertionStates.size() << ", bubbleHighlights size: " << insertionHighlights.size() << endl;
    cout << "bubbleStates size: " << mergeStates.size() << ", bubbleHighlights size: " << mergeHighlights.size() << endl;
    cout << "bubbleStates size: " << quickStates.size() << ", bubbleHighlights size: " << quickHighlights.size() << endl;

    float rectWidth = max(double(1680.0 / (2.13 * double(n))), 0.1);
    bool nextStep = false;

    size_t bubbleStep = 0, insertionStep = 0, mergeStep = 0, quickStep = 0;
    int maxHeight = n;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (manual && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                nextStep = true;
            }
        }

        window.clear();

        drawBars(window, bubbleStates[bubbleStep], rectWidth, 0, 525, sf::Color::Green, maxHeight, bubbleHighlights[bubbleStep]);
        drawBars(window, insertionStates[insertionStep], rectWidth, 840, 525, sf::Color::Red, maxHeight, insertionHighlights[insertionStep]);
        drawBars(window, mergeStates[mergeStep], rectWidth, 0, 1050, sf::Color::Blue, maxHeight, mergeHighlights[mergeStep]);
        drawBars(window, quickStates[quickStep], rectWidth, 840, 1050, sf::Color::Cyan, maxHeight, quickHighlights[quickStep]);

        drawText(window, "Bubble sort step: " + to_string(bubbleStep), 10, 10, font);
        drawText(window, "Insertion sort step: " + to_string(insertionStep), 850, 10, font);
        drawText(window, "Merge sort step: " + to_string(mergeStep), 10, 620, font);
        drawText(window, "Quick sort step: " + to_string(quickStep), 850, 620, font);

        window.display();

        if (manual)
        {
            if (nextStep)
            {
                nextStep = false;
                if (bubbleStep < bubbleStates.size() - 1) bubbleStep++;
                if (insertionStep < insertionStates.size() - 1) insertionStep++;
                if (mergeStep < mergeStates.size() - 1) mergeStep++;
                if (quickStep < quickStates.size() - 1) quickStep++;
            }
        }
        else
        {
            sf::sleep(delay);
            if (bubbleStep < bubbleStates.size() - 1) bubbleStep++;
            if (insertionStep < insertionStates.size() - 1) insertionStep++;
            if (mergeStep < mergeStates.size() - 1) mergeStep++;
            if (quickStep < quickStates.size() - 1) quickStep++;
        }

        if (bubbleStep == bubbleStates.size() - 1 && insertionStep == insertionStates.size() - 1 &&
            mergeStep == mergeStates.size() - 1 && quickStep == quickStates.size() - 1)
        {
            cout << "\nEnter to leave\n" << endl;
            cin.ignore();
            cin.get();

            window.close();
        }
    }
}
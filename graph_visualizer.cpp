#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <cstdlib>
#include<cmath>
#include <ctime>

using namespace std;

struct Cell 
{
    int x, y;
};

struct Node
{
    int x, y;
    float gCost, hCost, fCost;
};

struct Compare
{
    bool operator()(const Node& left, const Node& right)
    {
        return left.fCost > right.fCost;
    }
};

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

void drawMaze(sf::RenderWindow& window, vector<vector<int>>& maze, int cellSize, int n, vector<int> steps, int stepIndex, int offsetX, int offsetY)
{
    // Drawing with Vertext array (for better perfomance)
    sf::VertexArray vertices(sf::Quads);
    for (int y = 0; y < n; y++)
    {
        for (int x = 0; x < n; x++)
        {
            sf::Color color = (maze[y][x] == 1) ? sf::Color::Blue : sf::Color::White;

            sf::Vertex v0(sf::Vector2f(offsetX + x * cellSize, offsetY + y * cellSize), color);
            sf::Vertex v1(sf::Vector2f(offsetX + (x + 1) * cellSize, offsetY + y * cellSize), color);
            sf::Vertex v2(sf::Vector2f(offsetX + (x + 1) * cellSize, offsetY + (y + 1) * cellSize), color);
            sf::Vertex v3(sf::Vector2f(offsetX + x * cellSize, offsetY + (y + 1) * cellSize), color);

            vertices.append(v0);
            vertices.append(v1);
            vertices.append(v2);
            vertices.append(v3);
        }
    }

    for (int i = 0; i <= stepIndex && i < steps.size(); i++)  // Drawing steps
    {
        int pos = steps[i];
        int x = pos % n;
        int y = pos / n;

        sf::Color pathColor = (i == stepIndex) ? sf::Color::Red : sf::Color::Cyan;

        sf::Vertex v0(sf::Vector2f(offsetX + x * cellSize, offsetY + y * cellSize), pathColor);
        sf::Vertex v1(sf::Vector2f(offsetX + (x + 1) * cellSize, offsetY + y * cellSize), pathColor);
        sf::Vertex v2(sf::Vector2f(offsetX + (x + 1) * cellSize, offsetY + (y + 1) * cellSize), pathColor);
        sf::Vertex v3(sf::Vector2f(offsetX + x * cellSize, offsetY + (y + 1) * cellSize), pathColor);

        vertices.append(v0);
        vertices.append(v1);
        vertices.append(v2);
        vertices.append(v3);
    }

    window.draw(vertices);
}

void generateMaze(int startX, int startY, vector<vector<int>>& maze, int n) 
{
    // Possible movement directions (2 to be able to create paths)
    const vector<Cell> directions = {{0, -2}, {0, 2}, {-2, 0}, {2, 0}};

    srand(static_cast<unsigned>(time(0)));  // Seed random generator
    stack<Cell> stack;
    stack.push({startX, startY});
    maze[startY][startX] = 0;  // Starting point

    while (!stack.empty()) 
    {
        Cell current = stack.top();
        vector<Cell> neighbors;

        for (const auto& dir : directions) 
        {
            int nx = current.x + dir.x;
            int ny = current.y + dir.y;
            if (nx > 0 && ny > 0 && nx < n - 1 && ny < n - 1 && maze[ny][nx] == 1) 
            {
                neighbors.push_back({nx, ny});
            }
        }

        if (!neighbors.empty()) 
        {
            Cell next = neighbors[rand() % neighbors.size()];
            maze[(current.y + next.y) / 2][(current.x + next.x) / 2] = 0; // Creating path between 2 points
            maze[next.y][next.x] = 0;
            stack.push(next);
        }
        else 
        {
            stack.pop();
        }
    }

    maze[1][0] = 0; // Start
    maze[n - 2][n - 1] = 0; // End
}

void DFS(int start, int end, vector<vector<int>>& adMatrix, vector<int>& steps)
{
    stack<int> nodes;
    vector<bool> visited(adMatrix.size(), false);

    nodes.push(start); // DFS start

    while (!nodes.empty())
    {
        int current = nodes.top();
        nodes.pop();

        if (visited[current]) continue;
        visited[current] = true;
        steps.push_back(current);
        if (current == end) break;

        for (int i = 0; i < adMatrix[current].size(); i++)
        {
            if ((adMatrix[current][i] == 1) && !visited[i])
            {
                nodes.push(i);
            }
        }
    }
}

void BFS(int start, int end, vector<vector<int>>& adMatrix, vector<int>& steps)
{
    queue<int> nodes;
    vector<bool> visited(adMatrix.size(), false);

    nodes.push(start); // BFS start

    while (!nodes.empty())
    {
        int current = nodes.front();
        nodes.pop();
        steps.push_back(current);

        if (current == end) break;

        for (int i = 0; i < adMatrix[current].size(); i++)
        {
            if ((adMatrix[current][i] == 1) && !visited[i])
            {
                nodes.push(i);
                visited[i] = true;
            }
        }
    }
    // Temporal fix: for some reason, BFS visualization does not include last step, too late to figure out why, so I'll just add one more end to the step
    steps.push_back(end);
}

int heurManhattan(const Node& cur, const Node& goal)
{
    return abs(cur.x - goal.x) + abs(cur.y - goal.y);
}

void aStar(int start, int end, vector<vector<int>>& adMatrix, vector<int>& steps)
{
    int n = sqrt(adMatrix[0].size());

    priority_queue<Node, vector<Node>, Compare> nodes;
    unordered_set<int> visited;
    unordered_map<int, float> gCost;

    Node startNode = {start % n, start / n, 0, 0, 0};
    Node endNode = {end % n, end / n, 0, 0, 0};

    startNode.hCost = heurManhattan(startNode, endNode);
    startNode.fCost = startNode.hCost;

    nodes.push(startNode);
    gCost[start] = 0;

    while (!nodes.empty())
    {
        Node current = nodes.top();
        nodes.pop();

        int curIndex = current.x + current.y * n;
        if (visited.find(curIndex) != visited.end()) continue;
        steps.push_back(curIndex);

        if (curIndex == end)
        {
            return;
        }

        visited.insert(curIndex);
        const vector<Cell> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
        for (auto& dir : directions)
        {
            int x = current.x + dir.x;
            int y = current.y + dir.y;
            if ((x > 0) && (x < n) && (y > 0) && (y < n - 1))
            {
                int neighbour = x + y * n;

                if (visited.find(neighbour) == visited.end() && (adMatrix[curIndex][neighbour] == 1))
                {
                    int curgCost = gCost[curIndex] + 1;

                    if (!gCost.count(neighbour) || curgCost < gCost[neighbour])
                    {
                        gCost[neighbour] = curgCost;
                        Node neigh = { x, y, curgCost, heurManhattan({x, y, 0, 0, 0}, endNode), 0 };
                        neigh.fCost = neigh.gCost + neigh.hCost;
                        nodes.push(neigh);
                    }
                }
            }
        }
    }
}

void GraphVisualizer()
{
    // Layout and text
    const int marginX = 20;
    const int marginY = 20;
    const int horizontalGap = 20;
    const int verticalGap = 50;
    const int textLineHeight = 25;

    // Maze initial values
    int cellSize, n = INT_MAX;
    int dfsStep = 0, bfsStep = 0, aStep = 0;
    int maxN = 231;

    while ((n > maxN) || (n % 2 == 0) || (n <= 1))
    {
        cout << "Enter odd maze size n (maximum allowed: " << maxN << "): ";
        if (cin >> n)
        {
            if ((n > maxN) || (n % 2 == 0) || (n <= 1))
            {
                cout << n << "n is too large, too small or even, enter again\n";
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

    // HERE: 1680 - width, 1050 - height
    int cellSizeWidth = (1050 - 2 * marginX - horizontalGap) / (2 * n);
    int cellSizeHeight = (1680 - 2 * marginY - verticalGap - 2 * textLineHeight) / (2 * n);
    cellSize = max(1, min(cellSizeWidth, cellSizeHeight));

    vector<vector<int>> maze(n, vector<int>(n, 1)); // 1 = wall, 0 = path
    vector<vector<int>> adMatrix(n * n, vector<int>(n * n, 0)); // 1 = adjacent, 0 = not
    vector<int> dfsPath, bfsPath, DijkstraPath, aPath;

    generateMaze(1, 1, maze, n); // Maze generation
    
    // Adjacent matrix filling
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (maze[i][j] == 0)
            {
                if ((j + 1 < n) && (maze[i][j + 1] == 0))
                {
                    adMatrix[i * n + j][i * n + j + 1] = 1;
                    adMatrix[i * n + j + 1][i * n + j] = 1;
                }
                if ((i + 1 < n) && (maze[i + 1][j] == 0))
                {
                    adMatrix[i * n + j][(i + 1) * n + j] = 1;
                    adMatrix[(i + 1) * n + j][i * n + j] = 1;
                }
            }
        }
    }

    // Algorithms execution
    aStar(n, (n - 2) * n + n - 1, adMatrix, aPath);
    BFS(n, (n - 2) * n + n - 1, adMatrix, bfsPath);
    DFS(n, (n - 2) * n + n - 1, adMatrix, dfsPath);

    // Offsets
    int topRowWidth = 2 * n * cellSize + horizontalGap;
    int topRowStartX = (1680 - topRowWidth) / 2;

    int dfsOffsetX = topRowStartX;
    int dfsOffsetY = marginY;
    int bfsOffsetX = topRowStartX + n * cellSize + horizontalGap;
    int bfsOffsetY = marginY;
    int topTextY = marginY + n * cellSize + 5;
    int aStarOffsetX = marginX + (1680 - 2 * marginX - n * cellSize) / 2;
    int aStarOffsetY = marginY + n * cellSize + verticalGap + textLineHeight;
    int aStarTextY = aStarOffsetY + n * cellSize + 5;

    sf::RenderWindow window(sf::VideoMode(1680, 1050), "Graph Visualizer");

    sf::Font font;
    if (!font.loadFromFile("fonts/OpenSans-Regular.ttf"))
    {
        cout << "Error: font not found\n";
        return;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Mazes drawing
        drawMaze(window, maze, cellSize, n, aPath, aStep, aStarOffsetX, aStarOffsetY);
        drawMaze(window, maze, cellSize, n, dfsPath, dfsStep, dfsOffsetX, dfsOffsetY);
        drawMaze(window, maze, cellSize, n, bfsPath, bfsStep, bfsOffsetX, bfsOffsetY);

        // Data visualization
        drawText(window, "DFS: " + to_string(dfsStep) + "/" + to_string(dfsPath.size() - 1), dfsOffsetX, topTextY, font);
        drawText(window, "BFS: " + to_string(bfsStep) + "/" + to_string(bfsPath.size() - 2), bfsOffsetX, topTextY, font);
        drawText(window, "A*: " + to_string(aStep) + "/" + to_string(aPath.size() - 1), aStarOffsetX, aStarTextY, font);

        window.display();

        // Steps
        if (dfsStep < dfsPath.size() - 1) dfsStep++;
        if (bfsStep < bfsPath.size() - 1) bfsStep++;
        if (aStep < aPath.size() - 1) aStep++;

        if ((dfsStep == dfsPath.size() - 1) && (bfsStep == bfsPath.size() - 1) && (aStep == aPath.size() - 1))
        {
            cout << "\nEnter to leave\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            window.close();
            return;
        }
    }
}

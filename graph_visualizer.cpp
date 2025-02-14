#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Cell 
{
    int x, y;
};

void drawMaze(sf::RenderWindow& window, vector<vector<int>>& maze, int cellSize, int n, vector<int> steps, int stepIndex)
{
    window.clear();
    for (int y = 0; y < n; y++)
    {
        for (int x = 0; x < n; x++)
        {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(x * cellSize, y * cellSize);
            cell.setFillColor(maze[y][x] == 1 ? sf::Color::Black : sf::Color::White);
            window.draw(cell);
        }
    }

    for (int i = 0; i <= stepIndex && i < steps.size(); i++)  // Drawing steps
    {
        int pos = steps[i];
        int x = pos % n;
        int y = pos / n;

        sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
        cell.setPosition(x * cellSize, y * cellSize);
        cell.setFillColor(sf::Color::Cyan);
        window.draw(cell);
    }

    window.display();
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
    steps.push_back(start);

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
    steps.push_back(start);

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
}

void Dijkstra(int start, int end, vector<vector<int>>& adMatrix, vector<int>& steps)
{

}

void aPath(int start, int end, vector<vector<int>>& adMatrix, vector<int>& steps)
{

}

void GraphVisualizer()
{
    // Maze initial values
    int n = 281;
    int cellSize = 4;
    int stepIndex = 0;

    vector<vector<int>> maze(n, vector<int>(n, 1)); // 1 = wall, 0 = path
    vector<vector<int>> adMatrix(n * n, vector<int>(n * n, 0)); // 1 = adjacent, 0 = not
    vector<int> dfsPath, bfsPath, DijkstraPath, aPath;

    generateMaze(1, 1, maze, n); // Maze generation
    
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

    BFS(n, (n - 2) * n + n - 1, adMatrix, bfsPath);
    //DFS(n, (n - 2) * n + n - 1, adMatrix, dfsPath);

    sf::RenderWindow window(sf::VideoMode(n * cellSize, n * cellSize), "Graph Visualizer");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        drawMaze(window, maze, cellSize, n, bfsPath, stepIndex);
        //drawMaze(window, maze, cellSize, n, dfsPath, stepIndex);

        if (stepIndex < bfsPath.size())  // if (stepIndex < dfsPath.size())
        {
            stepIndex++;
            //sf::sleep(sf::milliseconds(10)); // Slowing down for visibility
        }
    }
}

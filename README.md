# Algorithm Visualizer

## Overview
This project implements a visualizer for some of the algorithms using C++ and the SFML graphics library. The visualizer allows users to choose between algorithms and take a look at how they actually work through dynamic visualization

## Main Features
### Main Menu
- Menu from which users can select a specific algorithm to visualize by clicking respective buttons
### Algorithms
#### Knapsack Problem
- Visual representation of the dynamic programming table (Tabulation aproach)
- Highlighting of current elements and paths taken to reach the solution
- Displaying total weight, capacity, total value, and indices of items included in the optimal solution
#### Sorting Algorithms
- Visual representation of array sorting progress for multiple algorithms simultaneously (Bubble Sort, Insertion Sort, Merge Sort, Quick Sort)
- Highlighting of currently compared or swapped element during each step
- Displaying current step count for each sorting algorithm individually
- Dynamic bar-like representation of each number for better visualization
#### Two Pointer (based on [Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/description/) Leetcode problem)
- Visual representation of the height bars and the amount of trapped water at each step using Two Pointer
- Dynamic highlighting of the left and right pointers during the traversal
- Displaying current positions of pointers and step progress
- Allows to both enter values of the bars manually or generate them randomly
#### Binary Search
- Visual representation of the binary search process over a sorted array
- Highlighting search range along with the target element
- Displaying step number, current low, mid, and high indices, and the target value at each stage
#### Graph Traversal Algorithms
- Procedural generation of a random maze using the Recursive Backtracker (randomized DFS) algorithm
- Visual side-by-side comparison of Depth-First Search (DFS), Breadth-First Search (BFS), and A* Search algorithms
- Highlighting of current traversal nodes (red for current step, cyan for visited)
- Real-time display of traversal progress (current step out of total steps) for each algorithm
- Efficient rendering using SFML’s vertex arrays for smooth animation and performance
- Displaying current step number and total steps for each algorithm

## Additional Features
### Input validation
- All algorithms include user input validation to ensure proper functioning and avoid unexpected errors
### Dynamic scaling
- All algorithms scale visuals' size up or down depending on the user's input for better visualization 
### Showcase options
- Most algorithms allow to choose between manually going through the steps (by left-clicking) or allowing program to automatically go to the next step of the algorithm
### Tests
- A **Tests/src** folder contains unit tests written using the Catch2 testing framework
- Tests are available for:
  - Knapsack Problem
  - Two Pointer
  - Binary Search
### Executable
- **Executable** folder contains compiled .exe file for immediate use without needing to compile the project manually

## Tech Stack
- **Language**: C++17
- **Graphics Library**: SFML
- **Testing Framework**: Catch2

## Repository Structure
- **Executable** folder: contains .exe executable for visualizer, as well as dependencies needed for execution
- **Tests** folder: contains catch_amalgamated.cpp/hpp files to use as a testing framework, **src** folder with code used for testing specified algorithms, and **Tests** folder with **Tests** project (.vcxproj) used to run the code
- **Visualizer** folder: contains all the main code for algorithm visualizations, as well as sfml.dll files and **fonts** folder required to execute the code
- **libraries** folder: contains needed libraries (mainly SFML)
- Other files: Solution (.sln), **Visualizer** project files (.vcxproj)

## Getting Started

### Prerequisites
To run this project, ensure you have the following installed on your machine:

- **C++ Compiler**: Make sure you have a C++15 (or later) compatible compiler (e.g., GCC, Clang) (personally, used C++17)
- **SFML**: Although SFML library is in the repository, you might need to properly set it up depending on your IDE. For further infotmation, check out SFML website [here](https://www.sfml-dev.org/) and use Internet to help you

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/Menma2021/Algorithm_visualizer.git
   cd Algorithm_visualizer
2. Link the SFML libraries to your project. Depending on your IDE or build system, you may need to configure this step directly by yourself

## Usage
### Algorithm Visualizer
1. Run the executable, use Solution and projects inside the repository or build the project yourself
2. Main file of the project (with main) - menu.cpp. Upon running it, main menu appears with labeled buttons used to choose the algorithm 
3. Chosoe the algorithm and follow the instructions:
   - For example, for Knapsack:
     - Enter maximum weight allowed inside the knapsack, and total amount of items available (personally recommend to use 40 - 30 (also, better looks when the maximum weight is bigger than the number of items))
     - Indicate whether program should work automatically or on the left-click
     - Input the weights and prices of each item (recommend using any random number generator and generate n entires of 2 values (weight + price of an item) (where n is the number of items from first entry)
     - Observe or spam left-click
4. Upon visualization ends, press *Enter* inside the console to return to main menu and pick different algorithm to look at

## Future improvements
1. Providing even more detailed visual explanations during the execution
2. Adding more algorithm visualization options
3. Adding more tests
4. Expending on graph traversal algorithms (different maze creation algorithm for more fair showcase of traversal algorithms; Adding option to generate maze with "traps" to be able to showcase Dijkstra's algorithm)

## Contribution
Contributions are welcome! If you have suggestions or improvements, feel free to fork the repository and submit a pull request

## License
This project is licensed under the MIT License

## Acknowledgements
Special thanks to the SFML community for their excellent documentation and support, as well as Catch2 framework contributors for simplifying unit testing

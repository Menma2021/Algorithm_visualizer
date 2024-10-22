# Algorithm Visualizer

## Overview
This project implements a visualizer for some of the algorithms using C++ and the SFML graphics library (currently, only Knapsack problem). The visualizer allows users to choose between algorithms and take a look at how they actually works (work in progress)

## Features
### Knapsack problem
- Visual representation of the dynamic programming table
- Highlighting of current elements and paths taken to reach the solution
- Displays total weight, capacity, total value, and indices of items included in the optimal solution

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
1. Enter the maximum weight and the number of items as it is told (personally recommend to use 40 - 30 or lower, 40 - 30 being probably the nicest looking option (also, better looks when the maximum weight is bigger than the number of items). Technically will work for the bigger values, but visuals start declining into the abyss)
2. Indicate whether program should work automatically or on the left-click
3. Input the weights and prices of each item (recommend using any random generator and generate n * 2 entries of max value (max_weight + const) (where n is number of items, const is any number you want)
4. Observe or spam left-click

## Future improvements
1. Maybe providing more information
2. Adding sorting algorithms
3. Adding graph traversal algorithms

## Contribution
Contributions are welcome! If you have suggestions or improvements, feel free to fork the repository and submit a pull request

## License
This project is licensed under the MIT License

## Acknowledgements
Special thanks to the SFML community for their excellent documentation and support

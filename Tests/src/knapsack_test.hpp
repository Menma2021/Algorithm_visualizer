#ifndef KNAPSACK_TEST_HPP
#define KNAPSACK_TEST_HPP

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// Knapsack logic copied from knapsack visualizer 
int knapsack(int n, int max_w, const vector<int>& weight, const vector<int>& price, vector<vector<int>>& knapsack)
{
    for (int i = 1; i <= n; i++)
    {
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
        }
    }
    return knapsack[n][max_w];
}

#endif

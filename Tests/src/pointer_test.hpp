#ifndef RAINWATER_TEST_HPP
#define RAINWATER_TEST_HPP

#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

using namespace std;

struct Step {
    vector<int> heights;
    vector<int> water;
    int l, r;
};

// Two Pointer logic copied from two pointer visualizer
void pointer(const vector<int>& height, vector<Step>& steps)
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

#endif

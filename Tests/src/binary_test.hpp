#ifndef BINARY_SEARCH_TEST_HPP
#define BINARY_SEARCH_TEST_HPP

#include <vector>
#include <iostream>
#include <numeric>

using namespace std;

// Binary Search logic copied from visualizer
void binaryTrace(const vector<int>& array, int target, vector<int>& midStates, vector<int>& lowStates, vector<int>& highStates)
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

// Search with the index of target in the array based on the visualizer's logic - for better testing
int binaryResult(const vector<int>& array, int target)
{
    int low = 0, high = array.size() - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (array[mid] == target)
        {
            return mid;
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

    return -1;
}

#endif

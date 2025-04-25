#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

#include "../src/pointer_test.hpp"

int totalWaterCollected(const vector<Step>& steps) // Counting total water from the array
{
    if (steps.empty()) return 0;
    const vector<int>& water = steps.back().water;
    return accumulate(water.begin(), water.end(), 0);
}

TEST_CASE("Flat Surface", "[rainwater]") 
{
    vector<int> height = {1, 1, 1, 1};
    vector<Step> steps;
    pointer(height, steps);

    REQUIRE(totalWaterCollected(steps) == 0); // No water fits
}

TEST_CASE("Simple Curve", "[rainwater]") 
{
    vector<int> height = {3, 0, 2, 0, 4};
    vector<Step> steps;
    pointer(height, steps);

    REQUIRE(totalWaterCollected(steps) == 7); // 0 + 3 + 1 + 3 + 0 = 7
}

TEST_CASE("Increasing Elevation", "[rainwater]") 
{
    vector<int> height = {1, 2, 3, 4, 5};
    vector<Step> steps;
    pointer(height, steps);

    REQUIRE(totalWaterCollected(steps) == 0); // Water "runs down"
}

TEST_CASE("Decreasing Elevation", "[rainwater]") 
{
    vector<int> height = {5, 4, 3, 2, 1};
    vector<Step> steps;
    pointer(height, steps);

    REQUIRE(totalWaterCollected(steps) == 0); // Water "runs down"
}

TEST_CASE("Multiple Curves", "[rainwater]") 
{
    vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    vector<Step> steps;
    pointer(height, steps);

    REQUIRE(totalWaterCollected(steps) == 6); // From LeetCode
}

TEST_CASE("Large Values", "[rainwater]") 
{
    vector<int> height = {20, 29, 32, 88, 37, 53, 14, 90, 11, 24, 68, 1, 19, 47, 82, 70, 48, 27, 9, 17, 26, 10, 83, 16, 58, 67, 69, 31, 30, 8};
    vector<Step> steps;
    pointer(height, steps);

    REQUIRE(totalWaterCollected(steps) == 929); // Checked with LeedCode
}
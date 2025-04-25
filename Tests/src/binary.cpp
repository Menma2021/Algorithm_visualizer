#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

#include "../src/binary_test.hpp"

TEST_CASE("Index For All Values In A Full Sequence", "[binaryResult]") 
{
    const int n = 100;
    vector<int> arr(n);
    iota(arr.begin(), arr.end(), 1);  // Fill with 1-100

    for (int i = 1; i <= n; i++) 
    {
        int idx = binaryResult(arr, i);
        REQUIRE(idx >= 0);
        REQUIRE(arr[idx] == i);
    }
}

TEST_CASE("Tracking Mid, Low, High For Leftmost Element", "[binaryTrace]") 
{
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
    vector<int> mids, lows, highs;

    binaryTrace(arr, 1, mids, lows, highs);

    REQUIRE(arr[mids.back()] == 1);
    for (int i = 0; i < mids.size(); i++) 
    {
        REQUIRE(lows[i] <= mids[i]);
        REQUIRE(highs[i] >= mids[i]);
    }
}

TEST_CASE("Tracking Mid, Low, High For Rightmost Element", "[binaryTrace]")
{
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
    vector<int> mids, lows, highs;

    binaryTrace(arr, 7, mids, lows, highs);

    REQUIRE(arr[mids.back()] == 7);
    for (int i = 0; i < mids.size(); i++)
    {
        REQUIRE(lows[i] <= mids[i]);
        REQUIRE(highs[i] >= mids[i]);
    }
}

TEST_CASE("Tracking Mid, Low, High For Large Array", "[binaryTrace]") 
{
    vector<int> arr(1000);
    iota(arr.begin(), arr.end(), 1);  // Fill with 1-1000
    vector<int> mids, lows, highs;

    binaryTrace(arr, 97, mids, lows, highs);

    REQUIRE(arr[mids.back()] == 97);

    for (int i = 0; i < mids.size(); i++) 
    {
        REQUIRE(lows[i] <= mids[i]);
        REQUIRE(highs[i] >= mids[i]);
    }
}

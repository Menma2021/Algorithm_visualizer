#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

#include "../src/knapsack_test.hpp"

TEST_CASE("Basic Test", "[knapsack]") 
{
    int n = 3;
    int max_w = 50;
    vector<int> weight = {10, 20, 30};
    vector<int> price = {60, 100, 120};
    vector<vector<int>> ks(n + 1, vector<int>(max_w + 1, 0));

    int result = knapsack(n, max_w, weight, price, ks);

    REQUIRE(result == 220); // 20 + 30 weight = 50, 100 + 120 = 220
}

TEST_CASE("All Items Fit", "[knapsack]") 
{
    int n = 3;
    int max_w = 60;
    vector<int> weight = {10, 20, 30};
    vector<int> price = {10, 20, 30};
    vector<vector<int>> ks(n + 1, vector<int>(max_w + 1, 0));

    int result = knapsack(n, max_w, weight, price, ks);

    REQUIRE(result == 60); // All items fit exactly, total price = 60
}

TEST_CASE("No Items Fit", "[knapsack]") 
{
    int n = 2;
    int max_w = 5;
    vector<int> weight = {10, 20};
    vector<int> price = {100, 200};
    vector<vector<int>> ks(n + 1, vector<int>(max_w + 1, 0));

    int result = knapsack(n, max_w, weight, price, ks);

    REQUIRE(result == 0); // Nothing fits
}

TEST_CASE("One Item Chosen", "[knapsack]") 
{
    int n = 2;
    int max_w = 15;
    vector<int> weight = {10, 20};
    vector<int> price = {60, 100};
    vector<vector<int>> ks(n + 1, vector<int>(max_w + 1, 0));

    int result = knapsack(n, max_w, weight, price, ks);

    REQUIRE(result == 60); // Only the first item fits
}

TEST_CASE("Large Input", "[knapsack][large]") {
    int n = 15;
    int max_w = 100;
    vector<int> weight = {5, 10, 15, 20, 7, 8, 9, 11, 13, 14, 6, 12, 4, 3, 17};
    vector<int> price = {10, 40, 30, 50, 25, 28, 35, 45, 42, 38, 15, 33, 8, 6, 60};

    vector<vector<int>> ks(n + 1, vector<int>(max_w + 1, 0));

    int result = knapsack(n, max_w, weight, price, ks);

    REQUIRE(result == 338); // Checked with the code from GeekForGeeks
}

#include <bits/stdc++.h>
using namespace std;

// Function to find the optimal split points of the matrix chain
vector<vector<int>> get_optimal_split(int dimensions[], int size)
{
    int numMatrices = size - 1; //m = cost, s=splitPoints
    vector<vector<int>> cost(numMatrices + 1, vector<int>(numMatrices + 1));
    vector<vector<int>> splitPoints(numMatrices + 1, vector<int>(numMatrices + 1));

    // Initialize diagonal elements to 0 (cost of multiplying a single matrix)
    for (int i = 1; i <= numMatrices; i++)
    {
        cost[i][i] = 0;
    }

    // Compute costs for all possible chain lengths and split points
    for (int chainLength = 2; chainLength <= numMatrices; chainLength++)
    {
        for (int start = 1; start <= numMatrices - chainLength + 1; start++)
        {
            int end = start + chainLength - 1;
            cost[start][end] = INT_MAX;

            // Try all possible split points within the current chain
            for (int split = start; split < end; split++)
            {
                int currentCost = cost[start][split] + cost[split + 1][end] + dimensions[start - 1] * dimensions[end] * dimensions[split];
                if (currentCost < cost[start][end])
                {
                    cost[start][end] = currentCost;
                    splitPoints[start][end] = split;
                }
            }
        }
    }

    // Return the matrix of optimal split points
    return splitPoints; //return s
}

// Recursive function to print the optimal way of multiplying the matrices in the chain
void print_optimal(vector<vector<int>> splitPoints, int start, int end)
{
    if (start == end)
    {
        // Base case: single matrix
        cout << "A" << start;
    }
    else
    {
        // Recursive case: split the chain at the optimal point and print the sub-chains
        int optimalSplit = splitPoints[start][end];
        cout << "(";
        print_optimal(splitPoints, start, optimalSplit);
        print_optimal(splitPoints, optimalSplit + 1, end);
        cout << ")";
    }
}

// Main function to test the matrix chain multiplication algorithm
int main()
{
    // Example 1: chain of matrices with dimensions {5x4, 4x6, 6x2, 2x7}
    int dimensions1[] = {5, 4, 6, 2, 7};
    int numMatrices1 = sizeof(dimensions1) / sizeof(dimensions1[0]);
    vector<vector<int>> splitPoints1 = get_optimal_split(dimensions1, numMatrices1);
    print_optimal(splitPoints1, 1, numMatrices1 - 1);
    cout << endl;

    // Example 2: chain of matrices with dimensions {4x4, 4x6, 6x12, 12x7}
    int dimensions2[] = {4, 4, 6, 12, 7};
    int numMatrices2 = sizeof(dimensions2) / sizeof(dimensions2[0]);
    vector<vector<int>> splitPoints2 = get_optimal_split(dimensions2, numMatrices2);
    print_optimal(splitPoints2, 1, numMatrices2 - 1);
}

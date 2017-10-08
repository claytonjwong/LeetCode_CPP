/*
 
 695. Max Area of Island
 
 https://leetcode.com/contest/leetcode-weekly-contest-53/problems/max-area-of-island/
 
 Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.
 
 Find the maximum area of an island in the given 2D array. (If there is no island, the maximum area is 0.)
 
 Example 1:
 [[0,0,1,0,0,0,0,1,0,0,0,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,1,1,0,1,0,0,0,0,0,0,0,0],
 [0,1,0,0,1,1,0,0,1,0,1,0,0],
 [0,1,0,0,1,1,0,0,1,1,1,0,0],
 [0,0,0,0,0,0,0,0,0,0,1,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,0,0,0,0,0,0,1,1,0,0,0,0]]
 Given the above grid, return 6. Note the answer is not 11, because the island must be connected 4-directionally.
 Example 2:
 [[0,0,0,0,0,0,0,0]]
 Given the above grid, return 0.
 Note: The length of each dimension in the given grid does not exceed 50.
 
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m=0;
        for (int r=0; r<grid.size(); ++r){
            for (int c=0; c<grid[0].size(); ++c){
                if (grid[r][c]){
                    int curr=dfs(grid,r,c);
                    m=max(m,curr);
                }
            }
        }
        return m;
    }
    
private:
    int dfs(vector<vector<int>>& grid, int r, int c){
        if (!(0<=r&&r<grid.size() && 0<=c&&c<grid[0].size())) return 0;
        if (!grid[r][c]) return 0;
        grid[r][c]=0;
        return 1
            +dfs(grid,r-1,c)  // top
            +dfs(grid,r,c+1)  // right
            +dfs(grid,r+1,c)  // bottom
            +dfs(grid,r,c-1); // left
    }
};

int main(int argc, const char * argv[]) {
    
    Solution solution;
    
    vector<vector<int>> grid =
       {{0,0,1,0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,1,1,0,0,0},
        {0,1,1,0,1,0,0,0,0,0,0,0,0},
        {0,1,0,0,1,1,0,0,1,0,1,0,0},
        {0,1,0,0,1,1,0,0,1,1,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,1,1,1,0,0,0},
        {0,0,0,0,0,0,0,1,1,0,0,0,0}};
    
    cout << solution.maxAreaOfIsland(grid) << endl;
    
    
    return 0;
}




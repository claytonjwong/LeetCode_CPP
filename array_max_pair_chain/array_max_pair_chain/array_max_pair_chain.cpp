/*
 
 646. Maximum Length of Pair Chain
 
 https://leetcode.com/problems/maximum-length-of-pair-chain/description/
 
 You are given n pairs of numbers. In every pair, the first number is always smaller than the second number.
 
 Now, we define a pair (c, d) can follow another pair (a, b) if and only if b < c. Chain of pairs can be formed in this fashion.
 
 Given a set of pairs, find the length longest chain which can be formed. You needn't use up all the given pairs. You can select pairs in any order.
 
 Example 1:
 Input: [[1,2], [2,3], [3,4]]
 Output: 2
 Explanation: The longest chain is [1,2] -> [3,4]
 Note:
 The number of given pairs will be in the range [1, 1000].
 
 */

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(),pairs.end(),
             [](const vector<int>& lhs, const vector<int>& rhs){
                 return lhs[1]==rhs[1] ? lhs[0] < rhs[0] : lhs[1] < rhs[1];});
        int last=INT_MIN,cnt=0;
        for (auto &&pair: pairs){
            if (last<pair[0]){
                last=pair[1];
                ++cnt;
            }
        }
        return cnt;
    }
};

int main(int argc, const char * argv[]) {
    
    vector<vector<int>> test{
        {-10,-8},
        {8,9},
        {-5,0},
        {6,10},
        {-6,-4},
        {1,7},
        {9,10},
        {-4,7}
    };
    
    Solution solution;
    cout << solution.findLongestChain(test) << endl;
    
    return 0;
}





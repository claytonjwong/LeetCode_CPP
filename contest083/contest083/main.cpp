/*
 
 Rank           Name            Score   Finish Time     Q1 (3)      Q2 (5)      Q3 (7)    Q4 (9)
 799 / 2688     claytonjwong    8       0:47:57         0:12:53     0:42:57  1
 
 Q1: https://leetcode.com/contest/weekly-contest-83/problems/positions-of-large-groups/
 A1: https://leetcode.com/problems/positions-of-large-groups/discuss/129394/Straightforward-C++
 
 Q2: https://leetcode.com/problems/masking-personal-information/description/
 A2: https://leetcode.com/problems/masking-personal-information/discuss/129400/Straightforward-C++
 
 
 
 */

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <numeric>

using namespace std;

/*
class Solution {
public:
    vector<vector<int>> largeGroupPositions(string S) {
        vector<vector<int>> ans;
        for (int i=0,j=i+1,N=(int)S.size(); i<N-2; i=j,j=i+1){
            while (j<N && S[i]==S[j])
                ++j;
            if (j-i > 2)
                ans.emplace_back(vector<int>({i,j-1}));
        }
        return ans;
    }
};
*/



class Solution {
public:
    string maskPII(string S) {
        auto pos=S.find('@');
        if (pos==string::npos)
            return phone(S);
        else
            return email(S,(int)pos);
    }
private:
    string phone(const string& S){
        string ans,digits;
        for (int i=0; i<(int)S.size(); ++i)
            if (isdigit(S[i]))
                digits.push_back(S[i]);
        if (digits.size() > 10)
            ans.append("+"+string(digits.size()-10,'*')+"-");
        ans.append("***-***-"+digits.substr(digits.size()-4));
        return ans;
    }
    string email(const string& S, const int pos){
        string ans=S.substr(0,1)+"*****"+S.substr(pos-1);
        transform(ans.begin(),ans.end(),ans.begin(),::tolower);
        return ans;
    }
};


/*
Submission Result: Time Limit Exceeded
Last executed input:
933320757
*/
/*
 // TLE
 
class Solution {
public:
    int consecutiveNumbersSum(int N) {
        if (N<3) return 1;
        int ans=1;
        for (int i=1,j=2,sum=i+j; j<=N/2+1;){
            if (sum < N){
                sum+=++j;
            } else {
                if (sum==N)
                    ++ans;
                sum-=i++;
            }
        }
        return ans;
    }
};*/

/*
class Solution {
public:
    int consecutiveNumbersSum(int N) {
        return go(N,N);
    }
private:
    int go(int i, const int T){
        if (i==T)
            return 1+go(i/2,T)+go(i/2+1,T);
        if (i<2)
            return i/2*(i+1)==T ? 1 : 0;
        int sum=i+(i+1);
        for (int j=i+1; sum<T;)
            sum+=++j;
        return ( sum==T ? 1 : 0 ) + go(i/2,T) + go(i/2+1,T);
    }
};
*/


int main(int argc, const char * argv[]) {
    
    /*
    Solution s;
    
    auto r=s.largeGroupPositions("aaa");
    */
    
    
    Solution s;
    auto r=s.maskPII("86-(10)12345678");
    
    
    /*
    Solution s;
    cout << s.consecutiveNumbersSum(15) << endl;;
    */
    
    return 0;
}



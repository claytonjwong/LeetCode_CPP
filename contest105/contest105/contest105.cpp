/*

https://leetcode.com/contest/weekly-contest-105

Rank            Name            Score   Finish Time     Q1 (4)    Q2 (6)    Q3 (7)    Q4 (8)
1490 / 3528     claytonjwong    4       0:12:02         0:12:02

Q1: https://leetcode.com/problems/reverse-only-letters/description/
A1: https://leetcode.com/problems/reverse-only-letters/discuss/178409/Concise-C++


*/


#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>


using namespace std;

/*
class Solution {
public:
    string reverseOnlyLetters( string A, vector<char> s = {}, string ans = {} ) {
        for( const auto c: A )
            if( isalpha( c )) s.push_back( c );
        for( size_t i{ 0 }, j{ s.size() };  i < A.size();  ++i )
            ans.push_back( isalpha( A[i] ) ? s[--j] : A[i] );
        return ans;
    }
};
*/

/*
Use a vector of chars as a ```s```tack to store letters from input string ```A```.

Iterate one ```i```ndex at a time through A to create the ```ans```wer to be returned:

if the character at the ```i```ndex is a letter, then append onto ```ans```swer the letter at the top of the ```s```tack ( ```j``` is the index one-past the current "top" of the ```s```tack )
else the character at the ```i```ndex is a non-letter, then append onto ```ans```wer the original non-letter from ```A```
*/
/*
class Solution {
public:
    string reverseOnlyLetters( string A, vector<char> s={} ) {
        copy_if( A.begin(), A.end(), back_inserter( s ),
            []( const auto c ){ return isalpha( c ); });
        auto j=s.size();
        transform( A.begin(), A.end(), A.begin(),
            [&]( const auto c ){ return isalpha( c ) ? s[--j] : c; });
        return A;
    }
};
*/
/*
class Solution {
public:
    string reverseOnlyLetters( string A, vector<char> letters={} ) {
        copy_if( A.begin(), A.end(), back_inserter( letters ),
            []( const auto c ){ return isalpha( c ); });
        auto it{ letters.rbegin() };
        transform( A.begin(), A.end(), A.begin(),
            [&]( const auto c ){ return isalpha( c ) ? *it++ : c; });
        return A;
    }
};
*/
/*
class Solution {
public:
    string reverseOnlyLetters( string A ) {
        for( int N{ static_cast<int>(A.size()) }, i{ 0 }, j{ N-1 };  i < j; )
            if( ! isalpha( A[i] ))
                ++i;
            else if( ! isalpha( A[j] ))
                --j;
            else
                swap( A[i++], A[j--] );
        return A;
    }
};
*/

class Solution {
public:
    string reverseOnlyLetters( string A ) {
        if( ! A.empty() ){
            for( auto i{ A.begin() }, j{ prev(A.end()) };  i < j;)
                if( ! isalpha( *i ))
                    ++i;
                else if( ! isalpha( *j ))
                    --j;
                else
                    iter_swap( i++, j-- );
        } return A;
    }
};

int main(int argc, const char * argv[]) {
    
    Solution s;
    
    
    cout << ("dc-ba" == s.reverseOnlyLetters("ab-cd") ) << endl;
    cout << ("j-Ih-gfE-dCba" == s.reverseOnlyLetters("a-bC-dEf-ghIj") ) << endl;
    cout << ("Qedo1ct-eeLg=ntse-T!" == s.reverseOnlyLetters("Test1ng-Leet=code-Q!")) << endl;
    
    
    
    return 0;
}

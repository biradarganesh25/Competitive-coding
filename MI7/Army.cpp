// Problem Title: Army

// Problem description: Specific skills of soliders are represented by different characters. You are given two strings representing the skills of soliders in
//                      in two different groups. You have to form a formation of soliders from both groups. At each time you can select soldier from either of
//                      the two groups and you can only insert that solider to the end of the result formation. You have to create a formation that performs the best.
//                      And in the resultant formation, you have to count the number of units, and output it.

// Solution description: In the very first sentence of the problem statement it's given that, soliders with same skills perform better.
//                       And in the question it is given that we have to create a formation that performs the best.
//                       The key question here is: When will the formation perform the best?
//                       The answer being: The formation performs best when maximum number of soliders with same skills are group together.
//                       Which also means that: The formation will have miniumum number of units. (maximum number of people grouped together -> minimum number of units in the final formation)
//                       So the final conclusion being: We have to merge the two strings, in such a way that it has minimum number of units.
//
//                       One may think that greedy solution would work. But it won't. (why?)
//                       Two steps can be followed:
//                              1. Think through the solution in recursion, and then simply cache it.
//                              2. There is no step 2, step 1 will give you the answer.

//                       We shall define a recursive function, that takes three parameters, first being a pointer to the first string.
//                       Second parameter being a pointer to the second string, and a third parameter prev, which can only take two values(0 or 1) indicating from
//                       which string (first or second respectively) did we previously choose the character from.
//
//                      We have to define another function, which takes a string parameter, and an index i, and outputs the number of units in the input string, from ith position.


// Template starts
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
#define REP(i, j) rep(i, 0, j)
#define test int ca; cin>>ca; while(ca--)
#define deb(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
#define io  ios_base::sync_with_stdio(false);cin.tie(NULL);if(fopen("../input.txt", "r")) freopen("../input.txt", "r", stdin);
#define cstart clock_t start_tm = clock()
#define cend cout<<"Time = "<<clock() - start_tm<<" ms"<<endl;

void err(istream_iterator<string> it) {}

template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

const ll mod = 1000000007;
//Template ends

const int N = 2500;
string s, t;
int dp[N][N][2];

int calc_blocks(string sa, int i) {
    int res = 1;
    for (int k = i + 1; k < sa.length(); k++)
        if (sa[k] != sa[k - 1]) res++;
    return res;
}

// At each step, we check if the character selected in the currenst step is different than the character selected in the previous step, if so, we add 1.
int recurse(int i, int j, int prev) {
    if (dp[i][j][prev] != -1) return dp[i][j][prev];
    char prev_char = (prev) ? t[j-1] : s[i-1]; // Get the previous character that was selected
    if (i ==
        s.length()) { // ith pointer has reached the end of first string, simply add all characters from the second string.
        return dp[i][j][prev] = calc_blocks(t, j) + ((t[j] != prev_char) ? 1 : 0);
    }
    if (j == t.length()) { // Same as above, but for the second string.
        return dp[i][j][prev] = calc_blocks(s, i) + ((s[i] != prev_char) ? 1 : 0);
    }
    // Select a character from the first string and recurse.
    int res1 = recurse(i + 1, j, 0) + ((s[i] != prev_char) ? 1 : 0);
    // Select a character from the second string and recurse.
    int res2 = recurse(i, j + 1, 1) + ((t[j] != prev_char) ? 1 : 0);
    // Take the min of both and assign it as answer to this dp state.
    int res = min(res1, res2);
    return dp[i][j][prev] = res;
}


int main() {
    io
    test {
        MEM(dp, -1); // clear the cache
        int n, m;
        cin>>n>>m;
        cin>>s>>t;
        deb(s, t);
        cout<<min(recurse(1,0, 0), recurse(0, 1, 1))<<endl;
    };
}


// Conclusion: I expected this problem to be solved by more teams, it turns out only one team was able to understand
//             the question and solve it correctly.
//             The only reason the recursive dp works within the time limits, is because the input length is small.

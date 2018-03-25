// Problem Name: Two Players

// Problem Description: Basically there are two players( A & B) each with a string, and they play in turns. At each turn, a player can select any character
//                      from his string, and place it anywhere in the result string. And when the result string becomes a palindrome, the player who inserted the
//                      last character wins. If you can't make a palindrome, then player B wins.


// Solution Description: Since we know that if it's not possible to make a palindrome, player B wins, we simply check for which all cases player A would win.
//                       There are only two cases when player A would win.
//                 Case 1: When there is a character present in A, and absent in B. and the frequency of that character is >1.
//                      Ex: A:abdd  B:abaa
//                      Player A would win by selecting d in his first move, and then again d in his next turn.
//                  Case 2: When all the characters of B are also present in A and if there is a single character in A that is not present in B.
//                      Ex: A:abcb  B:abbb
//                      Player A would win by select c in his first move.

// Template
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
#define REP(i, j) rep(i, 0, j)
#define test int t; cin>>t; while(t--)
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

int main() {
    io
    test { // For each test case.
        
        // Code starts from here.
        string s, t;
        cin>>s>>t;
        bool flag1 = false, flag2 = false, flag3 = false;
        map<char, int> freqa, freqb;
        
        REP(i, s.length()){
            freqa[s[i]]++;
        }
        REP(i, t.length()){
            freqb[t[i]]++;
        }
        
        for(char i = 'a'; i <= 'z'; i++){
            if(freqa[i] > 1 and freqb[i] ==0)
                flag1 = true; // Case 1
            if(freqa[i] != 0 and freqb[i] == 0)
                flag2 = true; // If there is char present in A, absent in B
            if(freqa[i] == 0 and freqb[i] != 0)
                flag3 = true; // If there is char present in B, absent in A
        }
        
        if(flag1){
            cout<<"A"<<endl;
        }else if(flag2 and !flag3){
            cout<<"A"<<endl;
        }else{
            cout<<"B"<<endl;
        }
    };
}

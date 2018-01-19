// Problem Link : https://www.codechef.com/problems/MONSTER
//
// Problem Description: You are given an array of lenght N, and the value of the array elements. And you have to solve for
//                      Q queries, where each query is of the form x y. where you have to reduce the value of all the array elements
//                      with y value, which satisfies the condition: i & x = i (where & is bit-wise AND operation).
//                      For each query you have to output the number of positive elements left in the array after the query operation.
//
// Pre-requisites: Sum-Over-Subsets DP (SOS) (http://codeforces.com/blog/entry/45223)
//                 Sqrt Decomposition
//
// Problem Difficulty: Intermediate
//
// Hint: We use SOS Dp along with sqrt Decomposition
//
// Solution Description:
//                  Here is the basic operation of the solution. We simply read all the queries at once, and then divide the queries into blocks.(Sqrt decomposition)
//                  For each block of queries, we compute the toal amount of the health that gets reduced for a particular index by the queries
//                  from the current block. Once that is calculated, we reduce the healths of each individual array elements h[i] by the amount that was previously calculated for that index.
//                  If after reducing the health at a particular block makes the h[i]<0 means that the queries in that block kills the particular monster.
//                  If after reducing the health at a partiular block makes h[i]>0 means that the queries in the particular block doesn't kill the monster i. so we simply reduce it.
//                  If it's the former case, then we also need to find out exactly at which query(query index j) the health of h[i] becomes <= 0. We store it as res[j]++.
//                  meaning that a monster was killed at query j. Finding exactly the index at which the h[i] becomes <=0 is done in brute force manner.
//
// Explanation for Sum-Over-Subset DP:
//                  I suggest you first go through the SOS dp resource mentioned above. Once you read that, come back here.
//                  Current question is slightly different than the once that's described in the tutorial.
//                  In here, instead of thinking what all indexes a particular query affects, we think differently.
//                  For a particular index i, what all values of x from the queries has effect on the index i.
//                  The base case, x & x = x. Meaning for the query x y, it definitly has the effect on index x itself, we first update that before continuing with the next step.
//                  After the previous step, all the values of y of the queries are stored in their corresponding x index.
//                  Next, consider this example for index 101, the queries with x values 111 and 101 has the effect on the index 101, since 101 & 101 = 101 and 101 & 111 = 101.
//                  So for index 101, the queries with x values 101(base case) and 111 has effect on it. Since for query with x as 101 we added the y in the base case itself, we just have to take care of
//                  query with x value as 111. So we add that as well as follow: bitmask[101] += bitmask[111]. Since bitmask[111] contains the y value from the query with x as 111.(base case for 111).
//                  In general, for every 0th bit, we have to add the health that gets reduced with that bit set as well.
//                  We have to do in this in reverse of mask because for bitmask[101], we also want value of bitmask[111](which is the total health reduced for index 111).
//                  We are generally constructing the tree in bottom up fashion. After this, we get the total health reduced for all the indexes.
//
//
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <map>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <cstdio>
#include <stack>
#include <queue>

using namespace std;
typedef long long ll;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REPI(i, j) for(ll i=1; i<=j; i++)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define pb push_back
#define deb(x) cout << #x << "=" << x << endl
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << endl
#define pb push_back
typedef vector<int> vi;
typedef vector<ll> vl;
const ll mod = 1000000007;
const int MAX = (1e9) + 17;

void solve();

int main() {
    //freopen("../input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}

// Actual solution code starts from here.

void solve() {
    // mask holds 17 1's. and bitmask array is used to hold, the health reduced for a particular index in the current block
    int mask = (1 << 17) - 1, n, bitmask[(1 << 18) + 1];
    cin >> n;
    int h[n];
    // Read health
    REP(i, n) cin >> h[i];
    int q;
    cin >> q;
    // Res[q] holds the number of monsters that gets killed at a particular query i.
    int res[q], queri[q][2];
    // set res array to zero
    MEM(res, 0);
    // Read the queries
    REP(i, q) cin >> queri[i][0] >> queri[i][1], queri[i][0] &= mask; // Apply mask on x values, as we don't care about bits more than 17 bits
    // Sqrt decomposition ( Not exactly sqrt, it doesn't matter)
    int blocksize = 2000, total_blocks = (q / blocksize) + (bool) (q%blocksize);
    // Process for each block of queries
    for (int curr_block = 0; curr_block < total_blocks; curr_block++) {
        // bitmask holds the total health reduced for a particular index after the current block of queries.
        MEM(bitmask, 0);
        // Start and end positions for the current block
        int pos = curr_block * blocksize;
        int end = min(q, pos + blocksize);

        // The base case as mentioned above.
        for (int i = pos; i < end; i++) {
            bitmask[queri[i][0]] += queri[i][1];
        }

        // Calulating the total health that gets reduced for a particular index in a bottom-up manner, you can also use the code present in tutorial for this.
        for (int bit = 0; bit <= 17; bit++) {
            for (int i = mask; i >= 0; i--) {
                if (!(i & (1 << bit))) { // if the bit is 0
                    bitmask[i] += bitmask[i ^ (1 << bit)];
                    // this step is crucial, since we are dealing with large numbers, there can be an overflow, we avoid this here. The maximum health that a monster can have is 10^9
                    bitmask[i] = min(bitmask[i], MAX);
                }
            }
        }

        // After calculating the total health loss for all indexes from the current block, we then proceed to check if this has effect on the h[i] array.
        for (int i = 0; i < n; i++) {
            if (h[i] <= 0) continue; // If that monster is already dead, then don't bother
            if (h[i] - bitmask[i] <= 0) { // If the monster dies after this block
                int temp = 0; // we check in brute force manner which query in the current block actually killed the monster
                for (int j = pos; j < end; j++) {
                    if ((i & queri[j][0]) == i) {
                        temp += queri[j][1];
                    }
                    if (h[i] - temp <= 0) { // jth query killed the monster i
                        res[j]++; // we increment res[j], meaning that a monster was killed at query j
                        break;
                    }
                }
            }
            h[i] -= bitmask[i]; // We actually reduce the health, probably killing it.
        }
    }
    int ans = n;
    // Answers
    REP(i, q) ans -= res[i], cout << ans << endl;
}

// Submission Link: https://www.codechef.com/viewsolution/17078996
// Conclusion: Although I wasn't able to solve this one in the live contest, this was nonetheless a good problem. Wish I had known about this before.
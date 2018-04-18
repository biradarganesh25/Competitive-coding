/*
Warning: Logical awesomeness ahead, be prepared.

Problem Title: Chef and Odd Queries

Problem Link: https://www.codechef.com/problems/CHANOQ/

Problem Description: You are given N ranges of the form [L, R] where 1 <= L <= R <= N. Q queries and each query has M points in it, each Mi point is within the range 1...N.
                     For each query, you have to output the number of ranges that has odd number of points inside it.

Constraints: You have to solve for T test cases, where 1 <= T <= 100
            1 <= Q, N <= 100000
            sum of M for all queries <= N

Hint: Don't dare to even think that bruteforce method would work

Prerequisites: 1) Sqrt Decomposition.
               2) A knack of thinking problems differently.

Solution Preface: I've been wanting to write a editorial for this awesome problem the moment I understood the solution, because it's just too good.
                  Reading the prerequisites, you can start thinking about the problem in terms of sqrt decomposition, but I bet it's not as easy as you think it is,
                  and rightly so, this problem is the 7th problem in the codechef feb long contest.
                  And one small reminder is that this is not the official solution for this problem, just like most of the other editorials that I've written about.
                  There are three solutions for this problem, official one uses advanced concepts, but solution is actually dumb.
                  Another solution is using bitmasks, and this only works because of no memory limits in codechef.
                  The final solution, which I am going to explain about, uses normal sqrt decomposition, but the solution is damn clever.

Solution description: I suggest you read this editorial on sqrt decomposition - https://blog.anudeep2011.com/mos-algorithm/ - before proceeding further.
                      The very first thing we do is sort the N ranges according to sqrt decomposition rules(divide the range into sqrt(n) blocks, and sort the ranges accordingly).
                      To make the concept clear, just consider that you are solving a single query.
                      You have N ranges and M points, you have to find out the number of ranges that has odd points in it.
                      For our example consider N = 5 and M = 4, the points being [1, 3, 4, 5], there are 5 ranges - [1, 2], [2, 4], [3, 5], [4, 4], [5, 5]
                      In sqrt decomposition, you have left and right pointers. We iterate through each of the N sorted ranges, and move the left and right pointers according to the rules specified in the tutorial.
                      For each query, we maintain a vector, which is used to store the index of ranges which has passed through odd number of points while traversing left and right pointers.(explained later)
                      Initially the vector would be empty and left = right = 0.
                      We now iterate through each of the N ranges.
                      Conider the first range[1, 2], right is moved from 0 to 2 index, since there is a point 1 present in the M points, we push the value 1 to the vector, indicating the first range has odd number of points.
                      left pointer remains unchanged, as per the sqrt decomposition rules.
                      Now the vector has [1] in it, indicating that range 1 has odd number of points in it. Next comes the clever part.
                      For the second range[2, 4], the right moves from 2 to 4, covering points 3, 4, since this is even number of points, the vector is unchanged.
                      left pointer is moved from 0 to 1, and it covers the point 1, and since this is odd number of pointer, vector is pushed with value 2, indicating that for second range, the left and right pointers moved odd number of times.
                      Now the vector has values [1, 2]. Let's analyse what this means.

                      1. If the left and right pointer are in a odd state, meaning the number of pointer between them are odd.
                      and if the next range also has odd number of points in it, left and right pointers move across even number of points, as
                      odd(new range) = odd(previous odd range) + even (points traversed while moving left and right to new range)
                      since the left and right now seen even number of points, the new range index isn't pushed into the vector.

                      2. If the left and right pointer are in odd state, and the next range has even number of points in it.
                      left and right pointers move across odd number of points as
                      even(new range) = odd(previous odd range) + odd(points traversed while moving left and right to the new range)
                      since left and right now see odd number of points, the new range index is pushed into the vector.

                      3. If the left and right pointers are in even state and the next range has odd number of points, then it moves through odd number of points,as
                      odd(new range) = even(previous even range) + odd(points traversed while moving left and right to the new range)
                      since left and right now see odd number of points, the new range index is pushed into the vector.

                      4. If the left and right pointers are in even state and the next range has even number of points, then it moves through even number of points,as
                      even(new range) = even(previous even range) + even(points traversed while moving left and right to the new range)
                      since left and right now see even number of points, the new range index isn't pushed into the vector.

                      So to conclude from this analysis, initially the left and right will be in even state, when they first encouter a odd state, the index is pushed into the vector.
                      After that, subsequent ranges with odd points are not pushed into the vector, range index is pushed when a range with even number of points is encountered.
                      The vector would have [ index of range with odd points, index of range with even points ]
                      Now the left and right are back to even state, and the cycle repeats.
                      The vector would have [index of odd range, index of even range, index of odd range, index of even range....].
                      So for our answer, starting from index of odd range up until(not including) the index of even range, the ranges contain odd number of points.
                      which can be calculated by [index of even range] - [index of odd range]
                      For the above example, the vector would contain [1 ,2, 3], where 1 is index of odd range, 2 is index of even range, 3 is index of odd range.
                      One final detail in here is that, we need to append the value N+1 to the vector if the size of the vector is odd, this means that the last element is the index of a odd range,
                      all the ranges from that index to N contains odd number of points(figure this out yourself).
                      so the vector would be [1, 2, 3, 6] and our answer for that query would be (2-1) + (6-3) = 4.

                      We just have to generalize this same concept,so that we can process all the queries in one sqrt decomp traversal.
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
#define REP(i, j) rep(i, 0, j)
#define test int t; cin>>t; while(t--)
#define deb(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
#define io  ios_base::sync_with_stdio(false);cin.tie(NULL);if(fopen("../input.txt", "r")) freopen("../input.txt", "r", stdin);

void err(istream_iterator<string> it) {}

template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

const ll mod = 1000000007;
// Code starts from here

// For storing each of the N ranges
struct segments {
    int l, r, block;

    segments() {
        l = r = block = 0;
    }
};

// Sqrt decomposition way of sorting, if two ranges are in same block, we sort according to their right value
bool cmp(segments a, segments b) {
    if (a.block == b.block) return a.r < b.r;
    else return a.block < b.block;
}

int main() {
    io // Fast I/O
    test { // For each test case
        int n;
        cin >> n;
        segments s[n];
        // Sqrt decomposition, size of each block
        int sqrt_n = sqrt(n);
        // Reading N ranges, and also assigning the block id
        REP(i, n) cin >> s[i].l >> s[i].r, s[i].block = (s[i].l / sqrt_n);
        // Sorting the ranges
        sort(s, s + n, cmp);

        int q;
        cin >> q;
        // queries[q] is vector for each of the q queries, as explained above.
        // points is a vector of vector of size n+1, if query i, has a point 3, then it is stored as points[3].pushback(i)
        vector<int> points[n + 1], queries[q];
        REP(i, q) {
            int m, temp;
            cin >> m;
            // As explained above
            REP(j, m) cin >> temp, points[temp].push_back(i);
        }

        // Standard sqrt decomposition traversal as explained in the tutorial
        int currentL = 0, currentR = 0;
        REP(i, n) {
            int L = s[i].l, R = s[i].r;
            while (currentL < L) {
                // For each of the queries associated with the point currentL, we update their respective vectors
                REP(j, points[currentL].size()) {
                    if (queries[points[currentL][j]].size() != 0) {
                        // We are simply toggling the range index for particular query vector, for indicating whether the left and right pointers have moved odd number of places.
                        if (queries[points[currentL][j]].back() == i) queries[points[currentL][j]].pop_back();
                        else queries[points[currentL][j]].push_back(i);
                    } else {
                        queries[points[currentL][j]].push_back(i);
                    }
                }
                currentL++;
            }
            while (currentL > L) {
                REP(j, points[currentL - 1].size()) {
                    if (queries[points[currentL - 1][j]].size() != 0) {
                        if (queries[points[currentL - 1][j]].back() == i) queries[points[currentL - 1][j]].pop_back();
                        else queries[points[currentL - 1][j]].push_back(i);
                    } else {
                        queries[points[currentL - 1][j]].push_back(i);
                    }
                }
                currentL--;
            }
            while (currentR <= R) {
                REP(j, points[currentR].size()) {
                    if (queries[points[currentR][j]].size() != 0) {
                        if (queries[points[currentR][j]].back() == i) queries[points[currentR][j]].pop_back();
                        else queries[points[currentR][j]].push_back(i);
                    } else {
                        queries[points[currentR][j]].push_back(i);
                    }
                }
                currentR++;
            }
            while (currentR > R + 1) {
                REP(j, points[currentR - 1].size()) {
                    if (queries[points[currentR - 1][j]].size() != 0) {
                        if (queries[points[currentR - 1][j]].back() == i) queries[points[currentR - 1][j]].pop_back();
                        else queries[points[currentR - 1][j]].push_back(i);
                    } else {
                        queries[points[currentR - 1][j]].push_back(i);
                    }
                }
                currentR--;
            }
        }
        REP(i, q) {
            // We push the value N to each vector as explained in the solution description. (N because the ranges are 0 indexed, otherwise it would be N+1)
            queries[i].push_back(n);
            int s = 0;
            for (int j = 0; j < queries[i].size() - 1; j += 2)
                // [index of even range] - [index of odd range]
                s += queries[i][j + 1] - queries[i][j];
            cout << s << endl;
        }
    };
}

/*
 * Conclusion: Of course, I wasn't able to solve this problem during live contest, but I really enjoyed understanding the crux of this unofficial solution.
 *            The official author of the problem intented this to be solved in a completely different way(advanced, but not so good), this is a very good example of
 *            how different thinking can lead to a clean and elegant solution. And in many cases, this unofficial solution performs better than the official one.
 * 
 * Unofficial Editorial Link: https://discuss.codechef.com/questions/122723/chanoq-unofficial-editorial-chef-and-odd-queries-feb-long
 */

// Warning: This ain't for the faint hearted. Reader discretion is advised.
//
// Problem link: https://www.codechef.com/JULY17/problems/PSHTTR
//
// Problem description:
//           You are given a tree with N nodes and N-1 edges, each edge is associated with a
//           cost/weight. You have to solve for Q queries, where each query is of the form u v k.
//           For each query you have to ouput the xor of the cost of edges between the two nodes u, v.
//           with additional condition that you have to only select the edges whose cost is less than or equal to k.
//
// Hint: Brute force won't work
//
// Problem Difficulty: Intermediate/Hard
//
// Solution:
// Prerequisites: 1) DFS
//                2) Euler tour(http://codeforces.com/blog/entry/43230 Problem 2)
//                3) LCA using Binary lifting method in LogN (https://www.youtube.com/watch?v=6Q7OrMi0Vvc)
//                4) Binary Indexed Trees for xor queries (https://www.topcoder.com/community/data-science/data-science-tutorials/binary-indexed-trees/)
//                5) Offline query processing with BIT (solve this http://www.spoj.com/problems/DQUERY/)
//                6) Patience
//
// Solution Description:
//              We first do DFS on the tree and record the Euler tour array in the E array(which is a pair), but with a twist, instead of
//              recording the node itself, we record the cost of the edges between the nodes we traverse. and also the index poisiton of the
//              the costs. Also we record the start and end positions of each node in the E array in st[] and et[] arrays.
//              We then sort the E array with respect to the costs.
//              Next we read all the queries and do some magic based on the euler tour example problem, and then
//              sort all the queries based on the k values. and then finally we can do Offline BIT operations for each query.
//


#include <cstdio>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

#define LOGN 19
#define N 101000

// Variables for storing the graph
vector<long> adj[N], costs[N];

// Variables relating to binary lifting
long level[N], pa[LOGN][N];

// Variables for Euler Tour
long st[N], et[N], position, position_e;
pair<long, long> E[N * 6];

// Variable for BIT tree
long T[N * 6];

// Struct to store the queries
struct Query {
    long idx, i, j, k;
};

// Standard LCA code using Binary lifting
long LCA(long u, long v) {
    if (level[u] < level[v]) swap(u, v);
    long diff = level[u] - level[v];
    for (long i = 0; i < LOGN; i++) if ((diff >> i) & 1) u = pa[i][u];
    if (u == v) return u;
    for (long i = LOGN - 1; i >= 0; i--)
        if (pa[i][u] != pa[i][v]) {
            u = pa[i][u];
            v = pa[i][v];
        }
    return pa[0][u];
}


// DFS with Euler Tour
// position_e is used to indicate the next index position in the E array
void dfs(long cur, long prev, long _depth = 0, long prev_cost = 0) {
    st[cur] = ++position; // Start position of the node
    pa[0][cur] = prev;  // for LCA
    level[cur] = _depth; // height of the current node

    for (long i = 0; i < adj[cur].size(); i++)
        if (adj[cur][i] != prev) {
            E[position_e].first = costs[cur][i]; // Storing the cost of edge from curr to its children
            E[position_e].second = position_e + 1;
            position_e++;
            dfs(adj[cur][i], cur, _depth + 1, costs[cur][i]); // Recursive DFS call
        }

    et[cur] = ++position; // End position of the node
    E[position_e].first = prev_cost; // Storing the cost of edge from curr to it's parent
    E[position_e].second = position_e + 1;
    position_e++;
}


// Sort condition for the queries
bool sort_cond2(const Query &q1, const Query &q2) {
    return q1.k < q2.k;
}

// Sort condition for the E array
bool sort_cond1(const pair<long, long> &q1, const pair<long, long> &q2) {
    return q1.first < q2.first;
}

// BIT update operation
void update(long idx, long val) {
    while (idx <= N * 6) {
        T[idx] ^= val;
        idx += (idx & -idx);
    }
}

// BIT read operation
long read(long idx) {
    long sum = 0;
    while (idx > 0) {
        sum ^= T[idx];
        idx -= (idx & -idx);
    }
    return sum;
}

// BIT query operation
long query(long l, long r) {
    return read(r) ^ read(l - 1);
}

int main() {
    long a, b, c, m, n, u, v, qNo, t, lca, res[N];
    scanf("%ld", &t);
    while (t--) {
        // Clearing stuff for each test case
        memset(E, 0, sizeof(E));
        memset(st, -1, sizeof(st));
        memset(et, -1, sizeof(et));
        memset(T, 0, sizeof(T));
        qNo = 0;
        position = -1;
        position_e = 0;
        scanf("%ld", &n);
        for (long i = 0; i < n; i++) {
            adj[i].clear();
            costs[i].clear();
            for (long j = 0; j < LOGN; j++) pa[j][i] = -1;
        }

        // Reading the graph
        for (long i = 1; i < n; i++) {
            scanf("%ld %ld %ld", &u, &v, &c);
            u--, v--; // Using 0 based indexing
            adj[u].push_back(v);
            costs[u].push_back(c);
            adj[v].push_back(u);
            costs[v].push_back(c);
        }

        dfs(0, -1); // Starting the DFS

        // Sorting the elements in the E array
        sort(E, E + (2 * n - 1), sort_cond1);

        // Preprocessing for LCA using Binary lifting
        for (long i = 1; i < LOGN; i++)
            for (long j = 0; j < n; j++)
                if (pa[i - 1][j] != -1)
                    pa[i][j] = pa[i - 1][pa[i - 1][j]];


        // p2 is holds the proper start position, end position , k value and also the index of the query i
        struct Query p2[N];
        scanf("%ld", &m);
        long mm = m;
        while (mm--) {
            long a, b, c;
            scanf("%ld %ld %ld", &a, &b, &c);
            long u = a - 1, v = b - 1, k = c, i = qNo++;

            p2[i].k = k;
            p2[i].idx = i;

            // get the LCA in LogN
            lca = LCA(u, v);

            // Based on Euler tour tutorial to find the start and end index positions in E array for each query.
            if (st[u] > st[v]) swap(u, v);
            if (lca == u) {
                p2[i].i = st[u] + 1;
                p2[i].j = st[v];
            } else {
                p2[i].i = et[u];
                p2[i].j = st[v];
            }
        }

        // Sorting all the queries based on the k value
        sort(p2, p2 + m, sort_cond2);

        // Offline processing of the queries.
        long i = 0, j = 0, k;
        while (i < m) {
            k = p2[i].k;
            while (j < position_e && E[j].first <= k) {
                update(E[j].second, E[j].first);
                j++;
            }
            while (i < m && p2[i].k == k) {
                res[p2[i].idx] = query(p2[i].i, p2[i].j);
                i++;
            }
        }

        // Printing the answers.
        for (i = 0; i < m; i++) printf("%ld\n", res[i]);
    }
}
//
// Submitted link: https://www.codechef.com/viewsolution/14550758
//        AC - 0.58s
//
// Conclusion: After 2 days, 4 different approaches and 25+ submissions, I was finally able to solve this in the live contest.
//             Although I don't expect the same kind of problem to appear in any contest, there's certainly many new things that
//             to learn from this problem. The solution explained in the official editorial is completely different than this.
//
// My Profile: https://www.codechef.com/users/vsr625


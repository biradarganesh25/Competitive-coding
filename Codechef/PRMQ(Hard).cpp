// Warning: This ain't for the faint hearted. Proceed with caution.
// Problem Link: https://www.codechef.com/JUNE17/problems/PRMQ
//
// Problem Description:
//              Although the problem description looks somewhat confusing, it's basically asking us this -
//              For all the prime numbers between the range X and Y, find the sum of the count of those prime numbers powers
//              in the prime decomposition of the arrays numbers between the indexes L and R.
//
// Problem Difficulty: Intermediate/Hard
// Tags: segement-trees, sieve
//
// Prerequisites:
//             1) Segment Trees(refer Geeksforgeeks)
//             2) Persistent Segment Trees (refer Geeksforgeeks) (https://blog.anudeep2011.com/persistent-segment-trees-explained-with-spoj-problems/)
//             3) Sieve and finding shorted prime factor (refer Geeksforgeeks)
//
// Solution Description:
//              My solution this is problem is again different with respect to the official editorials, which seems a bit complicated.
//              I basically optimized the fuck out of the brute force solution to this problem.
//              First we find the prime decomposition of a number using standard spf method. and we also memoize the intermediate solutions as well.
//              We maintain a segment tree for the primes, for example if the prime number 3 has been enountered 2 times, we represent it as
//              arr[3] = 2; basically.
//              To the above described segment tree we add persistance layer, for example version[2] holds the count of all prime numbers
//              in the prime decompositions up until the array index 2. In general version[i] holds the total count of all the prime numbers
//              in the prime decomposition of array index i.
//              With the presistance layer, now it's easy to calculate our required value, for the range L R and prime range of X Y, we first query
//              the version[r] segment tree with the range X to Y. and do the same with version[l-1]. and subtract with the query from version[r]
//              that gives us our required answer.

#include<iostream>
#include "bits/stdc++.h"
#include "math.h"

using namespace std;

#define MAXN 1000001

// Memoization for prime decompositions
map<long long, map<long long, long long>> dp;
map<long long, map<long long, long long>> sum;

int spf[MAXN];

// Standard Sieve
void sieve() {
    spf[1] = 1;
    for (int i = 2; i < MAXN; i++)
        spf[i] = i;

    for (int i = 4; i < MAXN; i += 2)
        spf[i] = 2;

    for (int i = 3; i * i < MAXN; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j < MAXN; j += i)
                if (spf[j] == j)
                    spf[j] = i;
        }
    }
}

// Standard get_prime_factors algo with added memoization
map<long long, long long> getfactors(long long x, long long i) {
    if (dp[x].size() != 0) {
        for (map<long long, long long>::iterator it = dp[x].begin(); it != dp[x].end(); ++it) {
            sum[i][it->first] += it->second;
        }
        return dp[x];
    } else {
        if (x != spf[x])
            dp[x] = getfactors(x / spf[x], i);
        dp[x][spf[x]]++;
        sum[i][spf[x]]++;
        return dp[x];
    }
}

// Segment tree node
struct node {
    long val;
    node *left, *right;

    node(node *l, node *r, long v) {
        left = l;
        right = r;
        val = v;
    }
};

// Standard segement tree build
void build(node *n, long low, long high) {
    if (low == high) {
        n->val = 0;
        return;
    }
    long mid = (low + high) / 2;
    n->left = new node(NULL, NULL, 0);
    n->right = new node(NULL, NULL, 0);
    build(n->left, low, mid);
    build(n->right, mid + 1, high);
    n->val = 0;
}

// Persistance upgrade function
void upgrade(node *prev, node *cur, long low, long high,
             long idx, long cur_val, long prev_val) {
    if (idx > high or idx < low or low > high)
        return;

    if (low == high) {
        cur->val = cur_val + prev_val;
        return;
    }
    int mid = (low + high) / 2;
    if (idx <= mid) {
        cur->right = prev->right;
        cur->left = new node(NULL, NULL, 0);
        upgrade(prev->left, cur->left, low, mid, idx, cur_val, prev->left->val);
    } else {
        cur->left = prev->left;
        cur->right = new node(NULL, NULL, 0);
        upgrade(prev->right, cur->right, mid + 1, high, idx, cur_val, prev->right->val);
    }
    cur->val = cur->left->val + cur->right->val;
}

// Normal segement tree query operation
long query(node *n, long low, long high, long l, long r) {
    if (l > high or r < low or low > high)
        return 0;
    if (l <= low and high <= r)
        return n->val;
    long mid = (low + high) / 2;
    long p1 = query(n->left, low, mid, l, r);
    long p2 = query(n->right, mid + 1, high, l, r);
    return p1 + p2;
}


int main() {
    long long l, r, i, j, x, y, n, q, res, num;
    long max = 1000000;

    sieve();
    node *version[100500]; // the maximum N value is 10^5
    version[0] = new node(NULL, NULL, 0);
    build(version[0], 0, max); // build initial segment tree

    scanf("%lld", &n);

    node *temp = new node(version[0]->left, version[0]->right, 0); // temp node imitating the version[0]

    for (i = 1; i <= n; i++) { // for each array index
        scanf("%lld", &num);
        getfactors(num, i); // Get the factors of that number
        version[i] = new node(NULL, NULL, 0); // New version for index i
        for (map<long long, long long>::iterator it = sum[i].begin(); it != sum[i].end(); ++it) {
            upgrade(temp, version[i], 0, max, it->first, sum[i][it->first], temp->val); // Upgrade the value of prime number it->first
            // There's a reason behind this, if you can't figure it out, then do raise an issue in the repo.
            temp = new node(version[i]->left, version[i]->right, version[i]->val);
        }
    }

    // Querying as described in the solution description
    scanf("%lld", &q);
    while (q--) {
        scanf("%lld %lld %lld %lld", &l, &r, &x, &y);
        res = query(version[r], 0, max, x, y) - query(version[l - 1], 0, max, x, y);
        printf("%lld\n", res);
    }
    return 0;
}
// Submission link: https://www.codechef.com/viewsolution/14147837
//                  AC - 0.97s (Barely passed)
//
// Conclusion: I agree that it's just a hacky solution to a problem, and it can be optimized further.
//             If you can understand and solve this problem by the approach discussed above, then surely you have understood
//             Segment trees and persistant segment trees.
//             These types of problems require use of advanced algorithms and data structures to solve the problem, and may not interest
//             many people who don't like to play with complex structures and algos.


/*
Given a set of n intervals (si ; fi ), each with a value vi , choose a subset S of non-overlapping intervals with 
Summation<vi>, ( i to s ) maximized.

p(j) = the largest i < j such that interval i doesn't overlap with j i.e. p(j) is the interval farthest to the
right that is compatible with j .

Let OPT be an optimal solution
v[i] is the weight assigned with ith interval

OPT(j) = max { v(j) + OPT(p[j]) , if j in OPT solution ,
               OPT(j-1)         , if j not in OPT solution,
               0                , j=0

Algorithm:

1)Sort the requests in order of non-decreasing finish times. This step takes time O(n log n).
2)For 1 ≤ j ≤ n, find the largest i < j such that fi ≤ sj, call it p(j). Since the requests are sorted in order of
  non-decreasing finish times, we can use binary search to find p(j) in time O(log j). 
  Thus, this step takes time sum(O(log j)) for 1 ≤ j ≤ n = O(n log n).
3)For 1 ≤ j ≤ n, compute OPT(j) = max(wj + OPT(p(j)), OPT(j-1)). This step takes time O(n).

Thus the overall time complexity of the algorithm is O(n log n).

*/


#include <cstdio>
#include <algorithm>
#include <stack>
using namespace std;

class WeightedInterval {
public:
    int start, finish, weight;

    bool operator < (const WeightedInterval& x) const   {
        if (finish != x.finish)
            return finish < x.finish;
        return start < x.start;
    }
} *intervals;

// returns index of the interval having greatest finish time <= val in range [lo, hi]
int binary_search(int lo, int hi, int val)   {
    int mid;
    while (lo < hi) {
        mid = lo + (hi - lo + 1) / 2;
        if (intervals[mid].finish <= val)
            lo = mid;
        else
            hi = mid - 1;
    }
    if (intervals[lo].finish > val)
        return 0;
    return lo;
}

// returns index of the interval having greatest finish time <= start time of interval i
int greatestNonOverlappingInterval(int i)   {
    return binary_search(0, i-1, intervals[i].start);
}

int main()  {
    int N, i, *dp, *p;

    scanf("%d", &N); //Number of intervals
    intervals = new WeightedInterval[N + 1];
    for (i = 1; i <= N; i++)
        scanf("%d %d %d", &intervals[i].start, &intervals[i].finish, &intervals[i].weight);

    // dummy interval used as a sentinel
    intervals[0].start = intervals[0].finish = intervals[0].weight = 0;

    // sort intervals in non-decreasing order of finish times
    sort(intervals + 1, intervals + N + 1);

    dp = new int[N + 1];
    p = new int[N + 1];
    dp[0] = p[0] = 0;

    // construct the value of the optimal solution
    for (i = 1; i <= N; i++)    {
        p[i] = greatestNonOverlappingInterval(i);
        dp[i] = max(intervals[i].weight + dp[p[i]], dp[i-1]);
    }

    // construct the optimal solution
    stack <int> opt;
    for (i = N; i > 0; )    {
        if (intervals[i].weight + dp[p[i]] >= dp[i-1])  {
            opt.push(i);
            i = p[i];
        } else
            i--;
    }

    // optimal solution
    printf("%d\n", dp[N]);
    while (!opt.empty())    {
        i = opt.top();
        opt.pop();
        printf("%d %d %d\n", intervals[i].start, intervals[i].finish, intervals[i].weight);
    }

    return 0;
}

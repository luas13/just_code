/*
Tom and Jerry are wonderful characters. They are always running and make us laugh.

Right now, they are in a grid of houses and Jerry is running away from Tom. The grid of houses is represented as 0
and 1, where 0 means that Jerry can enter the house, and 1

means Jerry can't. Jerry can only move horizontally or vertically. Also, Jerry doesn't enter the same house more than once.

Jerry started running from the house at (1,1
) which is the top-left house in the grid and have to reach (N,N

) which the bottom-right house in the grid. You have find the number of ways in which Jerry can reach the destination house where he can be safe.

Input Format

First line is an integer N
( N≤100), which is the size of the grid. N lines follow, each containing N space separated numbers which are either '0' or '1


Output format

Print a single line showing the number of ways in which Jerry can reach from (1,1) to (N,N).


SAMPLE INPUT

9
0 0 0 0 0 0 0 0 0
0 1 0 1 0 1 0 1 0
0 0 0 0 0 0 0 0 0
0 1 0 1 0 1 0 1 0
0 0 0 0 0 0 0 0 0
0 1 0 1 0 1 0 1 0
0 0 0 0 0 0 0 0 0
0 1 0 1 0 1 0 1 0
0 0 0 0 0 0 0 0 0


SAMPLE OUTPUT
8512


This Question depends on Back Tracking Technique.

Firstly:
You should check for the available transitions from a current state:
you will find 3 available directions, but only try (0s) positions.

Note: you can't return to the previous position since you can't visit
a cell more than once, so the available directions will be (3) not (4).

Secondly:
Store this state as visited so as to avoid visiting it again during the way
to the destination.

Thirdly:
Once you end the state recursion, you should set it again as unvisited so you
can use it in another possible way (Back Tracking Technique).

Note: You should check if a position is outside the board.

Base Case:
When you reach the destination house:

if(x == n - 1 && y == n - 1){     // base case

    ans++;                      // increase the number of ways
    return;
}

Let's call the number of possible adjacent transitions as M, number of (0s) in the grid as R

Time Complexity: O(MR).

Memory Space Complexity: O(N*N). 
*/

#include <iostream>
#include <vector>

using namespace std;

#define rep(i,n) for(int i=0; i<n; i++)

void countpaths(vector<vector<int>> &matrix, vector<vector<int>> &visited, int x, int y, int r, int& count)
{
	if (x == r-1 && y == r-1)
	{
		count++;
		return;
	}

	visited[x][y] = 1;

	int dir[][] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}};
	rep(i,4)
	{
		int dx = x + dir[i][0];
		int dy = y + dir[i][1];

		if (dx < 0 || dx >= r || dy < 0 || dy >= r)
			continue;

		if (visited[dx][dy] || matrix[dx][dy])
			continue;

		else
			countpaths(matrix, visited, dx, dy, r, count);

		//visited[dx][dy] = 0;
	}
	visited[dx][dy] = 0;
}

int main()
{
	int r;
	cin>>r;
	vector<vector<int>> matrix(r, vector<int>(r));
	rep(i,r)
		rep(j,r)
			cin>>matrix[i][j];

	vector<vector<int>> visited(r, vector<int>(r, 0));
	
	countpaths(matrix, visited, 0, 0, r, 0);

	cout<<count<<endl;
}

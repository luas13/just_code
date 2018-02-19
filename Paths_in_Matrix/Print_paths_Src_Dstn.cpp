# include<iostream>
# include <vector>
using namespace std;

void printpath(vector<int> path, int m, int n)
{
	// We know the path length will always be m+n-1
	for(int i= 0; i<m+n-1; i++)
		cout<<path[i]<<" ";
	cout<<endl;
}

void printAllPathsUtil(int mat[2][3], int i, int j, int m, int n, vector<int> &paths, int ci)
{
	// Reached the bottom of the matrix so we are left with
    	// only option to move right
	if (i == m-1)
	{
		for(int k=j; k<n; k++)
			paths[ci + k-j] = mat[i][k];
		printpath(paths, m, n);
		return;
	}

	// Reached the right corner of the matrix we are left with
    	// only the downward movement.
	if (j == n-1)
	{
		for(int k=i; k<m; k++)
			paths[ci + k-i] = mat[k][j];
		printpath(paths, m, n);
		return;
	}

	// Add the current cell to the path being generated
	paths[ci] = mat[i][j];

	// Print all the paths that are possible after moving down
	printAllPathsUtil(mat, i+1, j, m, n, paths, ci+1);
	
	// Print all the paths that are possible after moving right
	printAllPathsUtil(mat, i, j+1, m, n, paths, ci+1);
}

// The main function that prints all paths from top left to bottom right
// in a matrix 'mat' of size mXn
void printAllPaths(int mat[2][3], int m, int n)
{
	vector<int> path(m+n, 0);
	printAllPathsUtil(mat, 0, 0, m, n, path, 0);
}

// Driver program to test abve functions
int main()
{
	int mat[2][3] = { {1, 2, 3}, {4, 5, 6} };
	printAllPaths(mat, 2, 3);
	return 0;
}

/*
1 4 5 6 
1 2 5 6 
1 2 3 6
*/

/******************************************************************************
Problem: Print all possible combinations of r elements in a given array of size n
*** All elements are unique, No duplicates

Method: (Include and Exclude every element)

We one by one consider every element of input array, and recur for two cases:

1) The element is included in current combination (We put the element in subset[] 
and increment next available index in subset[])

2) The element is excluded in current combination (We do not put the element 
and do not change index)

When number of elements in subset[] become equal to r (size of a combination), we save it.

This method is mainly based on Pascal’s Identity, i.e. ncr = n-1cr-1 + n-1cr

*******************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

/* arr ---> Input Array  
l ---> Size of input array  
k ---> Size of a combination to be printed  
si ---> Current index in data[]  
subset ---> Temporary array to store current combination  
i ---> index of current element in arr[] 
*/

void util (vector<int>& arr, int l, vector<int> subset, int si, int i, int k, vector<vector<int>>& subsets)
{
	if (si == k)
	{
		subsets.push_back(subset);
		return;
	}

	// When no more elements are there to put in subset
	if (i >= l)
		return;

	// current is included, put next at next location
	subset[si] = arr[i];
	util(arr, l, subset, si+1, i+1, k, subsets);

	// current is excluded, replace it with next (Note that  
    // i+1 is passed, but si is not changed)  
	util(arr, l, subset, si, i+1, k, subsets);
}

void getAllCombinations(vector<int>& arr, int k, vector<vector<int>>& subsets)
{
	
	vector<int> subset(k, 0);
	int l = arr.size();

	util(arr, l, subset, 0, 0, k, subsets);
}

int main()
{
	vector<int> arr{1, 5, 2, 9, 7};
	vector<vector<int>> subsets;
	getAllCombinations(arr, 3, subsets);
	
	for (auto v: subsets)
	{
	    for (auto e : v)
	        cout<<e<<" ";
	    cout<<endl;
	}

	return 0;
}

/*
Output:
1 5 2 
1 5 9 
1 5 7 
1 2 9 
1 2 7 
1 9 7 
5 2 9 
5 2 7 
5 9 7 
2 9 7

*/

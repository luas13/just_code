#include <iostream>
#include <stdio.h>

using namespace std;

// a is an array where a[i] represents no of binary string which ends in 0 
// and contains no consecutive 1's
// b is an array where b[i] represents no of binary string which ends in 1 
// and contains no consecutive 1's
// We can append either 0 or 1 to a string ending in 0, but we can only append 0 
// to a string ending in 1. This yields the recurrence relation:

// a[i] = a[i - 1] + b[i - 1]
// b[i] = a[i - 1] 

The base cases of above recurrence are a[1] = b[1] = 1. The total number of strings of length i is just a[i] + b[i]. 

int computeBinaryStringWithNo1stogether(int n)
{
	int* a = (int*)malloc(sizeof(int) * n);
	int* b = (int*)malloc(sizeof(int) * n);

	a[0] = 1;
	b[0] = 1;

	for(int i=1; i<n; i++)
	{
		a[i] = a[i-1] + b[i-1];
		b[i] = a[i-1];
	}

	int total = a[n-1] + b[n-1];

	free(a);
	free(b);

	return (total);
}

int main()
{
	int n;
	cout<<"Enter the number"<<endl;
	cin>>n;
	int count = computeBinaryStringWithNo1stogether(n);
	cout<<"Total no of binary strings with no consecutive 1s are "<<endl;
}

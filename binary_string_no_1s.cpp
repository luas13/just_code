#include <iostream>
#include <stdio.h>

using namespace std;

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
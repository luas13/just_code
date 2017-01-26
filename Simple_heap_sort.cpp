// C++ program for implementation of Heap Sort
// Using Max Heap

#include <iostream>
using namespace std;

void mswap(int& a, int& b)
{
    int t=a;
    a=b;
    b=t;
}

// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void heapify(int arr[], int n, int i)
{
	int lar = i;
	int l = 2*i + 1;
	int r = 2*i + 2;
	
	if (l<n && arr[l] > arr[lar])
	{
	    lar = l;
	}
	if (r<n && arr[r] > arr[lar])
	{
	    lar = r;
	}
	
	if (lar != i)
	{
	    mswap(arr[i], arr[lar]);
	    heapify(arr, n, lar);
	}
}

// main function to do heap sort
void heapSort(int arr[], int n)
{
	for(int i=n/2-1; i>=0; i--)
	    heapify(arr, n, i);
	   
	for(int i=n-1; i>=0; i--)
	{
	    mswap(arr[i], arr[0]);
	    heapify(arr, i, 0);
	}
	
	//printArray(arr, n);
}

/* A utility function to print array of size n */
void printArray(int arr[], int n)
{
	for (int i=0; i<n; ++i)
		cout << arr[i] << " ";
	cout << "\n";
}

// Driver program
int main()
{
	int arr[] = {12, 11, 13, 5, 6};
	int n = sizeof(arr)/sizeof(arr[0]);

	heapSort(arr, n);

	cout << "Sorted array is \n";
	printArray(arr, n);
}

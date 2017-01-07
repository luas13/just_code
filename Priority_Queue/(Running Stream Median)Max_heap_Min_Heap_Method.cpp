/*
The brute force algorithm uses a vector and maintains a sorted list. In this case the complexity of adding an element
is O(n). Therefore, for n elements, the worst case is O(n^2).

Instead we maintain 2 priority queues i.e minHeap, maxHeap. We keep adding the numbers in both such that the number 
of elements in the maxheap is at max 1 greater than number of elements in the minHeap. Maintaining this constraint,
allows us to get the median in O(1) time. Also, insertion becomes O(logn). Therefore, overall complexity is O(nlogn).

*/

#include <iostream>
#include <queue>
using namespace std;

void insert(priority_queue<int> &maxHeap,priority_queue<int,vector<int>, greater<int> > &minHeap, int n)
{
    if(maxHeap.size()==minHeap.size())
    {
        if(!minHeap.empty() && n>minHeap.top())
        {
            maxHeap.push(minHeap.top());
            minHeap.pop();
            minHeap.push(n);
        }
        else
            maxHeap.push(n);
    }
    else
    {
        if(n<maxHeap.top())
        {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
            maxHeap.push(n);
        }
        else
            minHeap.push(n);
    }
}
double getMedian(priority_queue<int> maxHeap,priority_queue<int,vector<int>, greater<int> > minHeap)
{
    int a = minHeap.size();
    int b = maxHeap.size();
    if(a==0 && b==0) return -1;
    if((a+b)%2==0)
        return (double)(minHeap.top() + maxHeap.top())/2;
    else
        return maxHeap.top();
}
int main()
{
    priority_queue<int> maxHeap;
    priority_queue<int,vector<int>, greater<int> > minHeap;
    int a[] = {7,11,17,8,19,2,3,15,16};
    int n = sizeof(a)/sizeof(a[0]);
    for(int i=0; i<n; i++)
    {
        insert(maxHeap,minHeap,a[i]);
        cout<<getMedian(maxHeap,minHeap)<<endl;
    }
    return 0;
}



/*
Or,

#include <iostream>       // std::cout
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include <functional>     // std::greater

void dynamicMedian()
{ 
	priority_queue<int, vector<int>, less<int> > lQ; 
	priority_queue<int, vector<int>, greater<int> >rQ; 
	int left=0, right=0, element=INT_MIN; 
	double median=INT_MAX;
	while(element)
	{ 
		cin>>element; 
		if(element<median)
		{ 
			if(left>right)
			{ 
				rQ.push(lQ.top()); 
				right++; 
				lQ.pop(); 
				lQ.push(element); 
				median=(lQ.top()+rQ.top())/2; 
			}
			else if(left==right)
			{ 
				lQ.push(element); 
				left++; 
				median=lQ.top(); 
			} 
			else
			{ 
				lQ.push(element); 
				left++; 
				median=(lQ.top()+rQ.top())/2; 
			} 
		} 
		 
		else{ 
			if(left<right)
			{ 
				lQ.push(rQ.top()); 
				left++; 
				rQ.pop(); 
				rQ.push(element); 
				median=(lQ.top()+rQ.top())/2; 
			} 
			else if (left==right)
			{ 
				rQ.push(element); 
				right++; 
				median=rQ.top(); 
			} 
			else
			{ 
				rQ.push(element); 
				right++; 
				median=(lQ.top()+rQ.top())/2; 
			}

		} 
			
		cout<<"Median is "<<median<<endl; 
	}
}

*/

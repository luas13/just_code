/* C++ program to find Kth ancestor of given node */

#include <iostream> 
#include <queue> 
#include <unordered_map>

using namespace std; 

// A Binary Tree Node 
struct Node 
{ 
	int data; 
	struct Node *left, *right; 
}; 

// fucntion to generate array of ancestors 
void generateAncestors(Node *root, unordered_map<int, int>& ancestors_map) 
{ 
	// There will be no ancestor of root node 
    // 	ancestors[root->data] = -1; 
    ancestors_map[root->data] = -1;

	// level order traversal to 
	// generate 1st ancestor 
	queue<Node*> q; 
	q.push(root); 

	while(!q.empty()) 
	{ 
		Node* temp = q.front(); 
		q.pop(); 

		if (temp->left) 
		{ 
			ancestors_map[temp->left->data] = temp->data; 
			q.push(temp->left); 
		} 

		if (temp->right) 
		{ 
			ancestors_map[temp->right->data] = temp->data; 
			q.push(temp->right); 
		} 
	} 
} 

// function to calculate Kth ancestor 
int kthAncestor(Node *root, int k, int node) 
{ 
	// create array to store 1st ancestors 
	unordered_map<int, int> ancestors_map;

	// generate first ancestor array 
	generateAncestors(root,ancestors_map); 

	// variable to track record of number of 
	// ancestors visited 
	int count = 0; 

	while (node!=-1) 
	{ 
		node = ancestors_map[node]; 
		count++; 

		if(count==k) 
			break; 
	} 

	// print Kth ancestor 
	return node; 
} 

// Utility function to create a new tree node 
Node* newNode(int data) 
{ 
	Node *temp = new Node; 
	temp->data = data; 
	temp->left = temp->right = NULL; 
	return temp; 
} 

// Driver program to test above functions 
int main() 
{ 
	// Let us create binary tree shown in above diagram 
	Node *root = newNode(1); 
	root->left = newNode(2); 
	root->right = newNode(3); 
	root->left->left = newNode(4); 
	root->left->right = newNode(5); 
	root->left->right->left = newNode(7); 
	root->left->right->right = newNode(9); 

	int k = 2; 
	int node = 9; 

	// print kth ancestor of given node 
  // cout<<kthAncestor(root,5,k,node); 
	cout<<kthAncestor(root,k,node); 
	return 0; 
} 

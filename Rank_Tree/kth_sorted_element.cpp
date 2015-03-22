/*
Imp part to look is add() does not store the number of nodes to the left ,its the getRank() which prints it.

*/


#include <iostream>
using namespace std;

struct node
{
    int value,left_size;
    struct node *left;
    struct node *right;
};
typedef struct node TreeNode;

TreeNode* createNode(int n)
{
    TreeNode *temp = new TreeNode();
    temp->value = n;
    temp->left_size = 0;
    return temp;
}

void add(TreeNode* &root, int n)
{
    if(root==NULL)
        root  = createNode(n);
    else if(n<root->value)
    {
        add(root->left,n);
        root->left_size++;
    }
    else
        add(root->right,n);
}


int getRank(TreeNode* root, int n)
{
    if(root->value==n)
        return root->left_size;
    else if(n<root->value)
    {
        if(root->left==NULL) return -1;
        else return getRank(root->left,n);
    }
    else
    {
        int right_rank = (root->right)?getRank(root->right,n):-1;
        if(right_rank==-1) return -1;
        return 1 + root->left_size + right_rank;
    }
}




int kthelement(TreeNode* root, TreeNode* temp,int k)
{
    if(!root)
        return INT_MIN;
    int rank= getRank(temp, root->value) + 1;
    if( rank == k )
        return root->value;
    if( rank > k )
        return kthelement(root->left, temp, k);
    else
        return kthelement(root->right, temp, k);
}



void printin(TreeNode* root)
{
     if(!root)
        return;
     printin(root->left);
     cout<<"root->value= "<<root->value<< "       root->left_size= "<<root->left_size<<endl;
     printin(root->right);
}


int main()
{
    TreeNode* root = NULL;
    int a[] = {11,7,13,5,15,12};
    int k=3;
    int size = sizeof(a)/sizeof(a[0]);
    for(int i=0; i<size; i++)
    {
        add(root,a[i]);
    }
    for(int i=0; i<size; i++)
    {
        cout<<getRank(root,a[i])<<" ";
    }
    
    cout<<endl;
    printin(root);   
    cout<<endl;
    
    if(k > size) 
         cout<<"k is more than the array size\n";
    else
         cout<<k<<"th element is "<<kthelement(root,root,k)<<endl;
   
    getchar();
    return 0;
}

//**************************OUTPUT**********************************

2 1 4 0 5 3 
root->value= 5       root->left_size= 0
root->value= 7       root->left_size= 1
root->value= 11       root->left_size= 2
root->value= 12       root->left_size= 0
root->value= 13       root->left_size= 1
root->value= 15       root->left_size= 0

3th element is 11

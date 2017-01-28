// Bottom View: just same as Top view
#include <iostream>
#include <string>
#include <map>

using namespace std;

typedef struct node{
    int data;
    node* left;
    node* right;
}mytree;

mytree* newnode(int v)
{
    mytree* tmp = new mytree();
    tmp->data = v;
    tmp->left = tmp->right = NULL;
    return tmp;
}

void topview(mytree* root, map<int, pair<int, int>>& mymap, int hd, int level)
{
    if(!root)
        return;
    if(mymap.find(hd) == mymap.end() || mymap[hd].second < level)
        mymap[hd] = make_pair(root->data, level);
    topview(root->left, mymap, hd-1, level+1);
    topview(root->right, mymap, hd+1, level+1);
}

int main()
{
    mytree* root = newnode(1);
    root->left = newnode(2);
    root->right = newnode(3);
    root->left->left = newnode(4);
    root->left->left->right = newnode(10);
    root->left->right = newnode(5);
    //root->right->left = newnode(6);
    //root->right->right = newnode(7);
    root->left->right->right = newnode(8);
    root->left->right->right->right = newnode(9);
  
    map<int, pair<int, int>> mymap;
    topview(root, mymap, 0, 0);
  
    for(auto it = mymap.begin(); it!= mymap.end(); it++)
    {
        cout<<(it)->second.first<<" ";
    }
    cout<<endl;
    return 0;
}

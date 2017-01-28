// All 4 Views of a Tree
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

void leftview(mytree* root, int level, int& maxlevel)
{
    if(!root)
        return;
    if(maxlevel < level)
    {
        maxlevel = level;
        cout<<root->data<<" ";
    }
    leftview(root->left, level+1, maxlevel);
    leftview(root->right, level+1, maxlevel);
}

void rightview(mytree* root, int level, int& maxlevel)
{
    if(!root)
        return;
    if(maxlevel < level)
    {
        maxlevel = level;
        cout<<root->data<<" ";
    }
    rightview(root->right, level+1, maxlevel);
    rightview(root->left, level+1, maxlevel);
}

void topview(mytree* root, map<int, pair<int, int>>& mymap, int hd, int level)
{
    if(!root)
        return;
    if(mymap.find(hd) == mymap.end() || mymap[hd].second > level)
        mymap[hd] = make_pair(root->data, level);
    topview(root->left, mymap, hd-1, level+1);
    topview(root->right, mymap, hd+1, level+1);
}

void bottomview(mytree* root, map<int, pair<int, int>>& mymap, int hd, int level)
{
    if(!root)
        return;
    if(mymap.find(hd) == mymap.end() || mymap[hd].second < level)
        mymap[hd] = make_pair(root->data, level);
    bottomview(root->left, mymap, hd-1, level+1);
    bottomview(root->right, mymap, hd+1, level+1);
}


int main()
{
  mytree* root = newnode(1);
  root->left = newnode(2);
  root->right = newnode(3);
  root->left->left = newnode(4);
  root->left->right = newnode(5);
  root->right->left = newnode(6);
  root->right->right = newnode(7);
  root->left->right->right = newnode(8);
  root->left->right->right->right = newnode(9);
  
  map<int, pair<int, int>> mymap;
  topview(root, mymap, 0, 0);
  
  cout<<"Top view is as follows"<<endl;
  for(auto it = mymap.begin(); it!= mymap.end(); it++)
  {
      cout<<(it)->second.first<<" ";
  }
  cout<<endl;
  
  map<int, pair<int, int>> tmp;
  mymap = tmp;
  cout<<"Bottom view is as follows"<<endl;
  bottomview(root, mymap, 0, 0);
  for(auto it = mymap.begin(); it!= mymap.end(); it++)
  {
      cout<<(it)->second.first<<" ";
  }
  cout<<endl;
  
  int maxlevel =-1;
  cout<<"Right view is as follows"<<endl;
  rightview(root, 0, maxlevel);
  cout<<endl;
  
  maxlevel =-1;
  cout<<"Left view is as follows"<<endl;
  leftview(root, 0, maxlevel);
  cout<<endl;
  
  return 0;
}

// Output:
Top view is as follows
4 2 1 3 7 
Bottom view is as follows
4 2 5 8 9 
Right view is as follows
1 3 7 8 9 
Left view is as follows
1 2 4 8 9 

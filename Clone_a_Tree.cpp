struct node{
  int data;
  node* left;
  node* right;
};

node *clone(root)
{
   if (root == NULL)
      return root;
 
   //create new node and make it a copy of node pointed by root
   node *temp = (node *)malloc(sizeof(node)) ;
   temp->data = root-> data;    //copying data
   temp->left = clone(root -> left);    //cloning left child
   temp->right = clone(root -> right);  //cloning right child
   return temp;
}

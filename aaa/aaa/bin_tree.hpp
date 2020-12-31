#pragma  once
struct node
{
   int data;
   node *left;
   node *right;
};


node *insert(node *tree,int ele);

void preorder(node *tree);
void inorder(node *tree);
void postorder(node *tree);

void testbintree();
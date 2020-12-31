#pragma  once
struct Node
{
   int data ;
   Node *next ;
};
typedef struct Node Node ;

void reverse(Node*& head);
Node* reverse(Node* p,Node*& head);
Node * Merge(Node *head1 , Node *head2);
Node * MergeRecursive(Node *head1 , Node *head2);
bool check(const Node* head);

typedef struct TNode{
   TNode* left;
   TNode* right;
   int value;
} TNode;

void append(int N);
void testappend();
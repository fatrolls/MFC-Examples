#include <cstdlib>
#include <cstdio>
#include "node.hpp"
void reverse(Node*& head) {
    if(head ==NULL)
        return;
    Node *pre, *cur, *ne;
    pre=head;
    cur=head->next;
    while(cur)
    {
        ne = cur->next;
        cur->next = pre;
        pre = cur;
        cur = ne;
    }
    head->next = NULL;
    head = pre;
}

//还有一种利用递归的方法。这种方法的基本思想是在反转当前节点之前先调用递归函数反转后续节点。
//不过这个方法有一个缺点，就是在反转后的最后一个结点会形成一个环，所以必须将函数的返回的节点的next域置为NULL。
//因为要改变head指针，所以我用了引用。
Node* reverse(Node* p,Node*& head)
{
    if(p == NULL || p->next == NULL)
    {
        head=p;
        return p;
    }
    else
    {
        Node* tmp = reverse(p->next,head);
        tmp->next = p;
        return p;
    }
}

//(1)已知链表的头结点head,写一个函数把这个链表逆序 ( Intel)

Node * ReverseList(Node *head) //链表逆序
{
    if ( head == NULL || head->next == NULL )
        return head;
    Node *p1 = head ;
    Node *p2 = p1->next ;
    Node *p3 = p2->next ;
    p1->next = NULL ;
    while ( p3 != NULL )
    {
        p2->next = p1 ;
        p1 = p2 ;
        p2 = p3 ;
        p3 = p3->next ;
    }
    p2->next = p1 ;
    head = p2 ;
    return head ;
}
//(2)已知两个链表head1 和head2 各自有序，请把它们合并成一个链表依然有序。(保留所有结点，即便大小相同）
Node * Merge(Node *head1 , Node *head2)
{
    if ( head1 == NULL)
        return head2 ;
    if ( head2 == NULL)
        return head1 ;
    Node *head = NULL ;
    Node *p1 = NULL;
    Node *p2 = NULL;
    if ( head1->data < head2->data )
    {
        head = head1 ;
        p1 = head1->next;
        p2 = head2 ;
    }
    else
    {
        head = head2 ;
        p2 = head2->next ;
        p1 = head1 ;
    }
    Node *pcurrent = head ;
    while ( p1 != NULL && p2 != NULL)
    {
        if ( p1->data <= p2->data )
        {
            pcurrent->next = p1 ;
            pcurrent = p1 ;
            p1 = p1->next ;
        }
        else
        {
            pcurrent->next = p2 ;
            pcurrent = p2 ;
            p2 = p2->next ;
        }
    }
    if ( p1 != NULL )
        pcurrent->next = p1 ;
    if ( p2 != NULL )
        pcurrent->next = p2 ;
    return head ;
}
//(3)已知两个链表head1 和head2 各自有序，请把它们合并成一个链表依然有序，这次要求用递归方法进行。 (Autodesk)

Node * MergeRecursive(Node *head1 , Node *head2)
{
    if ( head1 == NULL )
        return head2 ;
    if ( head2 == NULL)
        return head1 ;
    Node *head = NULL ;
    if ( head1->data < head2->data )
    {
        head = head1 ;
        head->next = MergeRecursive(head1->next,head2);
    }
    else
    {
        head = head2 ;
        head->next = MergeRecursive(head1,head2->next);
    }
    return head ;
}


///如何判断一个单链表是有环的？（注意不能用标志位，最多只能用两个额外指针）
//一种O（n）的办法就是（搞两个指针，一个每次递增一步，一个每次递增两步，如果有环的话两者必然重合，反之亦然）：
bool check(const Node* head)
{
    if(head==NULL) return false;
    const Node *low=head;
    Node *fast=head->next;
    while(fast!=NULL && fast->next!=NULL)
    {
        low=low->next;
        fast=fast->next->next;
        if(low==fast) return true;
    }
    return false;
}


///////////////////////////////

TNode* root=NULL;
void testappend()
{
   append(63);
   append(45);
   append(32);
   append(77);
   append(96);
   append(21);
   append(17); // Again, 数字任意给出
}
void append(int N)
{
   TNode* NewNode=(TNode *)malloc(sizeof(TNode));
   NewNode->value=N;
   
   if(root==NULL)
   {
      root=NewNode;
      return;
   }
   else
   {
      TNode* temp;
      temp=root;

      while((N>=temp->value && temp->left!=NULL) || (N !=NULL))
      {
         while(N>=temp->value && temp->left!=NULL)
            temp=temp->left;
         while(N)    temp=temp->right;//??
      }
      if(N>=temp->value)
         temp->left=NewNode;
      else
         temp->right=NewNode;
      return;
   }
} 
#include<bits/stdc++.h>
using namespace std;
#define MP          make_pair
#define PB          push_back
#define debug(a)    cout<<a<<"\n"
#define mx(a,b,c)   max(a,max(b,c))



struct node {
int key;
int l;
int u;
int color;
node* left;
node* parent;
node* right;

};
node* nil;
node* root;

void rotate_right(node T,node* x)
{
    node* y = x->left ;
    x->left = y->right;
    y->right->parent = x;
    y->parent = x-> parent;
    if(x->parent == nil)
        root=y;
    else if(x == x->parent->left)
        x->parent->left=y;
    else
        x->parent->right=y;
    y->right=x;
    x->parent=y;
}
void rotate_left(node T,node* x)
{

    node* y= x->right;
    x->right=y->left;
    y->left->parent=x;
    y->parent=x->parent;
    if(x->parent==nil) root=y;

     else if(x==x->parent->left)
        x->parent->left=y;
    else
        x->parent->right=y;
    y->left=x;
    x->parent=y;
}
void insert_fixup(node T,node* z)
{
    node* y;
    while(z->parent->color==0)
    {
        if(z->parent==z->parent->parent->left)
        {
            y=z->parent->parent->right;
            if(y->color==0)
            {
                z->parent->color=1;
                y->color=1;
                z->parent->parent->color=0;
                z=z->parent->parent;
            }
            else
            {
                if(z==z->parent->right)
                 {
                     z=z->parent;
                      rotate_left(T,z);
                 }
                z->parent->color=1;
                z->parent->parent->color=0;
                rotate_right(T,(z->parent->parent));
            }
        }
            else
            {
                y=z->parent->parent->left;
            if(y->color==0)
            {
                z->parent->color=1;
                y->color=1;
                z->parent->parent->color=0;
                z=z->parent->parent;
            }
            else
            {
                if(z==z->parent->left)
                 {
                     z=z->parent;
                      rotate_left(T,z);
                 }
                z->parent->color=1;
                z->parent->parent->color=1;
                rotate_right(T,z->parent->parent);
            }
            }

        }
     //debug(z->color<<z->parent<<z->parent);
        root->color=1;
    }




void interval_insert(node T, node* z)
{
  node* y=nil;
  node* x=root;
  while(x!=nil)
  {
      y=x;
      if(z->l < x->l)
      {
          x=x->left;
      }
      else
        x=x->right;
  }
    z->parent=y;
     if (y == nil)
      root =z;
     else if (z->l< y->l)
        y->left=z;
     else y->right=z;

    z->left =nil;
    z->right=nil;
    z->color =0;
    //debug(z->color<<z->parent<<z->parent);
    insert_fixup(T,z);

}
node* successor(node* z)
{
    node* y;
    if(z->right!=nil)
    {
        while(z->left)
            z=z->left;
        return z;
    }
    y=z->parent;
    while(y!=nil && z==y->right)
    {
        z=y;
        y=y->parent;
    }
    return y;
}
void delete_fix(node T,node* x)
{
    node* y;
    node* w;
    while(x!=root && x->color==1)
    {
        if(x==x->parent->left)
        {
            w=x->parent->right;
            if(w->color==0)
            {
                w->color=1;
                x->parent->color=0;
                rotate_left(T,x->parent);
                w=x->parent->right;
            }
            if(w->left->color==1 && w->right->color==1)
            {
                w->color=0;
                x=x->parent;
            }
            else
            {
                if(w->right->color==1)
                {
                    w->left->color=1;
                    w->color=0;
                     rotate_right(T,w);
                    w=x->parent->right;
                }
                w->color=x->parent->color;
                x->parent->color=1;
                w->right->color=1;
                 rotate_left(T,x->parent);
                x=root;
            }
        }
        else
        {
            w=x->parent->left;
            if(w->color==0)
            {
                 x->parent->color=0;
                w->color=1;
                rotate_right(T,x->parent);
                w=x->parent->left;
            }
            if(w->right->color==1 && w->left->color==1)
            {
                w->color=0;
                x=x->parent;
            }
        else
        {
            if(w->left->color==1)
                {
                    w->right->color=1;
                    w->color=0;
                     rotate_left(T,w);
                    w=x->parent->left;
                }
                w->color=x->parent->color;
                w->left->color=1;
                x->parent->color=1;
                rotate_right(T,x->parent);
                x=root;
        }
    }
 }
    x->color=1;
}
void interval_delete(node T, node* z)
{
    node* y;
    node* x;
    if(z->left==nil || z->right==nil)
        y=z;
    else
        y=successor(z);
    debug(z->l);
    debug(z->parent->l);
    debug(y->parent->l);
    if(y->left!=nil)
        x=y->left;
    else
        x=y->right;

    debug(y->parent->l);
    x->parent=y->parent;
    if(y->parent==nil)
       root=x;
    else if(y==y->parent->left)
        y->parent->left=x;
    else
        y->parent->right=x;
    if(y!=z)
    {
        z->l=y->l;
    }

    if(y->color==1) delete_fix(T,x);
}
int cnt;
void traverse(node* x)
{
    if(x==nil) return;
    traverse(x->left);
    debug("( "<<x->l<<" , "<<x->u<<")"<<" key:"<<x->key);
    traverse(x->right);
}
node* interval_search(node T,int i,int j)
{
    node* x=root;
    while(x!=nil && (j<x->l || i>x->u))
    {
        if(x->left!=nil && x->left->key>=i) x=x->left;
        else x=x->right;
    }
    debug("("<<x->l<<" ,"<<x->u<<")");
    return x;
}
int keyAllocation(node* x)
{
    if(x==nil) return 0;
    x->key=mx(keyAllocation(x->left),keyAllocation(x->right),x->u);
    return x->key;

}
//void init(node *z)
//{
//    z=new struct node;
// z->l=-1; z->u=-1; z->key=-1; z->color=1;
// z->left=NULL; z->right=NULL;
//}
int interval[10][2];

int main()
{
nil =new struct node;
 node T;
// init(nil);
// init(root);

 nil->l=-1; nil->u=-1; nil->key=-1; nil->color=1;
 nil->left=NULL; nil->right=NULL,nil->parent=NULL;
 T.l=-1; T.u=-1; T.key=-1; T.color=1;
 T.left=nil; T.right=nil,T.parent=nil;
 root =&T;
node* if_find;
node* if_find1;

    interval[0][0]=15;
    interval[0][1]=20;
    interval[1][0]=10;
    interval[1][1]=30;
    interval[2][0]=17;
    interval[2][1]=19;
    interval[3][0]=5;
    interval[3][1]=20;
    interval[4][0]=12;
    interval[4][1]=15;
    interval[5][0]=30;
    interval[5][1]=40;
    for(int i=0;i<6;i++)
    {
        if(!i)
        {
          T.l=interval[i][0];
          T.u=interval[i][1];
          T.key=0;
        }
        else
        {
           node* a=new struct node;
            a->left=nil;
            a->right=nil;
            a->parent=nil;
            a->color=0;
            a->l=interval[i][0];
            a->u=interval[i][1];
            a->key=0;
            interval_insert(T,a);
        }
    }
   keyAllocation(root);
   debug("Preorder:");
   traverse(root);
   debug("Intervals overlapping with (14,16):");
   if_find=interval_search(T,14,16);
   if(if_find->l==0)
   {
       debug("No overlap.");
   }
    debug("Intervals overlapping with (30,40):");
  if_find1=interval_search(T,30,40);
    if(if_find1->l==0)
   {
       debug("No overlap.");
   }

return 0;
}

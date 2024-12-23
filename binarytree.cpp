
/*
    C++ Program to create a Complete Binary Tree.
    amirhosein nouri mon,23 december
    for  (data structure) =>  is a specialized format for organizing, processing, retrieving and storing data
    In a complete binary tree every level, except possibly the last, is completely filled,
    and all nodes in the last level are as far left as possible.
    It can have between 1 and 2h nodes at the last level h.
    An alternative definition is a perfect tree whose rightmost leaves (perhaps all) have been removed.
    Some authors use the term complete to refer instead to a perfect binary tree as defined above,
    in which case they call this type of tree an almost complete binary tree or nearly complete binary tree.
*/

#include<iostream>
using namespace std;

class node
{
    int data;           //field to store the value of the element
    node *left,*right;  //link field to the child nodes
    friend class cbt;   //allowing class cbt to access private members of class node
};

class  cbt
{
    node *root,*temp;   //root - Root pointer to the ROOT of the Tree, temp - Temporary node pointer  pointing to the node to be inserted
public:
        cbt();
        inline node* get_root(){return root;}          //getter method for accessing root

        void accept(int);              //method to accept values to be inserted
        node* insert(node*,node*);  //method to insert node in the binary tree
        void display(node*);        //method to display the tree in InOrder traversal

        int height(node*);          //method to get height of a given node
        int bal(node*);             /*method to get the balance factor of a given node
                                    [Balance Factor = Height of Left Sub-Tree - Height of Right Sub-Tree] */
        bool check(node*);         //method to check any node with balance factor > 0
	~cbt();
};

cbt :: cbt()
{
    //initializing root node to NULL
    root = NULL;
    temp = NULL;
}

bool cbt :: check(node *r)
{
    //traversing the nodes of the subtree to check any node with balance factor > 0
    if(r == NULL)
        return false;
    bool x = check(r->left);
        if(bal(r))
            return true;
    bool y = check(r->right);

    return x||y;    //If any node present with balance factor > 0
}

void cbt :: accept(int t)
{

    for(int i=0;i<t;i++)
    {
        //creating a node to be inserted
        temp = new node;
        temp->left = NULL;
        temp->right = NULL;

        cout<<"\nEnter the element : ";
        cin>>temp->data;

        //inserting the current node in the tree
        root = insert(root,temp);
    }
}

node* cbt :: insert(node* r,node* t)
{
    //Inserting a node in the tree
    if(r == NULL)
        return t;
    else if(bal(r)==0 && check(r->right))  //Condition to insert node in the right sub-tree
        r->right = insert(r->right,t);
    else if(bal(r)==0)                      //condition to insert node in the left sub-tree
        r->left = insert(r->left,t);
    else if(bal(r)==1 && check(r->left))   //condition to insert node in the left sub-tree
        r->left = insert(r->left,t);
    else if(bal(r)==1)
        r->right = insert(r->right,t);      //condition to insert node in right sub-tree

    return r;
}

void cbt :: display(node *r)
{
    //Traversing the tree in InOrder way using recursion
    if(r == NULL)
        return;
    display(r->left);
    cout<<r->data<<"\t";
    display(r->right);
}
int cbt :: height(node *r)
{
    if(r == NULL)
        return 0;
    else
    {
        int lheight = height(r->left)+1;
        int rheight = height(r->right)+1;

    return (lheight > rheight) ? lheight : rheight; //returns maximum height
    }
}

int cbt :: bal(node *r)
{
        if(r == NULL)
            return 0;
        int lheight = height(r->left)+1;
        int rheight = height(r->right)+1;

        return (lheight - rheight); //[Balance Factor = Height of Left Sub-Tree - Height of Right Sub-Tree]
}

cbt :: ~cbt()
{
	delete root;
	delete temp;
}
int main()
{
    cbt c;  //creating object of class cbt
    int ch,t;
    do
    {
        cout<<"\n\n\t| Complete Binary Tree |\n";
        cout<<"\n1.Create";
        cout<<"\n2.Insert";
        cout<<"\n3.Display";
        cout<<"\n4.Exit";
        cout<<"\n>>";
        cin>>ch;

        switch(ch)
        {
            case 1:
                cout<<"\nEnter the total number of elements : ";
                cin>>t;
                c.accept(t);
                break;
            case 2:
                c.accept(1);
                break;
            case 3:
                if(c.get_root() == NULL)
                {
                    cout<<"\n\t**** Tree doesn't exist *****\n";
                    break;
                }
                cout<<"\n\t| Tree Elements |\n\n";
                c.display(c.get_root());
                break;
            case 4:
                cout<<"\n\t**** EXIT ****\n";
                break;
            default:
                cout<<"\n\t**** Invalid Choice ****\n";
                break;
        }
    }while(ch != 4);
    return 0;
}


// enjoy 
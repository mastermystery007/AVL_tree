// C++ program to insert a node in AVL tree
#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int key;
    Node *left;
    Node *right;
    int height;
    int count;
};
Node *newNode(int key);
Node *minValueNode(Node *node);
int max(int a, int b);
Node *newNode(int key)
{
    Node *node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    node->count = 1;

    return (node);
}
class AvlTree
{
public:
    int c = 0;
    int height(Node *N);
    void kthLargestUtil(Node *root, int k);
    void kthLargest(Node *root, int k);
    Node *rightRotate(Node *y);
    Node *leftRotate(Node *x);
    Node *insert(Node *node, int key);
    int getBalance(Node *N);
    void preOrder(Node *root);
    Node* deleteNode(Node *root, int key);
    Node* upper_bound(Node *root, int value);
    Node* lower_bound(Node *root, int value);
    Node* do_upper_bound(Node *root, int value, Node *ub);
    Node* do_lower_bound(Node *root, int value, Node *lb);
    Node* search_element(Node* root ,int val);
    int total_elements_in_range(Node *root, int low, int high);//yet to implement
    int get_element_count(Node* root , int key);
};


int AvlTree::get_element_count(Node* node , int key)
{
    Node* temp =search_element(node,key);
    return temp->count;
}



Node* AvlTree::search_element(Node* root, int key) 
{ 

    if(root==NULL){cout<<"element not present";return NULL;}
    // Base Cases: root is null or key is present at root 
    if ( root->key == key) 
       return root; 
     
    // Key is greater than root's key 
    if (root->key < key) 
       return search_element(root->right, key); 
  
    // Key is smaller than root's key 
    return search_element(root->left, key); 
} 



int AvlTree::total_elements_in_range(Node *root, int low, int high) 
{ 
    // Base case 
    if (!root) return 0; 
  
    // Special Optional case for improving efficiency 
    
  
    // If current node is in range, then include it in count and 
    // recur for left and right children of it 
    if (root->key <= high && root->key >= low) 
         return root->count + total_elements_in_range(root->left, low, high) + 
                    total_elements_in_range(root->right, low, high); 
  
    // If current node is smaller than low, then recur for right 
    // child 
    else if (root->key < low) 
         return total_elements_in_range(root->right, low, high); 
  
    // Else recur for left child 
    else return total_elements_in_range(root->left, low, high); 
} 




int AvlTree::height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

Node *AvlTree::upper_bound(Node *root, int value)
{
    Node *ub = NULL;
    ub = do_upper_bound(root, value, ub);
    return ub;
}

Node *AvlTree::lower_bound(Node *root, int value)
{
    Node *lb = NULL;
    lb = do_lower_bound(root, value, lb);
    return lb;
}

Node *AvlTree::do_upper_bound(Node *root, int value, Node *ub)
{

    if (root == nullptr)
    {
        return ub;
    }

    if (root->key > value)
    {
        ub = root;
        return do_upper_bound(root->left, value, ub);
    }
    else
    {
        return do_upper_bound(root->right, value, ub);
    }
    return ub;
}

Node *AvlTree::do_lower_bound(Node *root, int value, Node *lb)
{
    if (root == nullptr)
    {
        return lb;
    }
    if (root->key >= value)
    {
        lb = root;
        return do_lower_bound(root->left, value, lb);
    }
    else
    {
        return do_lower_bound(root->right, value, lb);
    }

    return lb;
}

void AvlTree::kthLargestUtil(Node *root, int k)
{

    if (root == NULL || c >= k)
    {
        return;
    }

    kthLargestUtil(root->right, k);

    if (c < k && (c + root->count) >= k)
    {
        c = c + root->count;
        std::cout << "K'th largest element is "
                  << root->key << endl;

        return;
    }
    else
    {
        c = c + root->count;
    }

    kthLargestUtil(root->left, k);
}

// Function to find k'th largest element
void AvlTree::kthLargest(Node *root, int k)
{

    c = 0;

    kthLargestUtil(root, k);
    cout << "c val is" << c << endl;
    c = 0;
}

Node *AvlTree::rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    y->height = max(height(y->left),
                    height(y->right)) +
                1;
    x->height = max(height(x->left),
                    height(x->right)) +
                1;

    return x;
}

Node *AvlTree::leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left),
                    height(x->right)) +
                1;
    y->height = max(height(y->left),
                    height(y->right)) +
                1;

    return y;
}

int AvlTree::getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node *minValueNode(Node *node)
{
    Node *current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

Node *AvlTree::deleteNode(Node *root, int key)
{

    // STEP 1: PERFORM STANDARD BST DELETE
    if (root == NULL)
        return root;

    // If the key to be deleted is smaller
    // than the root's key, then it lies
    // in left subtree
    if (key < root->key)
        root->left = deleteNode(root->left, key);

    // If the key to be deleted is greater
    // than the root's key, then it lies
    // in right subtree
    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    // if key is same as root's key, then
    // This is the node to be deleted
    else
    {
        // node with only one child or no child
        if ((root->left == NULL) ||
            (root->right == NULL))
        {
            Node *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else               // One child case
                *root = *temp; // Copy the contents of
                               // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            Node *temp = minValueNode(root->right);

            // Copy the inorder successor's
            // data to this node
            root->key = temp->key;
            root->count = temp->count;

            // Delete the inorder successor
            root->right = deleteNode(root->right,
                                     temp->key);
        }
    }

    if (root == NULL)
        return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),
                           height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF
    // THIS NODE (to check whether this
    // node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced,
    // then there are 4 cases

    // Left Left Case
    if (balance > 1 &&
        getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 &&
        getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 &&
        getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 &&
        getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node *AvlTree::insert(Node *node, int key)
{

    if (node == NULL)
    {
        return (newNode(key));
    }

    if (key < node->key)
    {
        node->left = insert(node->left, key);
    }

    else if (key > node->key)
    {
        node->right = insert(node->right, key);
    }

    else
    {
        (node->count)++;
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AvlTree::preOrder(Node *root)
{
    if (root != NULL)
    {
        cout << root->key << " count = ";
        cout << root->count << " " << endl;
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main()
{
    Node *root = NULL;
    AvlTree *avl = new AvlTree();
    root = avl->insert(root, 10);
    root = avl->insert(root, 20);
    root = avl->insert(root, 30);
    root = avl->insert(root, 40);
    root = avl->insert(root, 40);
    root = avl->insert(root, 40);
    // root = avl->insert(root, 40);
    root = avl->insert(root, 50);
    root = avl->insert(root, 25);
    //root = avl->insert(root, 60);
    root = avl->insert(root, 25);

    //int count = avl->get_element_count(root,40);
    
    Node * myNode = avl->search_element(root,25);
    cout<<myNode->count<<endl;
  /*  cout << "Preorder traversal of the "
            "constructed AVL tree is \n";
    avl->preOrder(root);
    cout << "Yo Mama" << endl;
    root = avl->deleteNode(root, 30);
    avl->preOrder(root);
    cout << "Yo Mama" << endl;
    root = avl->deleteNode(root, 40);

    //avl->preOrder(root);

    avl->kthLargest(root, 5);*/
  //  Node * ub = avl ->upper_bound(root,23);
  //  cout<<"val is"<<endl;
    //cout<<ub->key<<endl;
    /*root = deleteNode(root, 30);

    cout << "Preorder traversal of the "
			"constructed AVL tree is \n"; 
    preOrder(root); */

    return 0;
}

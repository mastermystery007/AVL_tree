// C++ program to insert a node in AVL tree

#include <bits/stdc++.h>
using namespace std;
template <class T>
class Node
{
public:
    T key;
    Node<T> *left;
    Node<T> *right;
    int height;
    int count;
};

template <class T>
Node<T> *newNode(T key);

template <class T>
Node<T> *minValueNode(Node<T> *node);
int max(int a, int b);

template <class T>
Node<T> *newNode(T key)
{
    Node<T> *node = new Node<T>();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    node->count = 1;

    return (node);
}
template <class T>
class AvlTree
{
public:
    int c = 0;
    int height(Node<T> *N);
    void kthLargestUtil(Node<T> *root, int k);
    void kthLargest(Node<T> *root, int k);
    Node<T> *rightRotate(Node<T> *y);
    Node<T> *leftRotate(Node<T> *x);
    Node<T> *insert(Node<T> *node, T key);
    int getBalance(Node<T> *N);
    void preOrder(Node<T> *root);
    Node<T>* deleteNode(Node<T> *root, T key);
    Node<T>* upper_bound(Node<T> *root, T value);
    Node<T>* lower_bound(Node<T> *root, T value);
    Node<T>* do_upper_bound(Node<T> *root, T value, Node<T> *ub);
    Node<T>* do_lower_bound(Node<T> *root, T value, Node<T> *lb);
    Node<T>* search_element(Node<T>* root ,T val);
    int total_elements_in_range(Node<T> *root, T low, T high);//yet to implement
    int get_element_count(Node<T>* root , T key);
};

template <class T>
int AvlTree<T>::get_element_count(Node<T>* node , T key)
{
    Node<T>* temp =search_element(node,key);
    return temp->count;
}


template <class T>
Node<T>* AvlTree<T>::search_element(Node<T>* root, T key) 
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


template <class T>
int AvlTree<T>::total_elements_in_range(Node<T> *root, T low, T high) 
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



template <class T>
int AvlTree<T>::height(Node<T> *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}
template <class T>
Node<T> *AvlTree<T>::upper_bound(Node<T> *root, T value)
{
    Node<T> *ub = NULL;
    ub = do_upper_bound(root, value, ub);
    return ub;
}
template <class T>
Node<T> *AvlTree<T>::lower_bound(Node<T> *root, T value)
{
    Node<T> *lb = NULL;
    lb = do_lower_bound(root, value, lb);
    return lb;
}
template <class T>
Node<T> *AvlTree<T>::do_upper_bound(Node<T> *root, T value, Node<T> *ub)
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
template <class T>
Node<T> *AvlTree<T>::do_lower_bound(Node<T> *root, T value, Node<T> *lb)
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
template <class T>
void AvlTree<T>::kthLargestUtil(Node<T> *root, int k)
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

template <class T>
void AvlTree<T>::kthLargest(Node<T> *root, int k)
{

    c = 0;

    kthLargestUtil(root, k);
    cout << "c val is" << c << endl;
    c = 0;
}
template <class T>
Node<T> *AvlTree<T>::rightRotate(Node<T> *y)
{
    Node<T> *x = y->left;
    Node<T> *T2 = x->right;

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
template <class T>
Node<T> *AvlTree<T>::leftRotate(Node<T> *x)
{
    Node<T> *y = x->right;
    Node<T> *T2 = y->left;

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
template <class T>
int AvlTree<T>::getBalance(Node<T> *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
template <class T>
Node<T> *minValueNode(Node<T> *node)
{
    Node<T> *current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}
template <class T>
Node<T> *AvlTree<T>::deleteNode(Node<T> *root, T key)
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
            Node<T> *temp = root->left ? root->left : root->right;

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
            Node<T> *temp = minValueNode(root->right);

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
template <class T>
Node<T> *AvlTree<T>::insert(Node<T> *node, T key)
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
template <class T>
void AvlTree<T>::preOrder(Node<T> *root)
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
    Node<int> *root = NULL;
    AvlTree<int> *avl = new AvlTree<int>();
    root = avl->insert(root, 28);
    root = avl->insert(root, 22);
    root = avl->insert(root, 18);
    root = avl->insert(root, 20);
    root = avl->insert(root, 21);
    //root = avl->insert(root, 34);
    // root = avl->insert(root, 40);
    //root = avl->insert(root, 50);
    //root = avl->insert(root, 25);
    //root = avl->insert(root, 60);
    //root = avl->insert(root, 25);

    //int count = avl->get_element_count(root,40);
    
    
   cout << "Preorder traversal of the "
            "constructed AVL tree is \n";
    avl->preOrder(root);
   /* cout << "Yo Mama" << endl;
    root = avl->deleteNode(root, 30);
    avl->preOrder(root);
    cout << "Yo Mama" << endl;
    root = avl->deleteNode(root, 40);

    //avl->preOrder(root);

    avl->kthLargest(root, 1);*/
  //  Node<T> * ub = avl ->upper_bound(root,23);
  //  cout<<"val is"<<endl;
    //cout<<ub->key<<endl;
    /*root = deleteNode(root, 30);

    cout << "Preorder traversal of the "
			"constructed AVL tree is \n"; 
    preOrder(root); */

    return 0;
}

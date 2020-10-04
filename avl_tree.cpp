// C++ program to insert a node in AVL tree 
#include<bits/stdc++.h> 
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


int max(int a, int b); 


int height(Node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return N->height; 
} 


int max(int a, int b) 
{ 
	return (a > b)? a : b; 
} 


Node* newNode(int key) 
{ 
	Node* node = new Node(); 
	node->key = key; 
	node->left = NULL; 
	node->right = NULL; 
	node->height = 1; 
    node->count = 1;
					
	return(node); 
} 

void kthLargestUtil(Node *root, int k, int &c) 
{ 
   
    if (root == NULL || c >= k) 
        return; 
  
    
    kthLargestUtil(root->right, k, c); 
  
    
    c=c+root->count; 
  
    // If c becomes k now, then this is the k'th largest  
    if (c == k) 
    { 
        cout << "K'th largest element is "
             << root->key << endl; 
        return; 
    } 
  
    // Recur for left subtree 
    kthLargestUtil(root->left, k, c); 
} 
  
// Function to find k'th largest element 
void kthLargest(Node *root, int k) 
{ 
    // Initialize count of nodes visited as 0 
    int c = 0; 
  
    // Note that c is passed by reference 
    kthLargestUtil(root, k, c); 
} 


Node *rightRotate(Node *y) 
{ 
	Node *x = y->left; 
	Node *T2 = x->right; 

	// Perform rotation 
	x->right = y; 
	y->left = T2; 

	
	y->height = max(height(y->left), 
					height(y->right)) + 1; 
	x->height = max(height(x->left), 
					height(x->right)) + 1; 

	
	return x; 
} 


Node *leftRotate(Node *x) 
{ 
	Node *y = x->right; 
	Node *T2 = y->left; 

	 
	y->left = x; 
	x->right = T2; 

	
	x->height = max(height(x->left),	 
					height(x->right)) + 1; 
	y->height = max(height(y->left), 
					height(y->right)) + 1; 

	
	return y; 
} 


int getBalance(Node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return height(N->left) - height(N->right); 
} 


Node * minValueNode(Node* node)  
{  
    Node* current = node;  
  
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)  
        current = current->left;  
  
    return current;  
}  


Node* deleteNode(Node* root, int key)  
{  
      
    // STEP 1: PERFORM STANDARD BST DELETE  
    if (root == NULL)  
        return root;  
  
    // If the key to be deleted is smaller  
    // than the root's key, then it lies 
    // in left subtree  
    if ( key < root->key )  
        root->left = deleteNode(root->left, key);  
  
    // If the key to be deleted is greater  
    // than the root's key, then it lies  
    // in right subtree  
    else if( key > root->key )  
        root->right = deleteNode(root->right, key);  
  
    // if key is same as root's key, then  
    // This is the node to be deleted  
    else
    {  
        // node with only one child or no child  
        if( (root->left == NULL) || 
            (root->right == NULL) )  
        {  
            Node *temp = root->left ?  
                         root->left :  
                         root->right;  
  
            // No child case  
            if (temp == NULL)  
            {  
                temp = root;  
                root = NULL;  
            }  
            else // One child case  
            *root = *temp; // Copy the contents of  
                           // the non-empty child  
            free(temp);  
        }  
        else
        {  
            // node with two children: Get the inorder  
            // successor (smallest in the right subtree)  
            Node* temp = minValueNode(root->right);  
  
            // Copy the inorder successor's  
            // data to this node  
            root->key = temp->key;  
            root->count=temp->count;
  
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
  






Node* insert(Node* node, int key) 
{ 
	
	if (node == NULL) {return(newNode(key));} 

	

    
    if (key < node->key) {node->left = insert(node->left, key);} 
	
    else if (key > node->key) {node->right = insert(node->right, key);} 
	
    else {(node->count)++; return node;}

	
	node->height = 1 + max(height(node->left),height(node->right)); 

	
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


void preOrder(Node *root) 
{ 
	if(root != NULL) 
	{ 
		cout << root->key << " count = "; 
        cout << root->count << " "<<endl; 
		preOrder(root->left); 
		preOrder(root->right); 
	} 
} 


int main() 
{ 
	Node *root = NULL; 
	
	root = insert(root, 10); 
	root = insert(root, 20); 
	root = insert(root, 30); 
	root = insert(root, 40); 
    root = insert(root, 40); 
    root = insert(root, 45); 
	root = insert(root, 25); 
	root = insert(root, 25); 
	
	
	cout << "Preorder traversal of the "
			"constructed AVL tree is \n"; 
	preOrder(root); 

    root = deleteNode(root, 30);

    cout << "Preorder traversal of the "
			"constructed AVL tree is \n"; 
    preOrder(root); 
	
	return 0; 
} 



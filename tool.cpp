/* Dynamic programming based program 
for Largest Independent Set problem */
#include <bits/stdc++.h>
#include <string>
#include <queue>
using namespace std; 

// A utility function to find max of two integers 
int max(int x, int y) { return (x > y)? x: y; } 

/* A binary tree node has data, pointer
to left child and a pointer to 
right child */
class node 
{ 
	public:
	int data; 
	int liss; 
	node *left, *right; 
}; 

// A utility function to create a node 
node* newNode(int data) 
{ 
	node* temp = new node(); 
	temp->data = data; 
	temp->left = temp->right = NULL; 
	temp->liss = 0; 
	return temp; 
} 

int get_depth_of_tree(node *root) {
    if (root == NULL) {
        return 0;
    }
    
    return 1 + max(get_depth_of_tree(root->left), get_depth_of_tree(root->right));
}

string print_tree(node *root) {
    if (root == NULL) {
        return "";
    }
    
    string result = "";
    int level = get_depth_of_tree(root);
    string indent = "";
    for (int i = 1; i < level; i++) {
        indent += "  ";
    }
    result += indent;
    level = level/2;
    queue<node*> q;
    q.push(root);

    
    while (!q.empty()) {
        int size = q.size();
        
        for (int i = 0; i < size; i++) {
            node* curr = q.front();
            q.pop();

            if (curr == NULL) {
                result += indent;
                continue;
            }
            
            result += to_string(curr->data) + indent;
            
            if (curr->left) {
                q.push(curr->left);
            }
            else {
                q.push(NULL);
            }
            
            if (curr->right) {
                q.push(curr->right);
            }
        }
        
        
        string indent = "";
        for (int i = 1; i < level; i++) {
            indent += "  ";
        }
        level = level/2;
        
        result += "\n" + indent;
    }
    
    return result;
}

// A memoization function returns size 
// of the largest independent set in 
// a given binary tree 
int LISS(node *root) 
{ 
	if (root == NULL) 
		return 0; 

	if (root->liss) 
		return root->liss; 

	if (root->left == NULL && root->right == NULL) 
		return (root->liss = 1); 

	// Calculate size excluding the current node 
	int liss_excl = LISS(root->left) + LISS(root->right); 

	// Calculate size including the current node 
	int liss_incl = 1; 
	if (root->left) 
		liss_incl += LISS(root->left->left) + LISS(root->left->right); 
	if (root->right) 
		liss_incl += LISS(root->right->left) + LISS(root->right->right); 

	// Maximum of two sizes is LISS, store it for future uses. 
	root->liss = max(liss_incl, liss_excl); 

	return root->liss; 
} 

// Driver code
int main() 
{ 
	// Let us construct the tree 
	// given in the above diagram 
	node *root	 = newNode(20); 
	root->left		 = newNode(8); 
	root->left->left	 = newNode(4); 
	root->left->right	 = newNode(12); 
	root->left->right->left = newNode(10); 
	root->left->right->right = newNode(14); 
	root->right		 = newNode(22); 
	root->right->right	 = newNode(25); 

    cout << "Tree: \r\n" << print_tree(root) << endl;

    cout << "Depth of the tree: " << get_depth_of_tree(root) << endl;


	cout << "Size of the Largest Independent Set is " << LISS(root)
                                                        << endl;



	return 0; 
} 

// This code is contributed by rathbhupendra

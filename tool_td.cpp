#include "IS.h"

// Maximum number of rows for the 2D array
const int MAX_ROWS = 100;
// Maximum number of columns for the 2D array
const int MAX_COLS = 3;

// A utility function to find max of two integers 
int max(int x, int y) { return (x > y)? x: y; } 


// A utility function to create a node 
node* newNode() 
{ 
	node* temp = new node(); 
	temp->data = "data uninitialized"; 
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

string print_tree(node *root, bool do_indent = false) {
    if (root == NULL) {
        return "";
    }
    
    string result = "";
    int level = get_depth_of_tree(root);
    string indent = " ";
    
    if(do_indent)
    {
        for (int i = 1; i < level; i++) {
        indent += "  ";
        }
        cout << indent << flush;
    }
    
    level = level/2;
    queue<node*> q;
    q.push(root);

    
    // i tried very long to  make this print function work
    // with my original example it did in fact work, but now since introducing the hashmap, which is not even used here, it just show erractic behaviour which i cannot explain
    // when i add additional output for debugging it at least prints all the nodes but partly splits up the data (the vertices in a bag), which are just stored as a string together
    // i tried adding flush everywhere to avoid buffering issues, but it did not help
    // even after a lot of googling i could not find a solution

    while (!q.empty()) {
        int size = q.size();
        //cout << "queue length: " << q.size() << endl << flush;
        for (int i = 0; i < size; i++) {
            node* curr = q.front();
            q.pop();

            if (curr == NULL) {
                cout << "___" << flush;
                continue;
            }
            
            cout << curr->data << flush;
            cout << "+" << flush; // there is no way this should be at the beginning of the line
            // i originally used whitespaces here but to distinguish between the cases i changed to + and ___
            q.push(curr->left);
            q.push(curr->right);
        }

        
        
        
        if(do_indent)
        {
            for (int i = 1; i < level; i++) {
            indent += "  ";
            }
            cout << indent << flush;
        }
    
        level = level/2;
        
        cout << endl;
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

string read_td_from_file(string data[MAX_ROWS][3]){
    // Open the CSV file
    ifstream file("input/nice_td.csv");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return "error";
    }

    // Define a 2D array to store the CSV data
    string root_index = "";
    string line;
    int row = 0;
    // Store the CSV data from the CSV file to the 2D array
    while (getline(file, line) && row < MAX_ROWS) {
        stringstream ss(line);
        string cell;
        int col = 0;
        while (getline(ss, cell, ',') && col < MAX_COLS) {
            data[row][col] = cell;
            if(root_index == ""){
                root_index = cell;
            }
            //cout << cell << endl << flush;
            //cout << data[row][col] << endl << flush;
            col++;
        }
        row++;
        
    }
    

    

    // close the file after read opeartion is complete
    file.close();
    return root_index;

    // Print the data stored in the 2D array
    /*for (int i = 0; i < row; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            cout << data[i][j] << flush;
            flush(cout);
        }
        cout << endl << flush;
    }


    cout << data[0][0] + "," << data[0][1] + "," << data[0][2] << endl << flush; */

}

int read_graph_from_file(string data[MAX_ROWS][2]){
    // Open the CSV file
    ifstream file("input/graph.csv");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 0;
    }

    string line;
    int row = 0;
    // Store the CSV data from the CSV file to the 2D array
    while (getline(file, line) && row < MAX_ROWS) {
        stringstream ss(line);
        string cell;
        int col = 0;
        while (getline(ss, cell, ',') && col < MAX_COLS) {
            data[row][col] = cell;
            //cout << cell << endl << flush;
            //cout << data[row][col] << endl << flush;
            col++;
        }
        row++;
        
    }
    

    

    // close the file after read opeartion is complete
    file.close();

    // Print the data stored in the 2D array
    cout << "Graph edges: " << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < 2; j++) {
            cout << data[i][j] << flush;
            flush(cout);
        }
        cout << endl << flush;
    }

    return row+1;
}

unordered_map<string, node*> new_td(string data[100][3]){
    cout << "Tree Decomposition: " << endl;
    unordered_map<string, node*> td;
    for(int i = 0; i < MAX_ROWS; i++){
        if(data[i][0].empty() && data[i][1].empty()){
            break;
        }
        // case: edge
        if(data[i][1].rfind("N", 0) == 0){
            // check if the nodes A->B are already in the tree
            // if not, create them
            if(td.find(data[i][0]) == td.end()){
                td[data[i][0]] = newNode();
            }
            if(td.find(data[i][1]) == td.end()){
                td[data[i][1]] = newNode();
            }
            // print
            cout << "edge: " << data[i][0] << " " << data[i][1] << endl << flush;
            // add edge as B is a child of A 
            // first one to appear in file gets added as left child
            if(td[data[i][0]]->left == NULL){
                td[data[i][0]]->left = td[data[i][1]];
            }
            else{
                td[data[i][0]]->right = td[data[i][1]];
            }
        }
        // case: bag
        else{
            if(td.find(data[i][0]) == td.end()){
                td[data[i][0]] = newNode();
            }
            td[data[i][0]]->data = data[i][2];
            cout << "bag: " << data[i][0] << " " << td[data[i][0]]->data << endl << flush;
        }
        /*for(int j = 0; j < MAX_COLS; j++){
            
            cout << data[i][j] << flush;
            flush(cout);
        }
        cout << endl << flush; */
    }
    return td;
}

unordered_map<string, string> new_graph(string data[100][2]){
    unordered_map<string, string> graph;
    for(int i = 0; i < MAX_ROWS; i++){
        if(data[i][0].empty() && data[i][1].empty()){
            break;
        }
        if(graph.find(data[i][0]) == graph.end()){
            graph[data[i][0]] = data[i][1];
        }
        else
        {
            graph[data[i][0]] += "," + data[i][1];
        }
        if(graph.find(data[i][1]) == graph.end()){
            graph[data[i][1]] = data[i][0];
        }
        else
        {
            graph[data[i][1]] += "," + data[i][0];
        }
    }
    return graph;
}


// Driver code
int main() 
{ 
	// Let us construct the tree 
	// given in the above diagram 
	/*node *root	 = newNode(20); 
	root->left		 = newNode(8); 
	root->left->left	 = newNode(4); 
	root->left->right	 = newNode(12); 
	root->left->right->left = newNode(10); 
	root->left->right->right = newNode(14); 
	root->right		 = newNode(22); 
	root->right->right	 = newNode(25); 

    cout << "Tree: \r\n" << print_tree(root) << endl << flush;

    cout << "Depth of the tree: " << get_depth_of_tree(root) << endl << flush;


	cout << "Size of the Largest Independent Set is " << LISS(root)
                                                        << endl; */

    string graph_data[MAX_ROWS][2] = {};
    string data[MAX_ROWS][MAX_COLS] = {};
    int max_nr_verteces = read_graph_from_file(graph_data);
    unordered_map<string, string> graph = new_graph(graph_data);
    

    string root_index = read_td_from_file(data);
    // cout << "Data: " << data[0][0] + "," << data[0][1] + "," << data[0][2] << endl << flush;
    unordered_map<string, node*> td = new_td(data);
    //new_td(data, td);

    //cout << "child of child of etc. " << "N1" << ": " << td["N1"]->left->left->right->left->left->left->left->data << endl << flush;
    // i wrote a function to print the tree, but it does not work as expected
    // i explain above in the function definition for print_tree 
    //print_tree(td[root_index]);

   /* for(int i = 1; i <= 21; i++)
    {
        cout << "N" << i << ": " << td["N" + to_string(i)]->data << endl;

    } */


    //cout << "neighbors of e:" << flush;
    // print all neighbors of e
    // for loop through a:f
    //string abc[] = {"a", "b", "c", "d", "e", "f"};
    /*string abc = "f";
    vector<string> abcd = split(abc, ",");
    for(string a : abcd)
    {
        // convert char c to string
        //cout << "neighbors of " << c << ":" << flush;
        cout << a << " neighbors: " << graph[a] << endl;
    }
    cout << graph["e"] << endl;
    cout << graph["f"] << endl;
    */
    

    find_max_IS(td[root_index], graph);
    vector<string> lis = td[root_index]->lis_map["b"];

   /*  cout << "largest independent set found: " << endl;
    cout << lis.size() << endl;
    for(string a : lis)
    {
        cout << a << endl;
    }
 */



	return 0; 
} 

// This code is contributed by rathbhupendra

/* Dynamic programming based program 
for Largest Independent Set problem */
#include <bits/stdc++.h>
#include <string>
#include <queue>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
// import file compute_IS.cpp
//#include "compute_IS.cpp"
using namespace std;

class node 
{ 
	public:
	string data; 
	int liss = 0; 
    vector<string> lis;
    unordered_map<string, vector<string>> lis_map;
    unordered_map<string, int> liss_map;
	node *left, *right; 
}; 

int size_of_bag(string bag)
{
    // count number of ; in bag
    int count = 0;
    for(int i = 0; i < bag.length(); i++)
    {
        if(bag[i] == ';')
        {
            count++;
        }
    }

    // vertices are semicolon-separated as per assignment description, thus number of vertices = number of semicolons + 1
    return count+1;
}

vector<string> split(string str, string token)
{
    vector<string>result;
    while(str.size())
    {
        int index = str.find(token);
        if(index != string::npos)
        {
            result.push_back(str.substr(0,index));
            str = str.substr(index+token.size());
            if(str.size() == 0)result.push_back(str);
        }
        else
        {
            result.push_back(str);
            str = "";
        }
    }
    return result;
}

bool compareFunction (std::string a, std::string b) {return a<b;} 
//compare any way you like, here I am using the default string comparison

string vector_to_string(vector<string> vec)
{
    string result = "";
    for(string vertex : vec)
    {
        result += vertex;
        result += ";";
    }
    // remove last ;   
    result = result.substr(0, result.size()-1);
    return result;
}



bool check_if_subset_is_IS(vector<string>subset,  unordered_map<string,string> graph)
{
    for(string vertex : subset)
    {
        vertex = vertex[0];
        
        vector<string> neighbors =  split(graph[vertex], ",");
        
        for(string neighbor : neighbors){
        //cout << neighbor << " ";
        //vector<string> neighbors_of_neighbors = split(graph[neighbor], ",");
        if(std::find(subset.begin(), subset.end(), neighbor) != subset.end())
        {
                // if true means it loops back to the vertex --> not an IS
                //cout << "!!!!" << endl;
                return false;
        }

        // check if vector neighbors_of_neighbors contains any vertex in verteces_in_bag
            /*for(string neighbor_of_neighbor : neighbors_of_neighbors)
            {
                if(std::find(verteces_in_bag.begin(), verteces_in_bag.end(), neighbor_of_neighbor) != verteces_in_bag.end())
                {
                    // if true means it loops back to the vertex --> not an IS
                    //break;
                }
            } */



        }
        
    }
    return true;
}

void leaf_node(node *node,  unordered_map<string,string> graph)
{
    // split node->data by ;
    vector<string> verteces_in_bag = split(node->data, ";");
    //cout << "leaf node: " << verteces_in_bag[0][0] << " legnth " << verteces_in_bag[0][0] << endl; 
    //cout << "leaf node: " << node->data << endl;
    //cout << graph[(string(1,verteces_in_bag[0][0]))] << endl;

    // iterate through all subsets of verteces_in_bag
    int n = verteces_in_bag.size();
    for (int i = (1 << n); i > 0; i--) {
        vector<string> subset;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                subset.push_back(verteces_in_bag[j]);
            }
        }

        /*if(subset.size() <= node->liss)
        {
            // already found a bigger IS than this subset so no need to check
            continue;
        }*/

        cout << "subset: " << vector_to_string(subset) << endl; 

        if(check_if_subset_is_IS(subset, graph))
        {
            node->lis_map[vector_to_string(subset)] = subset;
            node->liss_map[vector_to_string(subset)] = subset.size();
        }
        else
        {
            node->lis_map[vector_to_string(subset)] = {};
            node->liss_map[vector_to_string(subset)] = 0;
        }
        
        cout << "IS for subset " << vector_to_string(subset) << endl;
        cout << vector_to_string(node->lis_map[vector_to_string(subset)]) << endl;
        
        

    }



    
    // for each subset S in bag x(t), check if S is an IS
    
    /* cout << "Max IS for leaf node " << node->data << endl;
    for(string vertex : node->lis)
    {
        cout << vertex << flush;
    }
    cout << endl; */
}

void introduce_node(node *node,  unordered_map<string,string> graph)
{
    vector<string> verteces_in_bag = split(node->data, ";");
    //cout << "leaf node: " << verteces_in_bag[0][0] << " legnth " << verteces_in_bag[0][0] << endl; 
    
    //cout << graph[(string(1,verteces_in_bag[0][0]))] << endl;

    // node v is the node that was introduced
    // get v by checking what is in node->data but not in node->left->data
    vector<string> verteces_in_bag_left = split(node->left->data, ";");
    string v = "";
    for(string vertex : verteces_in_bag)
    {
        // again problems with the string comparison, there seem to be artifacts that prevent an efficient comparision in c++
        /*if(std::find(verteces_in_bag_left.begin(), verteces_in_bag_left.end(), vertex) == verteces_in_bag_left.end())
        {
            v = vertex;
            //break;
        }*/
        v = vertex;
        for(string vertex_left : verteces_in_bag_left)
        {
            if(vertex[0] == vertex_left[0])
            {
                v = "";
                break;
            }
        }
        if(v != "")
        {
            break;
        }
    }

    cout << "v = " << v << endl;

    // iterate through all subsets of verteces_in_bag
    int n = verteces_in_bag.size();
    for (int i = (1 << n); i > 0; i--) {
        vector<string> subset;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                subset.push_back(verteces_in_bag[j]);
            }
        }

        /* /////// DEBUG
        //cout << "subset before ordering: " << flush;
        
        cout << subset.size() << flush;
        for(string vertex : subset)
        {
            cout << vertex << flush;
        }
        cout << endl;

        //cout << "subset after ordering: " << flush;
        std::sort(subset.begin(), subset.end(),compareFunction);
        cout << subset.size() << flush;
        for(string vertex : subset)
        {
            cout << vertex << flush;
        }
        cout << endl;

        /////// */
        
        if(subset.size() <= node->liss)
        {
            // already found a bigger IS than this subset so no need to check
            continue;
        }

        // v is not contained in U
        if(std::find(subset.begin(), subset.end(), v) == subset.end())
        {
            node->lis_map[vector_to_string(subset)] = node->left->lis_map[vector_to_string(subset)];
            node->liss_map[vector_to_string(subset)] = node->left->liss_map[vector_to_string(subset)];
        }
        else{
            // v is contained in U
            // write new function to just check if v is connected to any other node in U
            // since we already know that U' is an IS
            if(check_if_subset_is_IS(subset, graph))
            {   

                // make a deep copy of subset
                vector<string> subset_without_v = subset;

                // get IS_t'(U\{v}) from left node
                subset_without_v.erase(std::remove(subset_without_v.begin(), subset_without_v.end(), v), subset_without_v.end());



                // IS_t(U) = S union {v}
                // we already checked that U is in IS
                // S = IS_t'(U\{v})
                vector<string> IS_t_prime =  node->left->lis_map[vector_to_string(subset_without_v)];
                IS_t_prime.push_back(v);
                node->lis_map[vector_to_string(subset)] = IS_t_prime;
                node->liss_map[vector_to_string(subset)] = node->left->liss_map[vector_to_string(subset_without_v)] + 1;
            }
            else{
                node->lis_map[vector_to_string(subset)] = {};
                node->liss_map[vector_to_string(subset)] = 0;
            }
        }

        cout << "IS for subset " << vector_to_string(subset) << endl;
        cout << vector_to_string(node->lis_map[vector_to_string(subset)]) << endl;
        

    }
   /*  cout << "Max IS for introduce node " << node->data << endl; // << "is size " << node->liss << ": " << endl;
    for(string vertex : node->lis)
    {
        cout << vertex <<  flush;
    }
    cout << endl; */

    
}

void forget_node(node *node,  unordered_map<string,string> graph)
{
    vector<string> verteces_in_bag = split(node->data, ";");
    //cout << "leaf node: " << verteces_in_bag[0][0] << " legnth " << verteces_in_bag[0][0] << endl; 
    
    //cout << graph[(string(1,verteces_in_bag[0][0]))] << endl;

    // node v is the node that was introduced
    // get v by checking what is in node->data but not in node->left->data
    vector<string> verteces_in_bag_left = split(node->left->data, ";");
    string v = "";
    for(string vertex_left : verteces_in_bag_left)
    {
        // again problems with the string comparison, there seem to be artifacts that prevent an efficient comparision in c++
        /*if(std::find(verteces_in_bag_left.begin(), verteces_in_bag_left.end(), vertex) == verteces_in_bag_left.end())
        {
            v = vertex;
            //break;
        }*/
        v = vertex_left;
        for(string vertex : verteces_in_bag)
        {
            if(vertex[0] == vertex_left[0])
            {
                v = "";
                break;
            }
        }
        if(v != "")
        {
            break;
        }
    }

    cout << "v = " << v << endl;

    // iterate through all subsets of verteces_in_bag
    int n = verteces_in_bag.size();
    for (int i = (1 << n); i > 0; i--) {
        vector<string> subset;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                subset.push_back(verteces_in_bag[j]);
            }
        }
        
        /* // I only consider subsets that are potentially larger than the current largest IS
        // not sure if this is correct to dismiss smaller ISs in IS_t(U) at this point already
        if(subset.size() + 1 < node->liss)
        {
            // already found a bigger IS than this subset so no need to check
            continue;
        }
 */
        // n_t(U) = max(n_t'(U), n_t'(U union v))
        // n_t'(U)
        // n_t'(U union v)

        vector<string> v1 = node->left->lis_map[vector_to_string(subset)];
        vector<string> subset_with_v = subset;
        subset_with_v.push_back(v);
        vector<string> v2 = node->left->lis_map[vector_to_string(subset_with_v)];

        // IS_t(U) = IS_t'(U) union IS_t'(U union v)
        // attempt to union in somewhat acceptable time in C++ 
        // std::set_union would require sorting, which previously didn't work
        // I blame it on artefacts in the strings, but maybe cout was just bugging and it did in fact work
        // since n_t(U) = max(n_t'(U), n_t'(U union v)) could we replace IS_t(U) = IS_t'(U) union IS_t'(U union v) by just taking IS_t' of whatever has the bigger n_t'() ?
        vector<string> res;
        for(string a : v1)
        {
            if(std::find(res.begin(), res.end(), a) == res.end())
            {
                res.push_back(a);
            }
        }
        for(string a : v2)
        {
            if(std::find(res.begin(), res.end(), a) == res.end())
            {
                res.push_back(a);
            }
        }

       /*  cout << "v1: " << vector_to_string(v1) << endl;
        cout << "v2: " << vector_to_string(v2) << endl;
        cout << "v1 union v2: " << vector_to_string(res) << endl; */

        node->lis_map[vector_to_string(subset)] = res;
        node->liss_map[vector_to_string(subset)] = max(node->left->liss_map[vector_to_string(subset)],node->left->liss_map[vector_to_string(subset_with_v)]);

        cout << "IS for subset " << vector_to_string(subset) << endl;
        cout << vector_to_string(subset) << endl;
        cout << vector_to_string(subset_with_v) << endl;
        cout << vector_to_string(node->lis_map[vector_to_string(subset)]) << endl;
        

    }

    

}

void join_node(node *node,  unordered_map<string,string> graph)
{
    vector<string> verteces_in_bag = split(node->data, ";");

     int n = verteces_in_bag.size();
    for (int i = (1 << n); i > 0; i--) {
        vector<string> subset;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                subset.push_back(verteces_in_bag[j]);
            }
        }
        
        /* // I only consider subsets that are potentially larger than the current largest IS
        // not sure if this is correct to dismiss smaller ISs in IS_t(U) at this point already
        if(subset.size() + 1 < node->liss)
        {
            // already found a bigger IS than this subset so no need to check
            continue;
        }
 */
        // n_t(U) = max(n_t'(U), n_t'(U union v))
        // n_t'(U)
        // n_t'(U union v)

        vector<string> v1 = node->left->lis_map[vector_to_string(subset)];
        vector<string> v2 = node->right->lis_map[vector_to_string(subset)];

        // IS_t(U) = IS_t'(U) union IS_t'(U union v)
        // attempt to union in somewhat acceptable time in C++ 
        // std::set_union would require sorting, which previously didn't work
        // I blame it on artefacts in the strings, but maybe cout was just bugging and it did in fact work
        // since n_t(U) = max(n_t'(U), n_t'(U union v)) could we replace IS_t(U) = IS_t'(U) union IS_t'(U union v) by just taking IS_t' of whatever has the bigger n_t'() ?
        vector<string> res;
        for(string a : v1)
        {
            if(std::find(res.begin(), res.end(), a) == res.end())
            {
                res.push_back(a);
            }
        }
        for(string a : v2)
        {
            if(std::find(res.begin(), res.end(), a) == res.end())
            {
                res.push_back(a);
            }
        }

        /*for(string a: res)
        {
            cout << a << " ";
        }*/
        node->lis_map[vector_to_string(subset)] = res;
        node->liss_map[vector_to_string(subset)] = node->left->liss_map[vector_to_string(subset)] + node->left->liss_map[vector_to_string(subset)] - subset.size();

        cout << "IS for subset " << vector_to_string(subset) << endl;
        cout << vector_to_string(node->lis_map[vector_to_string(subset)]) << endl;
    }


}



void case_distinction(node *root, unordered_map<string,string> graph)
{   

    // first go down whole tree
    if(root->left)
    {
        case_distinction(root->left,graph);
    }
    if(root->right)
    {
        case_distinction(root->right,graph);
    }

    // until we reach the leaf nodes
    if(root->left == NULL && root->right == NULL)
    {
        cout << "######### leaf node " << root->data << endl; 
        leaf_node(root,graph);
    }

    // afterwards distinguish between introduce, forget and join nodes

    // introduce and forget nodes
    if((root->left && !root->right))
    {
        if(root->data.length() > root->left->data.length()){
        
            cout << "-------- introduce node " << root->data << endl;
            introduce_node(root, graph);
            // Mt(U) := Mt′(U∖{v}) + 1
        }
        else if (root->data.length() < root->left->data.length())
        {
            cout << "--------- forget node " << root->data << endl;
            forget_node(root, graph);
        }
        else{
            cout << "werid error case" << root->data << endl;
            return; 
        }
        // string length of root->data
    }

    if(root->left && root->right)
    {
        // join node
        cout << "--------- join node " << root->data << endl;
        join_node(root, graph);
    }
    
}

void find_max_IS(node *root, unordered_map<string,string> graph)
{
    vector<string> verteces_in_bag = split(root->data, ";");
    int n = verteces_in_bag.size();
    case_distinction(root, graph);
    cout << "ISs found for graph based on TD: " << endl;
    for (int i = (1 << n); i > 0; i--) {
        vector<string> subset;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                subset.push_back(verteces_in_bag[j]);
            }
        }

        cout << vector_to_string(subset) << endl;
        vector<string> is_found = root->lis_map[vector_to_string(subset)];
        for(string is : is_found)
        {
            cout << is << endl;
        }
    }
}
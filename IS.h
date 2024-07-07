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
	int liss; 
    //char lis[];
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

void leaf_node(node *node,  unordered_map<string,string> graph)
{
    // split node->data by ;
    vector<string> verteces_in_bag = split(node->data, ";");
    cout << "leaf node: " << verteces_in_bag[0][0] << " legnth " << verteces_in_bag[0][0] << endl; 
    cout << graph[(string(1,verteces_in_bag[1][0]))] << endl;

    
    for(string vertex : verteces_in_bag)
    {
        int i = 0;  
        
        //vector<string> neighbors =  split(graph[vertex], ",");
        //cout << "neighbors length " << neighbors.size() << endl;
        //cout << "vertex " << vertex << endl;
        /*for(string neighbor : neighbors){
           cout << neighbor << endl;
        }*/
        //cout << endl;
    }
}

void introduce_node(node *root, string data)
{
    root->data = data;
    root->left = NULL;
    root->right = NULL;
}


void case_distinction(node *root, unordered_map<string,string> graph)
{   
    ////cout << size_of_bag(root->data) << endl;
    if(root->left == NULL && root->right == NULL)
    {
        leaf_node(root,graph);
    }

    if(root->left)
    {
        case_distinction(root->left,graph);
    }
    if(root->right)
    {
        case_distinction(root->right,graph);
    }
    
}


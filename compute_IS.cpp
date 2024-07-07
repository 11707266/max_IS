#include "IS.h"

void case_distinction(node *root)
{
    if(root->left == NULL && root->right == NULL)
    {
        cout << "leaf" << endl << flush;
    }
    else if(root->left == NULL || root->right == NULL)
    {
        cout << "one child" << endl << flush;
    }
    else
    {
        cout << "two children" << endl << flush;
    }
}
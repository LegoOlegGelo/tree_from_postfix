#include "node.h"
#include <iostream>

using namespace std;

void print_as_tree(node* n, int tabs)
{
    if (!n) return;

    for (size_t i = 0; i < tabs + 1; i++)
        cout << "\t";
    print_as_tree(n->right, tabs + 1);
    cout << endl;

    for (size_t i = 0; i < tabs; i++)
        cout << "\t";
    cout << n->val;
    cout << endl;

    for (size_t i = 0; i < tabs + 1; i++)
        cout << "\t";
    print_as_tree(n->left, tabs + 1);
    cout << endl;
}
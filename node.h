#pragma once

struct node
{
    node* left = nullptr;
    node* right = nullptr;
    bool is_oper = false;
    char* val;
};

void print_as_tree(node* n, int tabs = 0);
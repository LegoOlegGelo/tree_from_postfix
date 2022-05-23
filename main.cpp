#include <iostream>
#include <string.h>
#include "node.h"
#include "list.h"

using namespace std;

int is_oper(char* a)
{
    return strlen(a) == 1 && (a[0] == '+' || a[0] == '-' || a[0] == '*' || a[0] == '/');
}

void zero_fill(char* s, int len)
{
    for (size_t i = 0; i < len; i++)
        s[i] = 0;
}

// выражение в виде строки переводим в список из node;
// каждый токен в строке - отдельный node
list* get_list_of_nodes_by_mathexpr(const char* expr)
{
    int len = strlen(expr);

    list* nodes = nullptr;

    char* temp = new char[len + 1];
    zero_fill(temp, len + 1);
    int k = 0;

    for (size_t i = 0; i < len; i++)
    {
        temp[k] = expr[i];

        if (expr[i + 1] == ' ' || i + 1 == len)
        {
            node* n = new node;
            n->is_oper = is_oper(temp);
            temp[k + 1] = 0;
            n->val = strdup(temp);
            add_to_list(nodes, n);

            zero_fill(temp, len);
            k = 0;
            i++;
            continue;
        }
    }

    return nodes;
}

// из списка node в единое дерево
node* get_tree_from_postfix(list* nodes)
{
    int i = 0;
    int len = get_list_len(nodes);
    
    while (len > 1) // list length не может быть = 2 (т.к. в выражении должны быть 2 числа и бинарная операция)
    {
        if (i + 2 >= len) i = 0;

        node* n0 = list_get(nodes, i);
        node* n1 = list_get(nodes, i + 1);
        node* n2 = list_get(nodes, i + 2);

        if (n2->is_oper)
        {
            n2->left = n0;
            n2->right = n1;

            list_remove_at(nodes, i + 1);
            list_remove_at(nodes, i);

            i -= 2;
        }

        i++;
        

        for (size_t i = 0; i < get_list_len(nodes); i++)
        {
            cout << "[" << i << "]: " << list_get(nodes, i)->val << endl;
        }
        cout << endl;
    }

    return nodes->x;
}

int main()
{
    const char* expression = "2 3 - 3 1 4 * + +";

    list* nodes = get_list_of_nodes_by_mathexpr(expression);
        

    for (size_t i = 0; i < get_list_len(nodes); i++)
    {
        cout << "[" << i << "]: " << list_get(nodes, i)->val << endl;
    }
    cout << endl;
    
    node* tree = get_tree_from_postfix(nodes);

    print_as_tree(tree);

    return 0;
}
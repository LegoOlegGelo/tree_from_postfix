#include <iostream>
#include <string.h>

using namespace std;


#pragma region NODE
struct node
{
    char* val = nullptr;
    int type = 0; // 0 - число; 2 - бинарная операция
    node* left = nullptr;
    node* right = nullptr;
};

void print_node(node* n, int tabs = 0)
{
    if (!n) return;

    print_node(n->right, tabs + 1);

    for (size_t i = 0; i < tabs; i++) cout << "\t";
    cout << n->val << endl;

    print_node(n->left, tabs + 1);
}

int get_weight(char* s)
{
    // 2 - бинарная операция; 0 - число
    
    if (!strcmp(s, "*")) return 2;
    if (!strcmp(s, "/")) return 2;
    if (!strcmp(s, "+")) return 1;
    if (!strcmp(s, "-")) return 1;

    return 0;
}

void print_infix(node* n, int weight = 0)
{
    if (!n) return;

    int cur_weight = get_weight(n->val);

    if (weight > cur_weight && n->left)
        cout << "(";

    if (n->left)
        print_infix(n->left, cur_weight);

    cout << n->val;

    if (n->right)
        print_infix(n->right, cur_weight);

    if (weight > cur_weight &&  n->right)
        cout << ")";
}

// postfix - то же самое, что и RPN (обратная польская запись)
void print_postfix(node* n)
{
    if (!n) return;

    print_postfix(n->left);
    print_postfix(n->right);
    cout << n->val << " ";
}
#pragma endregion


#pragma region LIST
struct list
{
    list* next = nullptr;
    node* val = nullptr;
};

void add_to_list(list*& l, node* n)
{
    list* new_el = new list;
    new_el->val = n;

    if (!l)
    {
        l = new_el;
        return;
    }

    list* cur = l;

    while (cur->next)
        cur = cur->next;
    
    cur->next = new_el;
}

int get_list_len(list* l)
{
    int len = 0;
    
    while (l)
    {
        l = l->next;
        len++;
    }
    
    return len;
}

void print_list(list* l)
{
    while (l)
    {
        cout << l->val->val << endl;
        l = l->next;
    }
}
#pragma endregion


#pragma region STACK
struct stack
{
    stack* next = nullptr;
    node* val = nullptr;
};

void push(stack*& s, node* val)
{
    stack* new_el = new stack;
    new_el->val = val;

    if (!s)
    {
        s = new_el;
        return;
    }

    new_el->next = s;
    s = new_el;
}

node* pop(stack*& s)
{
    if (!s) return nullptr;

    stack* top = s;
    s = s->next;

    return top->val;
}

void print_stack(stack* st)
{
    while (st)
    {
        cout << st->val << endl;
        st = st->next;
    }
}
#pragma endregion


#pragma region TREE_BY_EXPRESSION
int get_token_type(char* s)
{
    // 2 - бинарная операция; 0 - число
    
    if (!strcmp(s, "*")) return 2;
    if (!strcmp(s, "/")) return 2;
    if (!strcmp(s, "+")) return 2;
    if (!strcmp(s, "-")) return 2;

    return 0;
}

list* get_tokens(const char* expr)
{
    // копируем строку
    int expr_len = strlen(expr);
    char* expr_copy = new char[expr_len + 1];

    for (size_t i = 0; i < expr_len; i++)
        expr_copy[i] = expr[i];
    
    expr_copy[expr_len] = 0;
    

    // разбиваем строку на токены (подстроки) и создаем список нод
    char* cont = nullptr;
    list* tokens = nullptr; // список нод

    while (char* part = strtok_r(expr_copy, " ", &cont))
    {
        expr_copy = nullptr;

        node* n = new node;
        n->val = strdup(part);
        n->type = get_token_type(part);

        add_to_list(tokens, n);
    }

    list* tokens_copy = tokens;
    
    return tokens;
}

node* get_tree(const char* expr)
{
    // получаем токены (подстроки "2", "+" и т.д.)
    list* tokens = get_tokens(expr);
    list* tokens_copy = tokens; // для очищения помяти

    stack* st = nullptr;

    int i = get_list_len(tokens);

    while (i > 0 || st->next)
    {
        node* n = tokens->val;

        if (n->type == 0)
        {
            push(st, n);
        }
        else if (n->type == 2)
        {
            node* nr = pop(st);
            node* nl = pop(st);

            n->left = nl;
            n->right = nr;

            push(st, n);
        }

        tokens = tokens->next;
        i--;
    }



    return pop(st);
}
#pragma endregion


int main()
{
    const char* expression = "2 3 - 3 1 4 * + *";

    // строим дерево по токенам
    node* tree = get_tree(expression);

    // выводим дерево
    cout << "tree:" << endl;
    print_node(tree);
    cout << endl;

    // infix
    cout << endl << "infix: ";
    print_infix(tree);
    cout << endl;

    // postfix
    cout << endl << "postfix: ";
    print_postfix(tree);
    cout << endl;

    return 0;
}
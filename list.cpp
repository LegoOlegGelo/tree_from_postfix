#include "list.h"

using namespace std;

void add_to_list(list*& l, node* n)
{
    if (!l)
    {
        l = new list;
        l->x = n;
        return;
    }

    list* cur = l;
    
    while (cur->next)
        cur = cur->next;
    
    cur->next = new list;
    cur->next->x = n;
}

int get_list_len(list* l)
{
    if (!l) return 0;

    int len = 0;

    do
    {
        len++;
        l = l->next;
    } while (l);
    
    return len;
}

node* list_get(list* l, int index)
{
    if (!l) return nullptr;

    while (index-- && l->next)
        l = l->next;
    
    return l->x;
}

void list_remove_at(list*& l, int index)
{
    if (!l) return;

    if (index == 0)
    {
        l = l->next;
        return;
    }

    while (--index && l->next)
        l = l->next;
    
    l->next = l->next->next;
}

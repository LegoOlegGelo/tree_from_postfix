#pragma once
#include "node.h"

struct list
{
    node* x;
    list* next;
};

void add_to_list(list*& l, node* n);
int get_list_len(list* l);
node* list_get(list* l, int index);
void list_remove_at(list*& l, int index);
#include "21s.h"

void dpush(t_node **head, char key) 
{ 
    t_node* new_node;
    new_node = (t_node*)malloc(sizeof(t_node));  
    new_node->key = key;  
    new_node->next = (*head);  
    new_node->prev = NULL;  
    if ((*head) != NULL)  
        (*head)->prev = new_node;  
    (*head) = new_node;  
}

void dprintlist(t_node *node, int direction)
{
    t_node *first;
    
    if (direction != 1 && direction != 0)
        return ;
    while (node != NULL)
    {
        if (direction == 1)
            ft_putchar(node->key);
        first = node;
        node = node->next;
    }
    if (direction == 0)
    {
        while (first != NULL)
        {
            ft_putchar(first->key);
            first = first->prev;
        }
    }
    // ft_putstr("\n");
}

void insert(t_node *prev_node, char key)  
{  
    t_node* new_node;

    if (prev_node == NULL) 
        return;
    new_node = (t_node*)malloc(sizeof(t_node));
    new_node->key = key;
    new_node->next = prev_node->next;
    prev_node->next = new_node;
    new_node->prev = prev_node;
    if (new_node->next != NULL)  
        new_node->next->prev = new_node;
      
}

void ddel(t_node  **head, t_node *del) 
{ 
    if (*head == NULL || del == NULL) 
        return;
    if (*head == del)
        *head = del->next;
    if (del->next != NULL)
        del->next->prev = del->prev;
    if (del->prev != NULL)
        del->prev->next = del->next;
    free(del);
    return;
}

void ddellist(t_node *head)
{
    while(head)
            ddel(&head, head);
}
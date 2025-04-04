#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) { 
  struct list_node* new_node = malloc(sizeof(struct list_node));
  new_node -> value = value;
  
  return new_node; 
}

void insert_at_head(struct linked_list *list, size_t value) {
  struct list_node* temp = new_node(value);
  temp -> next = list -> head;
  list -> head = temp;
}

void insert_at_tail(struct linked_list *list, size_t value) {
  //case with empty list;
  if(list -> head == NULL)
  {
    insert_at_head(list, value);
  }
  else
  {
    struct list_node* temp;
    temp = list -> head;
    while(temp -> next != NULL)
    {
      temp = temp -> next;
    }

    struct list_node* tail = new_node(value);
    temp -> next = tail;
    tail -> next = NULL;
  }

}

size_t remove_from_head(struct linked_list *list) { 
  struct list_node* toDelete = list -> head;
  size_t value = toDelete -> value;

  list -> head = list -> head -> next;
  free(toDelete);

  return value; 
}

size_t remove_from_tail(struct linked_list *list) { 
  size_t value;
  
  //case with one node
  if(list -> head -> next == NULL)
  {
    value = remove_from_head(list);
  }
  else
  {
    struct list_node* prev = list -> head;
    struct list_node* cur = prev -> next;
    while(cur -> next != NULL)
    {
      prev = prev -> next;
      cur = cur -> next;
    }
    value = cur -> value;
    prev -> next = NULL;
    free(cur);
  }

  return value; 
}

void free_list(struct linked_list list) {
  while(list.head != NULL)
  {
    struct list_node* toFree = list.head;
    list.head = list.head -> next;
    free(toFree);
  }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}

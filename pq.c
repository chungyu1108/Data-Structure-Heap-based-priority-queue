/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: chung-yu, yang
 * Email: yangchun@oregonstate.edu
 */

#include <stdlib.h>

#include "pq.h"
#include "dynarray.h"
#include "assert.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq 
{
  struct dynarray* heap;
  struct dynarray* heap_arr;
};

struct pq_poior
{
  int str;
  void* val;
};


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() 
{
  struct pq* poior = malloc(sizeof(struct pq));
  poior->heap = dynarray_create();
  poior->heap_arr = dynarray_create();
  return poior;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) 
{
  assert(pq);
  dynarray_free(pq->heap);
  dynarray_free(pq->heap_arr);
  free(pq);
  return;
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
  if(dynarray_size(pq->heap) == 0)
  {
    return 1;
  }
    else 
  return 0;
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void swap(struct pq* pq, int lower, int upper)
{
  void* swp_n = dynarray_get(pq->heap_arr, lower);
  void* swp_v = dynarray_get(pq->heap,lower);

  dynarray_set(pq->heap_arr,lower,dynarray_get(pq->heap_arr, upper));
  dynarray_set(pq->heap,lower ,dynarray_get(pq->heap, upper));

  dynarray_set(pq->heap_arr, upper, swp_n);
  dynarray_set(pq->heap, upper, swp_v);
}

void pq_insert(struct pq* pq, void* value, int priority) 
{
  int *new_pq = malloc(sizeof(int));
  *new_pq = priority;
  void* pq_val = value;
  dynarray_insert(pq->heap, pq_val);
  dynarray_insert(pq->heap_arr, new_pq);

  if(dynarray_size(pq->heap) == 0)
    return;

  int parent_node = (dynarray_size(pq->heap_arr)-2)/2;
  int child_node = dynarray_size(pq->heap)-1;
  int parent = *(int *)dynarray_get(pq->heap_arr, parent_node);
  int child = *(int *)dynarray_get(pq->heap, child_node);
  while(1)
  {
    if(parent <= child || child == 0)
    {
      return;
    }
    else
    {
      swap(pq, child_node, parent_node);
      parent_node = (parent_node-1)/2;
      child_node = (parent_node-1)/2;
    }  
    return;
  }
return;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
  return dynarray_get(pq->heap, 0);
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
  return *(int *)dynarray_get(pq->heap_arr, 0);
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */


int right_child(int x)
{
  return 2* x+2;
}
int left_child(int y)
{
  return 2* y+1;
}


void* pq_remove_first(struct pq* pq) 
{
  assert(pq);
  void* remove = dynarray_get(pq->heap, 0);
  free(dynarray_get(pq->heap_arr, 0));
  dynarray_remove(pq->heap, 0);
  dynarray_remove(pq->heap_arr, 0);
  return remove;
  
  int remove_parent = *(int *)dynarray_get(pq->heap_arr,0);
  void *remove_child = dynarray_get(pq->heap,0);
  remove_parent= *(int *)dynarray_get(pq->heap_arr,0);
  remove_child = dynarray_get(pq->heap,0);
  
  int node_l = *(int *)dynarray_get(pq->heap_arr,1);
  int node_r = * (int *)dynarray_get(pq->heap_arr,2);
  void * val_l = dynarray_get(pq->heap, 1);
  void * val_r = dynarray_get(pq->heap,2);


  int replace = 0;
  int curr = 0;

  int tem_l = left_child(curr);
  int tem_r = right_child(curr);

  while(1) 
  {
    if(val_l == NULL && val_r == NULL)
      break;
    if(val_l != NULL && val_r == NULL)
    {
      if(remove_parent < node_l)
        break;
      //replace = tem_l;
    }
    else if(val_l == NULL && val_r != NULL)
    {
      if(remove_parent < node_r)
        break;
      //replace = tem_r;
    }
    else if(val_l != NULL && val_r != NULL)
    {
      if(remove_parent < node_l && remove_parent < node_r)
        break;
      if(node_l > node_r)
      {
        swap(pq, replace, curr);

        replace = curr;
        tem_l = left_child(curr);
      }
      else
      {
        swap(pq, replace, curr);

        replace = curr;
        tem_l = left_child(curr);
      }
    }
  }
  
  return remove;
}

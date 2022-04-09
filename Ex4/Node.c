
#include <string.h>
#include <stdlib.h>
#include "Node.h"

/**
 * Allocates dynamically new Node element.
 * @param elem_copy_func func which copies the element stored in the Node (returns
 * dynamically allocated copy).
 * @param elem_cmp_func func which is used to compare elements stored in the Node.
 * @param elem_free_func func which frees elements stored in the Node.
 * @return pointer to dynamically allocated Node.
 * @if_fail return NULL.
 */
Node *node_alloc (NodeElemCpy elem_copy_func, NodeElemCmp elem_cmp_func, NodeElemFree elem_free_func)
{
  if (!elem_cmp_func || !elem_copy_func || !elem_free_func)
  {
    return NULL;
  }
  Node *node = calloc (1, sizeof (Node));
  if (!node) return NULL;
  node->elem_copy_func = elem_copy_func;
  node->elem_cmp_func = elem_cmp_func;
  node->elem_free_func = elem_free_func;
  return node;

}

/**
 * Frees a Node and the elements the Node itself allocated.
 * @param p_node pointer to dynamically allocated pointer to Node.
 */
void node_free (Node **p_node)
{
  if (!p_node || !(*p_node) || !(*p_node)->elem_free_func)
  {
    return;
  }
  clear_node (*p_node);
  (*p_node)->data = NULL;
  free (*p_node);
  (*p_node) = NULL;
}

/**
 * Gets a value and checks if the value is in the Node.
 * @param node a pointer to Node.
 * @param value the value to look for.
 * @return 1 if the value is in the Node, 0 otherwise.
 * Returns -1 if no such value in the Node
 *            or if something went wrong during the check
 * You cannot assume anything about the input.
 */
int check_node (Node *node, void *value)
{
  if (!node || !value || !node->elem_cmp_func)
  {
    return -1;
  }
  if (node->data != NULL && node->elem_cmp_func (node->data, value))
  {
    return 1;
  }
  return 0;

}

/**
 * Adds a new value to the data of the Node.
 * @param node a pointer to Node.
 * @param value the value to be added to the Node.
 * @return 1 if the adding has been done successfully, 0 otherwise.
 */
int set_node_data (Node *node, void *value)
{
  if (!node || !value || !node->elem_copy_func || !node->elem_free_func)
  {
    return 0;
  }
  if (node->data){
    clear_node (node);
  }
  node->data = node->elem_copy_func? node->elem_copy_func (value) : NULL;
  return 1;
}
/**
 * Deletes the data in the Node.
 * @param node Node a pointer to Node.
 */
void clear_node (Node *node)
{
  if (!node)
  {
    return;
  }
  if (node->elem_free_func && node->data) node->elem_free_func (&(node->data));
  node->data = NULL;
}

/**
 * Gets the number of data values in the hashtable that would have been hashed
 * to this node
 * @param node The current node
 * @return the number of data in the hashtable that would have been hashed
 * to this node or -1 in case of illegal input;
 * You cannot assume anything about the input.
 */
int get_hash_count (Node *node)
{
  if (!node)
  {
    return -1;
  }
  return node->hashCount;
}


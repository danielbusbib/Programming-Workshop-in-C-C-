#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "HashSet.h"
/**
 * function that initialize and allocate memory for
 * all nodes in Nodes list of the hash set
 * @param hash_set Hash set
 * @param nodes
 * @param size
 */
void init_nodes (HashSet *hash_set, Node **nodes, size_t size)
{
  for (size_t i = 0; i < size; ++i)
  {
    nodes[i] = node_alloc (hash_set->value_cpy, hash_set->value_cmp, hash_set->value_free);
  }
}
/**
 * helper function -> clear all nodes
 * in hash set
 * @param hash_set Hash set
 */
void hash_set_clear_helper (HashSet *hash_set)
{
  for (size_t i = 0; i < (hash_set)->capacity; ++i)
  {
    clear_node (hash_set->NodesList[i]);

    if (hash_set->NodesList[i]) hash_set->NodesList[i]->hashCount = 0;
  }
}
/**
 * Allocates dynamically new hash set element.
 * @param hash_func a function which "hashes" keys.
 * @param value_cpy a function which copies Values.
 * @param value_cmp a function which compares Values.
 * @param value_free a function which frees Values.
 * @return pointer to dynamically allocated HashSet.
 * @if_fail return NULL.
 */
HashSet *hash_set_alloc (
    HashFunc hash_func, HashSetValueCpy value_cpy,
    HashSetValueCmp value_cmp, HashSetValueFree value_free)
    {
  if (!hash_func || !value_free || !value_cmp || !value_cpy) return NULL;
  HashSet *hash_set = calloc (1, sizeof (HashSet));
  if (!hash_set) return NULL;
  hash_set->NodesList = calloc (HASH_SET_INITIAL_CAP, sizeof (Node *));
  init_nodes (hash_set, hash_set->NodesList, HASH_SET_INITIAL_CAP);
  hash_set->capacity = HASH_SET_INITIAL_CAP;
  hash_set->size = 0;
  hash_set->hash_func = hash_func;
  hash_set->value_cpy = value_cpy;
  hash_set->value_cmp = value_cmp;
  hash_set->value_free = value_free;
  return hash_set;
}
/**
 * re hash function -> do hashing to new Nodes list size of hash set
 * nodes list
 * @param tmp
 * @param hash_set
 * @param new_capacity
 */
void re_hash_function (Node **tmp, HashSet *hash_set, size_t new_capacity)
{
  for (size_t i = 0; i < hash_set->capacity; ++i)
  {
    if (hash_set->NodesList[i] && hash_set->NodesList[i]->data)
    {
      Value value = hash_set->NodesList[i]->data;
      size_t hash = hash_set->hash_func (value) & (new_capacity - 1);
      size_t ind = hash;
      size_t y = 1;
      while (y < new_capacity
      && tmp[ind] && tmp[ind]->data)
      {
        ind = hash + ((y + (y * y)) / 2) % new_capacity;
        y++;
      }
      set_node_data (tmp[ind], value);
    }
  }
}
/**
 * helper function --> free all nodes in NodesList
 * and free list.
 * @param list Nodes list
 * @param size size of list
 */
void clear_nodes_list(Node*** list, size_t size){
  Node ** nodes_list = *(list);
  for (size_t i=0;i<size;i++){
    clear_node (nodes_list[i]);
    free(nodes_list[i]);
    nodes_list[i] = NULL;
  }
  free(nodes_list);
  nodes_list = NULL;
}
/**
 * This function check the load factor after erase
 * of the hash set, and resize the hash set if
 * load factor is below Max load factor
 * @param hash_set HashSet
 * @return -1 if not below, o if success resize else 0
 */
int check_size_erase (HashSet *hash_set)
{
  size_t new_size = 0;
  double load_factor = hash_set_get_load_factor (hash_set);
  if (load_factor <= HASH_SET_MIN_LOAD_FACTOR)
  {
    new_size = hash_set->capacity / HASH_SET_GROWTH_FACTOR;
  }
  else
  {
    return -1;
  }
  if (new_size < 1) new_size = 1;
  Node **tmp = calloc (new_size, sizeof (Node *));
  if (!tmp)
  {
    return 0;
  }
  init_nodes (hash_set, tmp, new_size);
  re_hash_function (tmp, hash_set, new_size);
  if (hash_set && hash_set->NodesList) hash_set_clear_helper(hash_set);
  if (hash_set->NodesList) clear_nodes_list(&hash_set->NodesList, hash_set->capacity);
  hash_set->NodesList = tmp;
  hash_set->capacity = new_size;
  return 1;
}
/**
 * This function check the load factor after insert
 * to the hash set, and resize the hash set if
 * load factor is above Max load factor
 * @param hash_set HashSet
 * @return -1 if not above, o if success resize else 0
 */
int check_size_insert (HashSet *hash_set)
{
  size_t new_size = 0;
  double load_factor = hash_set_get_load_factor (hash_set);
  if (load_factor >= HASH_SET_MAX_LOAD_FACTOR)
  {
    new_size = hash_set->capacity * HASH_SET_GROWTH_FACTOR;
  }
  else
  {
    return -1;
  }
  if (new_size < 1) new_size = 1;
  Node **tmp = calloc (new_size, sizeof (Node *));
  if (!tmp) return 0;
  init_nodes (hash_set, tmp, new_size);

  re_hash_function (tmp, hash_set, new_size);
  if (hash_set) hash_set_clear_helper(hash_set);
  if (hash_set->NodesList) clear_nodes_list(&hash_set->NodesList, hash_set->capacity);
  hash_set->NodesList = tmp;
  hash_set->capacity = new_size;
  return 1;
}
/**
* Frees the hash set and all its elements.
* @param p_hash_set pointer to pointer to a hash_set.
*/
void hash_set_free (HashSet **p_hash_set)
{
  if (!p_hash_set || !(*(p_hash_set)))
  {
    return;
  }
  for (size_t i = 0; i < (*p_hash_set)->capacity; ++i)
  {
    node_free (&((*p_hash_set)->NodesList[i]));
    free ((*p_hash_set)->NodesList[i]);
  }
  free ((*p_hash_set)->NodesList);
  (*p_hash_set)->NodesList = NULL;
  free ((*p_hash_set));
  (*p_hash_set) = NULL;
}

/**
 *
 * Inserts a new Value to the hash set.
 * The function inserts *new*, *copied*, *dynamically allocated* Value,
 * NOT the Value it receives as a parameter.
 * @param hash_set the hash set where we want to insert the new element
 * @param value a Value we would like to add to the hashset
 * @return returns 1 for successful insertion, 0 otherwise.
 */
int hash_set_insert (HashSet *hash_set, Value value)
{
  if (!hash_set || !value || !hash_set->NodesList || !hash_set->hash_func
  || hash_set_contains_value (hash_set, value))
  {
    return 0;
  }
  size_t x = hash_set->hash_func (value) & (hash_set->capacity - 1), ind = 0, is_hashed_count = 0;
  if (hash_set->NodesList[x] && hash_set->NodesList[x]->data)
  {
    hash_set->NodesList[x]->hashCount++;
    ind = x;
    size_t i = 1;
    while (i < hash_set->capacity
    && hash_set->NodesList[ind] && hash_set->NodesList[ind]->data)
    {
      ind = (x + ((i + (i * i)) / 2)) % hash_set->capacity;
      i++;
    }
  }
  else
  {
    is_hashed_count = 1;
    ind = x;
  }
  if (!(hash_set->NodesList[ind]))
  {
    hash_set->NodesList[ind] = node_alloc (
        hash_set->value_cpy, hash_set->value_cmp, hash_set->value_free);
    if (!hash_set->NodesList[ind]) return 0;
  }
  set_node_data (hash_set->NodesList[ind], value);
  if (is_hashed_count) hash_set->NodesList[ind]->hashCount++;
  if (!check_size_insert (hash_set)) return 0;
  if (hash_set->size < hash_set->capacity) hash_set->size++;
  return 1;
}

/**
 * The function checks if the given value exists in the hash set.
 * @param hash_set a hash set.
 * @param value the value to be checked.
 * @return 1 if the value is in the hash set, 0 otherwise.
 */
int hash_set_contains_value (HashSet *hash_set, Value value)
{
  if (!hash_set || !(hash_set->NodesList) || !value)
  {
    return 0;
  }
  for (size_t i = 0; i < hash_set->capacity; ++i)
  {
    if (!(hash_set->NodesList[i]))
    {
      continue;
    }
    if (hash_set->NodesList[i]->data != NULL &&
    hash_set->NodesList[i]->elem_cmp_func (hash_set->NodesList[i]->data, value))
    {
      return 1;
    }
  }
  return 0;
}

/**
 * The function erases a Value.
 * @param hash_set a hash set.
 * @param value the value to be erased from the hashtable
 * @return 1 if the erasing was done successfully, 0 otherwise.
 */
int hash_set_erase (HashSet *hash_set, Value value)
{
  if (!hash_set || !value || !(hash_set_contains_value (hash_set, value)))
  {
    return 0;
  }
  size_t x = hash_set->hash_func (value) & (hash_set->capacity - 1);
  if (hash_set->NodesList[x]) hash_set->NodesList[x]->hashCount--;
  for (size_t i = 0; i < hash_set->capacity; ++i)
  {
    if (check_node (hash_set->NodesList[i], value) == 1)
    {
      clear_node (hash_set->NodesList[i]);
      hash_set->NodesList[i]->hashCount--;
    }
  }
  hash_set->size--;
  if (!check_size_erase (hash_set)) return 0;
  return 1;
}

/**
 * This function returns the load factor of the hash set.
 * @param hash_set a hash set.
 * @return the hash set's load factor, -1 if the function failed.
 */
double hash_set_get_load_factor (HashSet *hash_set)
{
  if (!hash_set)
  {
    return -1;
  }
  return (double) hash_set->size / hash_set->capacity;
}

/**
 * This function deletes all the values in the hash set.
 * @param hash_set a hash set to be cleared.
 */
void hash_set_clear (HashSet *hash_set)
{
  if (!hash_set)
  {
    return;
  }
  hash_set_clear_helper (hash_set);
  hash_set->size = 0;
}

/**
 * This function gets the element in the hashset hashed to the indexed value
 * @param hash_set the hashset
 * @param value the index of the node in the hashtable that we would like to have its value
 * @return the element in the hashset hashed to the indexed value
 * NULL in case of an error or an empty node or an unexpected value
 */
Value hash_set_at (HashSet *hash_set, int value)
{
  if (!hash_set || !hash_set->NodesList || (size_t)value >= hash_set->capacity)
  {
    return NULL;
  }
  Node *p = hash_set->NodesList[value];
  if (!p || p->data == NULL)
  {
    return NULL;
  }
  return p->data;
}
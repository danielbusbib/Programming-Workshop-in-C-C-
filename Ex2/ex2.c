#include "ex2.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 *This function put node int list head && tail if list is empty
 * @param list linkedlist
 * @param node Node
 * @return 1 if done the process, else 0
 */
int check_first_in_list (LinkedList *const list, Node *const node)
{
  if (!(list->head) && !(list->tail))
  {
    list->head = node;
    list->tail = node;
    return ONE;
  }
  return ZERO;
}
/**
 * This function check if list is NULL or node is NULL,
 * and print error information according the case.
 * @param list  linkedlist
 * @param node  Node
 * @return 1 if one of them is NULL, else 0
 */
int check_list_node (LinkedList *const list, Node *const node)
{
  if (list == NULL)
  {
    fprintf (stderr, LIST_NULL_MSG);
    return ONE;
  }
  if (node == NULL)
  {
    fprintf (stderr, NODE_NULL_MSG);
    return ONE;
  }
  return ZERO;
}
/**
 * Adds a node as the head of the list.
 *
 * Assumptions:
 *    You cannot assume the pointers are valid.
 *
 * In case of errors:
 *    Invalid pointer - print error to stderr and return from function.
 *
 * @param list pointer to list to add a node to.
 * @param node pointer to the node to add to the list.
 */
void add_to_start_linked_list (LinkedList *const list, Node *const node)
{
  // Write your code here
  if (check_list_node (list, node))
  {
    return;
  }
  if (check_first_in_list (list, node))
  {
    return;
  }
  Node *tmp = list->head;
  node->next = tmp;
  list->head = node;
  tmp->prev = node;

}
/**
 * remove helper -> update node after remove.
 * (assume node is in list)
 * @param node
 */
void remove_helper (Node *node)
{
  Node *p_tmp = node->prev;
  Node *n_tmp = node->next;
  node->next = NULL;
  node->prev = NULL;
  free (node->data);
  if (p_tmp)
  {
    p_tmp->next = n_tmp;
  }
  if (n_tmp)
  {
    n_tmp->prev = p_tmp;
  }
  free (node);
  node = NULL;
}

/**
 * Adds a node as the tail of the list.
 *
 * Assumptions:
 *   You cannot assume the pointers are valid.
 *
 * In case of errors:
 *    Invalid pointer - print error to stderr and return from function.
 *
 * @param list pointer to list to add a node to.
 * @param node pointer to the node to add to the list.
 */
void add_to_end_linked_list (LinkedList *const list, Node *const node)
{
  // Write your code here
  if (check_list_node (list, node))
  {
    return;
  }
  if (check_first_in_list (list, node))
  {
    return;
  }
  Node *tmp = list->tail;
  tmp->next = node;
  list->tail = node;
  node->prev = tmp;
}

/**
 * removes a node from the list and frees it's resources.
 *
 * Assumptions:
 *    You cannot assume the pointers are valid.
 *    You cannot assume the node is in the list. In this case don't free its resources.
 *    To be sure - you are supposed to compare the given node to the nodes in the list using == operator.
 *
 * In case of errors:
 *    Invalid pointer - print informative error message to stderr and return from function.
 *
 * @param list pointer to list to remove a node from.
 * @param node pointer to the node to remove from the list.
 */
void remove_node (LinkedList *const list, Node *const node)
{
  // Write your code here
  if (check_list_node (list, node))
  {
    return;
  }
  Node *tmp = list->head, *next = NULL;
  while (tmp)
  {
    next = tmp->next;
    if (tmp == node)
    {
      //remove
      if (list->head == tmp)
      {
        list->head = list->head->next;
      }
      if (list->tail == tmp)
      {
        list->tail = list->tail->prev;
      }
      remove_helper (node);
    }
    tmp = next;
  }
}

/**
 * Frees the resources (all dynamic allocations) of the given list.
 *
 * Assumptions:
 *    You cannot assume the pointer is valid.
 *
 * In case of errors:
 *    Invalid pointer - This means there is nothing to free, just return from function.
 *
 * @param list the list to free.
 */
void free_linked_list (LinkedList *const list)
{
  // Write your code here
  if (!list)
  {
    return;
  }
  Node *tmp = list->head;
  while (tmp)
  {
    free (tmp->data);
    Node *a = tmp->next;
    free (tmp);
    tmp = NULL;
    tmp = a;
  }
  free(list);
}
/**
 * THis function calculate the average of the Node data.
 * @param node Node
 * @return avg of node->data
 */
double avg (Node *const node)
{
  double sum = ZERO;
  for (size_t i = 0; i < node->len; ++i)
  {
    sum += (node->data)[i];
  }
  return sum / node->len;
}
/**
 * This function create a safe realloc of pointer p.
 * @param p pointer
 * @param size size_t
 * @return pointer after realloc.
 */
void *safe_realloc (void *p, size_t size)
{
  void *tmp = realloc (p, size);
  if (!tmp)
  {
    free (p);
    return NULL;
  }
  return tmp;
}
/**
 * This function add to the linkedlist a Node in
 * the start/end of list
 * @param list Linkedlist
 * @param node Node
 * @param dest destination 's'/'e'
 */
void add_to_list (LinkedList *const list, Node *const node, char dest)
{
  if (dest == START_SYMBOL)
  {
    //add to start of list
    add_to_start_linked_list (list, node);
  }
  else
  {
    //add to end of list
    add_to_end_linked_list (list, node);
  }
}
/**
 * This function check if pointer num_elements_in_returned_array
 * is valid. and update his value if yes. else print error
 * and free averages.
 * @param averages
 * @param num_elements_in_returned_array
 * @param i
 * @return 0 if not valid pointer, else 1.
 */
int check_size_pointers(double * averages, size_t * num_elements_in_returned_array, size_t i)
{
  if (!num_elements_in_returned_array)
  {
    fprintf (stderr, INVALID_NUM_POINTER);
    if  (averages){
      free(averages);
      averages = NULL;
    }
    return ZERO; //FALSE
  }
  *num_elements_in_returned_array = (size_t) i - 1;
  return ONE;
}
/**
 * calculates the grade average of every node in the linked list.
 *
 * Assumptions:
 *    You cannot assume the pointers are valid.
 *    You don't know the number of nodes in the linkedlist in advance.
 *    You can assume that there is at least one node with data != NULL (i.e. len > 0).
 *    You can assume that for each node 'len' is indeed the length of 'data'
 *     (in particular len=0 <=> data=NULL).
 *
 * In case of errors:
 *    Invalid pointer - print informative message to stderr, free resources allocated by function,
 *                      return NULL from function.
 *    Allocation fail - print informative message to stderr, free resources allocated by function,
 *                      return NULL from function.
 *    Node with NULL data - don't count the node in the calculation.
 *
 * @param list: LinkedList pointer to linked list from whom to calculate grade averages.
 * @param num_elements_in_returned_array: pointer to unsigned long, that should contain the number of nodes in the list
 * (for nodes with data != NULL) when the function finishes execution. To be clear - at the start of the function,
 * (*num_elements_in_returned_array) is a garbage value, and this function should set its value.
 *    @Note: Nodes with NULL data should not be count in the calculation.
 *    Therefore *num_elements_in_returned_array <= numOfNodes.
 * @return array of grade averages per node. To be clear - this means you should
 * calculate the grade average of every node and save it into an array, which you will return from the function.
 */
double *get_averages (LinkedList * list, size_t * num_elements_in_returned_array)
{
  if (!list)
  {
    fprintf (stderr, LIST_NULL_MSG);
    return NULL;
  }
  Node *tmp = list->head;
  size_t i = 1;
  double *averages = NULL;
  while (tmp)
  {
    if (!(tmp->data))
    {
      tmp = tmp->next;
      continue;
    }
    double *tmp_avgs = safe_realloc (averages, i * sizeof (double));
    if (!tmp_avgs)
    {
      averages = NULL;
      fprintf (stderr, ALLOCATION_FAILE_MSG);
      return NULL;
    }
    averages = tmp_avgs;
    averages[i - 1] = avg (tmp);
    tmp = tmp->next;
    i++;
  }
  if (!check_size_pointers (averages, num_elements_in_returned_array, i))
  {
      return NULL;
  }
  return averages;  // Write your code here
}
/**
 * This function return int arrays of
 * data in file text.
 * @param token string
 * @param s size of data
 * @return pointer to data
 */
int* get_data(char *token, size_t *s){
  int *data = NULL;
  *s = 1;
  while ((token = strtok (NULL, DELIMITERS)))
  {
    if (strcmp (token, END_LINE_SYMB_1) == ZERO || strcmp (token, END_LINE_SYMB_2) == ZERO)
    {
      break;
    }
    int *tmp = safe_realloc (data, (*s) * sizeof (*tmp));
    if (!tmp)
    {
      data = NULL;
      fprintf (stderr, ALLOCATION_FAILE_MSG);
      *s = ZERO;
      return NULL;
    }
    data = tmp;
    data[(*s) - 1] = (int) strtol (token, NULL, TEN);
    (*s)++;
  }
  return data;
}

/**
 * opens a file from a given filename and parses it's contents into a LinkedList.
 *
 * Assumptions:
 *    You cannot assume the filename is OK (meaning - you cannot assume it is a valid path to a file).
 *    You cannot assume anything on the number of ints in a row of the file, just that it is >= 1.
 *    You can assume that if the file opened, then it is exactly in the format specified in the exercise PDF.
 *    You can assume max line length of 1024.
 *
 * In case of errors:
 *    Invalid pointer - print informative message to stderr, free resources allocated by function,
 *                      return NULL from function.
 *    File open fail - print informative message to stderr, free resources allocated by function,
 *                      return NULL from function.
 *    Allocation fail - print informative message to stderr, free resources allocated by function,
 *                      return NULL from function.
 *
 * Think - in what mode should we open this file? (read? write? append?)
 *
 * @param file filename of input file that needs to be parsed.
 * @return pointer to LinkedList instance, whose nodes and data arrays were parsed from the given file.
 */
LinkedList *parse_linked_list (const char *const filename)
{
  FILE *file = fopen (filename, FILE_OPEN_MODE);
  if (file == NULL)
  {
    fprintf (stderr, FILE_NOT_FOUND_ERR);
    return NULL;
  }
  LinkedList *list = calloc (1, sizeof (LinkedList));
  if (!list){
    fprintf (stderr, ALLOCATION_FAILE_MSG);
    return NULL;
  }
  size_t s = ZERO;
  char buffer[BUFFER_SIZE] = {0}, *token = NULL;
  while (fgets (buffer, BUFFER_SIZE, file) != NULL)
  {
    token = strtok (buffer, DELIMITERS); // set the string to parse, read first token
    char e = token[0];     // continue reading the last string put into strtok
    s = 1;
    int *data = get_data (token, &s);
    if (!data && s == ZERO)
    {
        return NULL;
    }
    Node *node = calloc (1, sizeof (Node));
    node->data = data;
    node->len = s - 1;
    add_to_list (list, node, e);
  }
  fclose(file);
  return list;  // Write your code here
}
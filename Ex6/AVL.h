
#ifndef _AVL_H_
#define _AVL_H_
#include <vector>
#include <cmath>
#include "Apartment.h"
enum RotationType {
    RR, LL, RL, LR, NONE
};
class AVL {
 public:
  /**
   * To manage the tree nodes, we use a nested struct. This struct contains the
   * apartment corresponding to the node, the left son and the right son of the
   * node, both of them node type themselves.
   */
  struct node {
      /**
       * Constructor - It can be expanded
       * @param data the corresponding apartment object
       * @param left child
       * @param right child
       */
      node (Apartment data, node *left, node *right, int height)
      : data_ (data), left_ (left), right_ (right), height_ (height)
      {}
      node (Apartment data)
      : data_ (data), left_ (), right_ (), height_ (0)
      {}
      /**
       *
       * @return the left child of this node
       */
      node *get_left () const
      {
        return left_;
      }
      /**
       *
       * @return the right child of this node
       */
      node *get_right () const
      {
        return right_;
      }
      /**
     *
     * @return the const reference apartment of this node
     */
      const Apartment &get_data () const
      {
        return data_;
      }

      Apartment data_;
      node *left_, *right_;
      int height_;

  };
  /**
   * Constructor. Constructs an empty AVL tree
   */
  AVL ();
  /**
   * Copy constructor
   * @param other
   */
  AVL (const AVL &other);
  /**
   * Destructor
   */
  ~AVL ();
  /**
   * operator =
   * @param other AVL
   * @return  AVL
   */
  AVL &operator= (const AVL &other);
  /**
   * A constructor that receives a vector of a pairs. Each such pair is an
   * apartment that will inserted to the tree. Insert can be used to insert the
   * apartments a vector of a pairs
   * @param coordinates
   */
  AVL (const std::vector<std::pair<double, double>> &coordinates);
  /**
   *
   * @return the root node of this tree
   */
  node *get_root () const
  {
    return root_;
  }
  /**
   * The function inserts the new apartment into the tree so that it maintains
   * the legality of the tree.
   * @param apartment
   */
  void insert (const Apartment &apartment);
  /**
   * The function deletes the apartment from the
   * tree (if it is in that tree) so that it maintains
   * the legality of the tree.
   * @param apartment
   */
  void erase (const Apartment &apartment);
  /**
   * The class should support forward iterator. Don't forget to define the
   * iterator traits and all the actions required to support a forward iterator
   * The iterator will move in preorder.
   */
  class Iterator {
    std::vector<node *> vec{};
    friend class ConstIterator;
   public:
    typedef Apartment value_type;
    typedef Apartment &reference;
    typedef Apartment *pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;
    Iterator (node *node)
    {
      add_to_vec (node);
    }
    void add_to_vec (node *node)
    {
      if (!node) return;
      vec.push_back (node);
      add_to_vec (node->left_);
      add_to_vec (node->right_);
    }
    pointer operator-> ()
    {
      return &vec[0]->data_;
    }
    reference operator* ()
    {
      return vec[0]->data_;
    }
    Iterator &operator++ ()
    {
      vec.erase (vec.begin ());
      return *this;
    }
    Iterator operator++ (int)
    {
      iterator it = *this;
      vec.erase (vec.begin ());
      return it;
    }
    bool operator== (const Iterator &rhs) const
    {
      if (vec.empty () || rhs.vec.empty ()) return vec.empty () && rhs.vec.empty ();
      return vec[0] == rhs.vec[0];
    }
    bool operator!= (const Iterator &rhs) const
    {
      return !(rhs == *this);
    }
  };
  class ConstIterator {
    std::vector<node *> vec{};
   public:
    typedef const Apartment value_type;
    typedef const Apartment &reference;
    typedef const Apartment *pointer;
    typedef const std::forward_iterator_tag iterator_category;
    typedef const std::ptrdiff_t difference_type;
    ConstIterator (node *node)
    {
      add_to_vec (node);
    }
    void add_to_vec (node *node)
    {
      if (!node) return;
      vec.push_back (node);
      add_to_vec (node->left_);
      add_to_vec (node->right_);
    }
    pointer operator-> () const
    {
      return &vec[0]->data_;
    }
    reference operator* () const
    {
      return vec[0]->data_;
    }
    ConstIterator &operator++ ()
    {
      vec.erase (vec.begin ());
      return *this;
    }
    ConstIterator operator++ (int)
    {
      ConstIterator it = *this;
      vec.erase (vec.begin ());
      return it;
    }
    bool operator== (const ConstIterator &rhs) const
    {
      if (vec.empty () || rhs.vec.empty ()) return vec.empty () && rhs.vec.empty ();
      return vec[0] == rhs.vec[0];
    }
    bool operator!= (const ConstIterator &rhs) const
    {
      return !(rhs == *this);
    }
  };
  using iterator = Iterator; // same as typedef Iterator iterator;
  using const_iterator = ConstIterator;
  iterator begin ();
  const_iterator begin () const;
  const_iterator cbegin () const;
  iterator end ();
  const_iterator end () const;
  const_iterator cend () const;
  /**
   * The function returns an iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   * @param data apartment to search
   * @return iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   */
  iterator find (const Apartment &data);
  /**
   * The function returns an iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   * @param data apartment to search
   * @return iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   */
  const_iterator find (const Apartment &data) const;
  /**
   * Insertion operator, prints the apartment in the tree in preorder traversal.
   * Each apartmnet will be printed in the format: (x,y)\n
   * @param os reference to std::ostream
   * @param avl tree
   * @return os reference to std::ostream
   */
  friend std::ostream &operator<< (std::ostream &os, const AVL &avl);
 private:
  node *root_;
  static void delete_nodes (AVL::node *node);
  friend RotationType get_rotation_type
  (AVL::node *node, const Apartment &apartment);
  friend RotationType get_rotation_type (AVL::node *node);
  friend node *do_rotation (RotationType rt, node *node);
  friend node *right_rotation (node *node);
  friend node *left_rotation (node *node);
  friend void preorder_output (std::ostream &os, node *node);
  node *find_node (node *node, const Apartment &a) const;
  friend node *insertnode (node *node, const Apartment &apartment);
  friend node *delete_node (node *node, const Apartment &apartment);
  friend void add_nodes (node *original_node, node *new_node);
};

#endif //_AVL_H_

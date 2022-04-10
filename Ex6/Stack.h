//
// Created by rotem on 07/10/2021.
//

#ifndef _STACK_H_
#define _STACK_H_
#include "Apartment.h"
#include <utility>
#include <vector>
//typedef std::vector<Apartment> vector;
class Stack {
  std::vector<Apartment> vector{};

  class iterator;
  friend class iterator;
  class iterator {
    std::vector<Apartment> vec{};
    friend class ConstIterator;
   public:
    typedef Apartment value_type;
    typedef Apartment &reference;
    typedef Apartment *pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;
    iterator (const std::vector<Apartment> &vec_a)
    {
      for (const auto &v: vec_a)
      {
        vec.push_back (v);
      }
    }

    pointer operator-> ()
    {
      return &vec[vec.size () - 1];
    }
    reference operator* ()
    {
      return vec[vec.size () - 1];
    }
    iterator &operator++ ()
    {
      vec.pop_back ();
      return *this;
    }
    iterator operator++ (int)
    {
      iterator it = *this;
      vec.pop_back ();
      return it;
    }
    bool operator== (const iterator &rhs) const
    {
      if (vec.empty () || rhs.vec.empty ()) return vec.empty() &&
      rhs.vec.empty();
      return vec[vec.size () - 1] == rhs.vec[rhs.vec.size () - 1];
    }
    bool operator!= (const iterator &rhs) const
    {
      return !(rhs == *this);
    }
  };
  class ConstIterator {
    std::vector<Apartment> vec{};
   public:
    typedef const Apartment value_type;
    typedef const Apartment &reference;
    typedef const Apartment *pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;
    ConstIterator(const std::vector<Apartment> &vec_a)
    {
      for (const auto &v: vec_a)
      {
        vec.push_back (v);
      }
    }

    pointer operator-> () const
    {
      return &vec[vec.size () - 1];
    }
    reference operator* () const
    {
      return vec[vec.size () - 1];
    }
    ConstIterator &operator++ ()
    {
      vec.pop_back ();
      return *this;
    }
    ConstIterator operator++ (int)
    {
      ConstIterator it = *this;
      vec.pop_back ();
      return it;
    }
    bool operator== (const ConstIterator &rhs) const
    {
      if (vec.empty () || rhs.vec.empty ()) return vec.empty()
      && rhs.vec.empty();
      return vec[vec.size () - 1] == rhs.vec[rhs.vec.size () - 1];
    }
    bool operator!= (const ConstIterator &rhs) const
    {
      return !(rhs == *this);
    }
  };
 public:
  /**
   * Default constructor, constructs an empty stack
   */
  Stack ();
  /**
   * Constructor that gets vector of pairs, and pushes them as apartments to the stack, when the first pair is pushed first.
   * @param coordinates vector of pairs
   */
  Stack (std::vector<std::pair<double, double>> coordinates);
  /**
   * Pushes an apartment to the top of the stack
   * @param apartment
   */
  void push (const Apartment &apartment);
  /**
   * A method that deletes the item from the top of the stack.
   * Calling this method with an empty stack will throw an out of range exception with an informative message of your choice.
   */
  void pop ();
  /**
  *A method that returns true if the stack is empty and otherwise false.
  */
  bool empty () const;
  /**
  *A method that returns how many items are inside the stack.
  */
  size_t size () const;
  /**
   * Method that return the item from the top of the stack, but do not remove it from it.
   * Calling this method with an empty stack will throw an out of range exception with an informative message of your choice.
   * @return refernce to the top most item
   */
  Apartment &top ();
  /**
   * Method that return the item from the top of the stack, but do not remove it from it.
   * Calling this method with an empty stack will throw an out of range exception with an informative message of your choice.
   * @return copy to the top most item
   */
  Apartment top () const;
  /**
   * The stack should support the iterator (at least a forward iterator) so that the item at the top of the stack is the first item.
   */
  typedef iterator iterator;
  typedef ConstIterator const_iterator;
  iterator begin ();
  const_iterator begin () const;
  const_iterator cbegin () const;
  iterator end ();
  const_iterator end () const;
  const_iterator cend () const;
};


#endif //_STACK_H_

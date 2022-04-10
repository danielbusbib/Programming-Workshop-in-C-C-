#include "Stack.h"
#define POP_EMPTY "ERROR: CAN NOT POP FROM EMPTY STACK"
#define TOP_EMPTY "ERROR: CAN NOT TOP FROM EMPTY STACK"

Stack::iterator Stack::begin ()
{
  return {vector};
}
Stack::const_iterator Stack::begin () const
{
  return {vector};
}
Stack::const_iterator Stack::cbegin () const
{
  return {vector};
}
Stack::iterator Stack::end ()
{
  return {std::vector<Apartment> ()};
}
Stack::const_iterator Stack::end () const
{
  return {std::vector<Apartment> ()};
}
Stack::const_iterator Stack::cend () const
{
  return {std::vector<Apartment> ()};
}
Stack::Stack ()
{}
Stack::Stack (std::vector<std::pair<double, double>> coordinates)
{
  for (auto &c: coordinates)
  {
    vector.push_back (Apartment
    (std::pair<double, double>{c.first, c.second}));
  }
}
void Stack::push (const Apartment &apartment)
{
  vector.push_back (apartment);
}
void Stack::pop ()
{
  if (vector.empty()) throw std::out_of_range(POP_EMPTY);
  vector.pop_back ();
}
bool Stack::empty () const
{
  return vector.empty ();
}

size_t Stack::size () const
{
  return vector.size ();
}

Apartment &Stack::top ()
{
  if (vector.empty()) throw std::out_of_range(TOP_EMPTY);
  return vector[vector.size () - 1];
}

Apartment Stack::top () const
{
  return vector[vector.size () - 1];
}


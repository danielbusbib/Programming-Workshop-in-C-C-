#include "Apartment.h"

Apartment::Apartment (const std::pair<double, double> &Coordinates)
 : _x (Coordinates.first), _y (Coordinates.second)
{}
double Apartment::get_x () const
{
  return _x;
}
double Apartment::get_y () const
{
  return _y;
}
bool Apartment::operator< (const Apartment &other) const
{
  return distance ((*this)) + EPSILON < distance (other);
}
bool Apartment::operator> (const Apartment &other) const
{
  return distance ((*this)) > distance (other) + EPSILON;
}

bool Apartment::operator== (const Apartment &other) const
{
  return std::abs (_x - other.get_x ()) <= EPSILON &&
  std::abs (_y - other.get_y ()) <= EPSILON;

}

double distance (const Apartment &a)
{
  return sqrt ((a._x - X_FEEL_BOX) * (a._x - X_FEEL_BOX) + (a._y - Y_FEEL_BOX) * (a._y - Y_FEEL_BOX));
}

std::ostream &operator<< (std::ostream &os, const Apartment &apartment)
{
  os << "(" << apartment.get_x () << "," << apartment.get_y () << ")" << std::endl;
  return os;
}

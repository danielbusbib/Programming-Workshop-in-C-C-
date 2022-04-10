//
// Created by rotem on 07/10/2021.
//

#ifndef _APARTMENT_H_
#define _APARTMENT_H_
#define X_FEEL_BOX 35.213506
#define Y_FEEL_BOX 31.772425
#define EPSILON 0.0001
#include <iostream>
#include <cmath>
class Apartment {
  /**
   * X and y coordinates of the apartment.
   */
  double _x, _y;
 public:
  /**
   * Constructor that get pair of points, and creates new apartment.
   * @param Coordinates std::pair, which the first is the x coordinate and the second is the y.
   */
  Apartment (const std::pair<double, double> &Coordinates);
  /**
   *
   * @return the x coordinate of the apartment
   */
  double get_x () const;
  /**
   *
   * @return the y coordinate of the apartment
   */
  double get_y () const;
  /**
   * Operator <, apartment is smaller than other if it closer to [31.772425, 35.213506]
   * @param other
   * @return true, if this apartment is smaller than the other one, false otherwise
   */
  bool operator< (const Apartment &other) const;
  /**
   * Operator >, apartment is greater than other if it farther from [31.772425, 35.213506]
   * @param other
   * @return true, if this apartment is greater than the other one, false otherwise
   */
  bool operator> (const Apartment &other) const;
  /**
   * Operator ==, Two apartments are identical if their x and
   * y values are the same, to the point of an epsilon = 0.0001
   * @param other
   * @return true if the two apartments are equal, false otherwise
   */
  bool operator== (const Apartment &other) const;
  /**
   * Insertion operator, prints the apartment in the format: (x,y)\n
   * @param os reference to std::ostream
   * @param apartment
   * @return os reference to std::ostream
   */
  friend std::ostream &operator<< (std::ostream &os, const Apartment &apartment);

 private:
  friend double distance (const Apartment &a);

};


#endif //_APARTMENT_H_


#include "MesureTimeHelper.h"
#include <iostream>
#include <vector>
#include <chrono>
#include "AVL.h"
#include "Stack.h"
#include "Find.h"
#include <unordered_set>
#define X_X 31.81428051893798
#define X_Y 35.18577781093502
void write_results (std::string file_name)
{
  std::ofstream result_file;
  result_file.open ("RESULT");
  Apartment x (std::pair<double, double> (X_X, X_Y));
  std::vector<std::pair<double, double>> vec = xy_from_file (file_name);

  auto t1 = std::chrono::high_resolution_clock::now ();
  Stack stack (vec);
  auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>
      (t1.time_since_epoch());
  result_file << "Stack = " << diff.count() << std::endl;

  t1 = std::chrono::high_resolution_clock::now ();
  AVL avl (vec);
  diff = std::chrono::duration_cast<std::chrono::nanoseconds> (t1.time_since_epoch());
  result_file << "AVL = " << diff.count() << std::endl;

  std::unordered_set<Apartment, MyHashFunction> set;
  t1 = std::chrono::high_resolution_clock::now ();
  for (auto &c: vec)
  {
    set.insert (c);
  }
  result_file << "Unsorted Set = " <<
  std::chrono::duration_cast<std::chrono::nanoseconds>
      (t1.time_since_epoch()).count () << std::endl;
  /*
   * find
   */
  t1 = std::chrono::high_resolution_clock::now ();
  find (stack.begin (), stack.end (), x);
  result_file << "Stack = " << std::chrono::duration_cast<
      std::chrono::nanoseconds> (t1.time_since_epoch()).count () << std::endl;

  t1 = std::chrono::high_resolution_clock::now ();
  find (avl.begin (), avl.end (), x);
  result_file << "AVL = " <<
  std::chrono::duration_cast<std::chrono::nanoseconds>
      (t1.time_since_epoch()).count () << std::endl;

  t1 = std::chrono::high_resolution_clock::now ();
  find (set.begin (), set.end (), x);
  result_file << "Unsorted Set = " <<
  std::chrono::duration_cast<std::chrono::nanoseconds>
      (t1.time_since_epoch()).count () << std::endl;

  /*
   * type find
   */
  t1 = std::chrono::high_resolution_clock::now ();
  avl.find (x);
  result_file << "AVL = " <<
  std::chrono::duration_cast<std::chrono::nanoseconds>
      (t1.time_since_epoch()).count () << std::endl;

  t1 = std::chrono::high_resolution_clock::now ();
  set.find (x);
  result_file << "Unsorted Set = " <<
  std::chrono::duration_cast<std::chrono::nanoseconds>
      (t1.time_since_epoch()).count () << std::endl;

  result_file.close ();
}


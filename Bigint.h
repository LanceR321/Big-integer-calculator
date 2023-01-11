// Lance Reyes (ID:5550001857)
#ifndef MESA_CISC187_BIGINT_H
#define MESA_CISC187_BIGINT_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>


class Bigint {
 
  private:
  std::vector<int> number; //vector holds number in reverse order


  public:
  
  // constructors  
  Bigint() = default;
  Bigint(std::string input);


  // Helper functions
  std::vector<int> add_vectors(std::vector<int> &vec1, std::vector<int> & vec2);
  std::vector<int> multiply_vectors(std::vector<int> &vec1, std::vector<int> &vec2); 
  std::vector<int> power_vectors(std::vector<int> &vec1, std::vector<int> &vec2);

  void clear();
  void size();
  void pop_back();
  void print_vector();
  void return_vector();
  bool vector_check(std::vector<int> &vec1, std::vector<int> &exponent_vec);
  bool zero_check(std::vector<int> &vector);

  // Operators
  Bigint operator + (Bigint other); 
  Bigint operator * (Bigint other);
  Bigint operator ^ (Bigint other);


};// end of Big int class

#endif

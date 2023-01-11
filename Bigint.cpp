// Lance Reyes (ID:5550001857)

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

#include "Bigint.h"

  // constructors  
Bigint::Bigint(std::string input) {   // string of numbers is reversed into a vector of int
  
    int size = input.length();
    --size;
    std::string temp;

    while(size != -1) {
      temp = input[size];
      int digit = std::stoi(temp);
      number.push_back(digit);
      --size;
      }
    } 




// Helper functions
std::vector<int> Bigint::add_vectors(std::vector<int> &vec1, std::vector<int> &vec2) { 
 
  std::vector<int> new_vec;
  int vec_sz1 = vec1.size();
  int vec_sz2 = vec2.size();  
  int max_ = 0;
  int temp_digit = 0;
  int carry = 0;

 if (vec_sz1 > vec_sz2) {
   max_ = vec_sz1;
   int temp_val = max_ - vec2.size();
      for ( int i = 0; i < temp_val; i++) { // pushes back zeros until it meets the size of other vector
             vec2.push_back(0);        
            }
    }

 else {
   max_ = vec_sz2;
   int temp_val2 = max_ - vec1.size();
    for ( int i = 0; i < temp_val2; i++) {   // pushes back zeros until it meets the size of other vector
      vec1.push_back(0);        
      }

  }

    for (int count = 0; count < max_ ; count++) {   
      
          temp_digit = vec1[count] + vec2[count] + carry; 
  
      if (temp_digit >= 10) {              
            temp_digit = temp_digit % 10;
            new_vec.push_back(temp_digit);
            carry = 1;
        }

        else{
            new_vec.push_back(temp_digit);
            carry = 0;
        }
          if (carry == 1 &&( count +1 == max_)){ // if carry has a number by the end of the count it will be pushed back
                new_vec.push_back(carry);
                carry =0;
                break;
            }       
          
    }// end of for loop

return new_vec;
}



std::vector<int> Bigint::multiply_vectors(std::vector<int> &vec1, std::vector<int> &vec2) { 

    int vec_sz1 = vec1.size();  
    int vec_sz2 = vec2.size();  
    int small = 0;
    int max_ = 0;
    int temp_digit = 0;
    int carry = 0; 
    int pad = 1;
      
   if (vec_sz1 > vec_sz2) {
       max_ = vec_sz1;
       small = vec_sz2;
      }

   else {
        max_ = vec_sz2;
        small = vec_sz1;
        }
      

   std::vector<int> product;   
   std::vector<int> temp_vec; 


    for (int count1 = 0; count1 < max_ ; count1++) {  
    
            if (count1 > 0) {

                     for (int i =0; i< pad; i++) { // pushes back appropriate number of zeros after every run
                       temp_vec.push_back(0);
                      }
                     
                  pad = pad +1;
                 }

            for (int count2 = 0; count2 < small ; count2++) { 
                    
                    if (max_ == vec_sz1) { // if else statement makes sure its being multiplied correctly
                    
                          if(count1 == 1){ 
                            temp_digit = (vec1[count1] * vec2[count2]) + carry;
                          }

                        temp_digit = (vec1[count1] * vec2[count2]) + carry;
                
                    }
                    else {        
                    temp_digit = (vec1[count2] * vec2[count1])  + carry;
                    }
   
                      if (temp_digit >= 10) {    // sets the carry and digit that is pushed back after % 10
                             carry = temp_digit/10;       
                             temp_digit = temp_digit % 10;
                             temp_vec.push_back(temp_digit);
                            }
                      
                      else{
                          temp_vec.push_back(temp_digit);   
                          carry =0;
                   }

           } // nested for loop

          if(carry != 0) {              // if carry is holding a value after running the for loop it is pushed back
            temp_vec.push_back(carry);
            }

          product = add_vectors(product, temp_vec); // temp_vec will keep adding to the product vector after every run
          temp_vec.clear();      
          carry =0;

    }// outer for loop


    bool all_zero = false;
    all_zero = zero_check(product); 

    if (all_zero == true) {   // makes sure if multiplied by a zero, only a single zero is returned
        product.clear();
        product.push_back(0);
        }

return product;
}


std::vector<int> Bigint::power_vectors(std::vector<int> &vec1, std::vector<int> &vec2) { 

  std::vector<int> power;  
  std::vector<int> adder;    // used to add 1 after every run in the while loop
  adder.push_back(1);
  std::vector<int> sum;    
  sum.push_back(0);

  std::vector<int> squared;
  squared.push_back(2);

  int count =0;
  int index = 0;
  int size = vec2.size();
  bool vec2_verify = false;

    if (vec2[index] == 0 && size == 1) { // if exponent is 0 the power is 1
      power.push_back(1);
      vec2_verify = true;
    }

    if(vec2[index] == 1 && size ==1) { // if exponent is 1 the power is itself
      power = vec1;
      vec2_verify = true;
    }

    if(vec2[index] == 2 && size ==1) { // if exponent is 2 the power is squared
    power = multiply_vectors(vec1, vec1);
    vec2_verify = true;
    }
    


    while (vec2_verify == false) {
          
      if (count == 0) {             // if statement only runs once to get the product of vec1

        power = multiply_vectors(vec1, vec1);
        count = count + 1;
        sum = add_vectors(sum, squared);       // adds 2 the sum
        vec2_verify= vector_check(sum,vec2);    

      }
             

      if (count > 0) {             
        power = multiply_vectors(power, vec1);                  
        sum = add_vectors(sum, adder);          // after every run +1 is added to the sum
        vec2_verify= vector_check(sum,vec2);    // checks if the sum is equal to the same number of the exponent
      }
    
    }// end of while loop

    
return power;
}




void Bigint::clear() {  // clears vector
    number.clear();
    } 


void Bigint::size() { // outputs size of vector

  std::cout << number.size();
  }

void Bigint::pop_back() {
      number.pop_back();
  }

void Bigint::print_vector() {    // prints vector in correct order

 int vec_size = number.size();
    --vec_size;
    while(vec_size != -1) {
      std::cout << number[vec_size];
     --vec_size;
    } 

  }

  void Bigint::return_vector() {  
  return print_vector();
  }


bool Bigint::vector_check(std::vector<int> &vec1, std::vector<int> &exponent_vec) { // checks if 2 vectors are equal
int size = exponent_vec.size();
int count = 0;

for (int i =0; i < size; i++) {

      if (vec1[i] == exponent_vec[i]) {
        count = count +1;
      }
}

    if ( count  == size) {
        return true;
      }

        else{
        return false;
        }

}



bool Bigint::zero_check(std::vector<int> &vector) { // checks if a vector contains only zeros

  int size = vector.size();
  int empty = 0;

  for (int i =0; i < size; i++) {

          if (vector[i] == 0) {
              empty = empty +1;    
            }
    }

    if ( empty  == size) {
           std::cout << "Vector2 is now empty and size is " << empty <<std::endl;
           return true;
          }

    else{
           return false;
          }
  }



// Operators
Bigint Bigint::operator + (Bigint other) {
    
      Bigint sum;
      sum.number = add_vectors(number, other.number);
      return (sum);
    } 


Bigint Bigint::operator * (Bigint other) {
  
    Bigint product;
    product.number = multiply_vectors(number,other.number);
    return (product);
    }


Bigint Bigint::operator ^ (Bigint other) {

  Bigint power;
  power.number = power_vectors(number, other.number);
  return (power);
  }




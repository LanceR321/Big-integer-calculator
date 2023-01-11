//Lance Reyes (ID:5550001857)
#include <cctype>
#include <cstring>
#include <iostream>
#include <stack>
#include <string>
#include <string.h>

#include "Bigint.h"
#include "function.h"



class Handler {

    public:

   virtual bool handler(std::stack<Bigint> &stack, std::string token) = 0;
   Handler()= default;

}; // end of handler class

class add: public Handler {

    bool handler(std::stack<Bigint> &stack, std::string token) {

          if (token == "+") {

             Bigint add1, add2, sum_;

             add2 = stack.top();
             stack.pop();
             add1 = stack.top();
             stack.pop();
             sum_ = add1 + add2;
             stack.push(sum_);
  
            return true;
            }

          else{
          return false;
          }     
      }

}; // end of add


class multiply: public Handler {

    bool handler(std::stack<Bigint> &stack, std::string token) {

        if (token == "*") {

          Bigint mult1, mult2, product_;

          mult2 = stack.top();
          stack.pop();
          mult1 = stack.top();
          stack.pop();
          product_ = mult1 * mult2;
          stack.push(product_); 
          return true;
        }

        else{
        return false;
        }

     }

};// end of mult

class power: public Handler {

    bool handler(std::stack<Bigint> &stack, std::string token) {
    if (token == "^") {

     Bigint pow1, pow2, power_;
     pow2 = stack.top();
     stack.pop();
     pow1 = stack.top();
     stack.pop();
     power_ = pow1 ^ pow2;
     stack.push(power_);
      return true;
    }

    else{
    return false;
    }

  }

}; // end of power



int main(int argc, char* argv[])
  {

    bool show_equation = false;

      for (int x = 1; x<argc; ++x) {

          if (strcmp(argv[x], "-h") == 0){
              std::cerr << help(*argv);
              break;
  
          } else if(strcmp(argv[x], "-v") == 0){
              ++x;
              show_equation = true;
            }
      }




  std::stack<Bigint> numberStack;
  std::vector<std::string> operators;

  std::string checker; // used to take input from char and verify
  std::string show;   // if -v is used it will output the equation entered 
  bool exit_calc;     // if true program exits
  bool verify;        // verify the inputs are correct
  char equation_[100]; 


  while (exit_calc == false) {
    std::cout<< "Enter equation in postfix \n";
  
    std::cin.getline(equation_, 100);
    checker = equation_;
    show = equation_;
    exit_calc = check_exit(checker);



  if (exit_calc == false) {

    verify =check_input(checker); 

      while (verify == false) {
            std::cerr << "Characters entered are not valid! Please reenter input." << std::endl;
            std::cin.getline(equation_, 100);
            checker = equation_;
            verify=check_input(checker);
            }

  
    char* pointer;                      //https://www.youtube.com/watch?v=TDyKV_sEDaI
    pointer = strtok(equation_, " " );  //at 2:10, used code to help break input 
    std::string equation;

      while( pointer != NULL) {
        equation = pointer;

        if (equation == "+" || equation == "*" || equation == "^") {
          operators.push_back(equation); 
        }
        else{
          Bigint newNumber(equation);
          numberStack.push(newNumber);
        }
      pointer = strtok(NULL, " ");
      }


  Bigint answer, result;

  std::vector<Handler*> chain = {new add(), new multiply(), new power() };

      if ( numberStack.size() == operators.size() + 1 ) {
    
            for (unsigned int count = 0; count < operators.size(); count++) {

                for(Handler* linker :chain) {

                    if (linker->handler(numberStack, operators[count]))  {
                      }
                
                   }
              
                if (count == operators.size() -1) {
                    result = numberStack.top();
                    answer = result;
                  }

               }// end of for loop

          }// end of if statement

      else {
        std::cerr << "Not enough operators or numbers entered !" <<std::endl;
      }



    if (show_equation == true) {
        std::cout << show << " = "; 
        answer.return_vector();
        std::cout << "\n";
        }

    if (show_equation == false) {
        answer.return_vector();
        std::cout << "\n";
        } 


    operators.clear(); // clears the vector

    while(!numberStack.empty() ) { // clears stack
        numberStack.pop();
    }


    }// end of if statement if exit calc = false

  }// end of while loop of whole program

  std::cout<< "Program has ended " <<std::endl; 




  return 0;
} // end of main




bool check_input(std::string input) { 

  bool result;
  int count= 0;

  for (unsigned long check = 0; check < input.size(); ++check) {
      if ( isdigit(input[check]) || input[check] == '+' || input[check] == '*' || input[check] == '^'|| input[check] == ' ' ) {
          }
          else{
           ++ count;
          }
        }

    if (count != 0) {
        result = false;
        }

        else{
        result = true;
        }

return result;
}


std::string usage(const char* name) {
  std::string output = "Usage: ";
  return output.append(name).append(" [-h] [-v] \n");
}


std::string help(const char* name) {
    
      auto output = usage(name);
      constexpr auto text = R"help_text(
        Options:
        -h  Show this text
        -v  Set a verbose output flag. Default = false.

        Running with no input from standard in enters 'interactive mode'.
        Equations can be entered one per line.
        The program runs until 'quit' is the first word on a line or EOF is reached.

        )help_text";
      return output.append(text);
}


bool check_exit(std::string text){

    if (text == "quit" || text == "Quit") {
    return true;
    }

return false;
}






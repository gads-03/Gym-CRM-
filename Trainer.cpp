#include <iostream>
#include <ostream>
#include <string>
#include <iomanip>
#include "Trainer.h"
#include <sstream>
using namespace std;

Trainer::Trainer (const int ID,  const string &FirstName, const string &LastName, string &email, double salary):
User (ID, FirstName, LastName, email){
    setsalary(salary);
}

 void Trainer::setsalary(double salary) {
    if (salary < 0.0) {
        throw invalid_argument("Salary must be >= 0.0");
     }
     this->salary= salary;
  }

 double Trainer::getsalary() const{ //check if we want this and toString const.
    return salary;
 }

 void Trainer::addBonus (double bonus){
    salary+=bonus;
 }

 ostream& operator<<(ostream& output, const Trainer& trainer) {

   output << static_cast<const User&>(trainer); // Call base class operator
   output << "Salary: $ " << fixed << setprecision(2) << trainer.getsalary() << endl;
   return output;
}
 

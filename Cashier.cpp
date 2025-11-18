#include "Cashier.h"
#include <sstream>
#include <stdexcept>
#include <iomanip>
using namespace std;

Cashier::Cashier (const int ID, const string& FirstName, const string& LastName, const string& email, double salary)
    :User (ID, FirstName, LastName, email) {
        setSalary(salary);
    }

    void Cashier :: setSalary(double salary) {
        if ( salary < 0.0) {
            throw invalid_argument("Salary cannot be negative.");
        }
        Salary = salary;
    } 

    double Cashier :: getSalary() const {
        return Salary;
    }

    ostream& operator<<(ostream& output, const Cashier& cashier){

        output << static_cast<const User&>(cashier);
        output << "Salary: $" << fixed << setprecision(2) << cashier.getSalary() << endl;

        return output;

    }
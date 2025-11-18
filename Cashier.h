#ifndef CASHIER_H
#define CASHIER_H

using namespace std;
#include "User.h"
#include <string>

class Cashier : public User {
    public:

    friend ostream operator<<(ostream& output, Cashier&);

    Cashier(const int ID, const string &FirstName, const string &LastName, const string &email, double salary = 0.0);

    void setSalary(double);
    double getSalary() const;

    string getRole() const override {
        return "Cashier";
    }
    

    private:

    double Salary;

};

#endif


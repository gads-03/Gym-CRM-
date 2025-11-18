#ifndef TRAINER_H
#define TRAINER_H
#include <string>
#include <iostream>
#include "User.h"
using namespace std;

class Trainer: public User {
    public:

    friend ostream& operator<<(ostream& output, const Trainer& trainer);

    Trainer(const int, const string &, const string &, string &, double=0.0);
    void setsalary(double);
    double getsalary() const;
    void addBonus(double);

    // overriding virutal mehtods from User
    string getRole() const override { 
        return "Trainer: ";}
    
    private:
    double salary;
};
#endif
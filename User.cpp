#include <iostream>
#include <ostream>
#include <string>
#include <iomanip>
#include "User.h"
using namespace std;

    User::User(const int ID,  const string &FirstName, const string &LastName, const string &email) 
        : ID(ID), FirstName(FirstName) , LastName(LastName), email(email) {
    }

    // initalizing the FirstName
    void User::setFirstName (const string &FirstName){
         this->FirstName=FirstName;
    }

    // returning the first name
     string User::getFirstName() const {
        return FirstName;
     }

     // intializing last name
     void User::setLastName (const string & LastName){
        this->LastName=LastName;
     }

     // returning the last name 
     string User::getLastName () const{
       return LastName;
     }

     // initializing the email
     void User::setEmail (const string & email) {
        this->email=email;
     }

     // returning the email 
    string User::getEmail () const{
        return email;
    }

    // initializing the ID
    void User::setID (const int ID)  {
        this->ID=ID;
     }

     // returning the ID
     int User::getID  () const{
        return ID;
     }

      istream & operator>>(istream & input, User & user){
        cout << "Enter First Name: "; 
        input>>user.FirstName;
        
        cout << "Enter Last Name: ";
        input>>user.LastName;
        
        cout << "Enter ID: ";
        input>>user.ID;

        cout << "Enter Email: ";
        input>>user.email;

        return input;
     }

      ostream & operator<<(ostream & output, const User & user){
        output<< "Full Name: "<< user.getFirstName()<<" "<<user.getLastName()<<endl;
        output<< "ID: "<< user.getID()<<endl;
        output<< "Email: "<< user.getEmail()<<endl;
        output << "Role: " << user.getRole() << endl;
        return output;
     }


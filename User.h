#ifndef USER_H
#define USER_H
#include <string>
#include <iostream>

using namespace std;

class User {

    public:

    // friend input and output operator to allow overloading 
    friend ostream &operator<<( ostream &, const User &);
    friend istream &operator>>( istream &, User &);

    //constructor
    User(const int ID , const string &FirstName, const string &LastName, const string &email);

    //setter and getter methods for FirstName
    void setFirstName(const string &);
    string getFirstName() const;

    //setter and getter methods for LastName
    void setLastName(const string &);
    string getLastName() const;

    //setter and getter methods for Email
    void setEmail(const string &);
    string getEmail() const;

    //setter and getter methods for ID 
    void setID(const int);
    int getID() const;

    // virtual member function for base class to get the user role 
    virtual string getRole() const { return "User";}

    private:
    int ID;
    string FirstName;
    string LastName;
    string email;
    
};

#endif
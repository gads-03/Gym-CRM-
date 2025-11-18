#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>

using namespace std;

class Transaction {
    private:
    int transactionID;
    int clientID;
    double amount;
    string type; // this is for membership, class, trainer, etc..
    string description;
    time_t date;
    int proccessedByID; //ID of the cashier/user who processed the transaction

    public:

    friend ostream& operator<<(ostream& output, const Transaction& transaction);

    //constructor
    Transaction(int id, int client, double amt, const string & typ, const string & desc, time_t d, int processed);

    //getters
    int getTransactionID() const;
    int getClientID() const;
    double getAmount() const;
    string getType() const;
    string getDescription() const;
    time_t getDate() const;
    int getProcessedByID() const;

    //setters
    void setClientID(int client);
    void setAmount(double amt);
    void setType(const string & t);
    void setDescription(const string & desc);
    void setDate(time_t d);
    void setProcessedByID(int processed);

    string getFormattedDate() const;
    
};

#endif



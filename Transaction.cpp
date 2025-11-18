#include "Transaction.h"
#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std;


//constructor
Transaction::Transaction(int id, int client, double amt, const string & t, const string & desc,
time_t d, int processed ) 
: transactionID(id),
clientID(client),
amount(amt),
type(t),
description(desc),
date(d),
proccessedByID(processed) {
    if (amount < 0.0) {
        throw invalid_argument("Transaction amount can't be negative");
    }
}

//getters
int Transaction::getTransactionID() const {
    return transactionID;
}

int Transaction::getClientID() const {
    return clientID;
}

double Transaction::getAmount() const {
    return amount;
}

string Transaction::getType() const {
    return type;
}

string Transaction::getDescription() const {
    return description;
}

time_t Transaction::getDate() const {
    return date;
}

int Transaction::getProcessedByID() const {
    return proccessedByID;
}

//setters

void Transaction::setClientID(int client) {
    clientID = client;
}

void Transaction::setAmount(double amt) {
    if (amt < 0.0) {
        throw invalid_argument("Amount can't be negative");
    }
    amount = amt;
}

void Transaction::setType(const string & t) {
    type = t;
}

void Transaction::setDescription(const string & desc) {
    description = desc;
}

void Transaction::setDate(time_t d) {
    date = d;
}

void Transaction::setProcessedByID(int processed) {
    proccessedByID = processed;
}

//utility methods
string Transaction::getFormattedDate() const {
    char buffer[80];
    struct tm* timeinfo = localtime(&date);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", timeinfo);
    return string(buffer);
}

ostream& operator<<(ostream& output, const Transaction& transaction) {
    output << "Transaction ID: " << transaction.transactionID << endl;
    output << "Client ID: " << transaction.clientID << endl;
    output << "Amount: $" << fixed << setprecision(2) << transaction.amount << endl;
    output << "Type: " << transaction.type << endl;
    output << "Date: " << transaction.getFormattedDate() << endl;
    output << "Processed by ID: " << transaction.proccessedByID << endl;
    output << "Description: " << transaction.description << endl;
    
    return output;
}
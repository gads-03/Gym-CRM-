#ifndef FITNESS_CRM_H
#define FITNESS_CRM_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <memory>
#include <fstream>
#include <ctime>
#include <string>
#include "Cashier.h"
#include "User.h"
#include "Trainer.h"
#include "Client.h"
#include "Transaction.h"

// Define a type for predicate functions used in searching
template<typename T>
using Predicate = std::function<bool(const std::shared_ptr<T>&, const std::string&)>;

class FitnessCRM {
private:
    // Storage for users, trainers, clients, and transactions
    std::vector<std::shared_ptr<User>> users;
    std::vector<std::shared_ptr<Trainer>> trainers;
    std::vector<std::shared_ptr<Client>> clients;
    std::vector<std::shared_ptr<Transaction>> transactions;
    
    // File paths for persistence
    std::string usersFile;
    std::string transactionsFile;
    
    // Currently logged-in user
    std::shared_ptr<User> currentUser;
    
    // Helper functions for loading and saving data
    void loadUsers();
    void saveUsers();
    void loadTransactions();
    void saveTransactions();

public:
    // Constructor with file paths for data persistence
    FitnessCRM(const std::string& usersFilePath, const std::string& transactionsFilePath);
    
    // Destructor to ensure data is saved
    ~FitnessCRM();
    
    // User management
    bool addUser(const User& user);
    bool removeUser(int id);
    bool login(int id, const std::string& email);
    void logout();
    std::shared_ptr<User> getCurrentUser() const;
    std::vector<std::shared_ptr<User>> getUsers() const;
    void displayAllUsers() const;
    
    // Trainer management
    bool addTrainer(const Trainer& trainer);
    bool removeTrainer(int id);
    std::shared_ptr<Trainer> getTrainer(int id) const;
    std::vector<std::shared_ptr<Trainer>> getTrainers() const;
   void displayAllTrainers() const;
    
    // Client management
   bool addClient(const Client& client);
    bool updateClient(int id, const Client& updatedClient);
    bool removeClient(int id);
    std::shared_ptr<Client> getClient(int id) const;
    std::vector<std::shared_ptr<Client>> getClients() const;
    void displayAllClients() const;
    bool assignTrainerToClient(int clientId, int trainerId);
    
    // Sorting methods for clients
    void sortClientsByName();
    void sortClientsByID();
    void sortClientsByFee();
    
    // Transaction management
    bool createTransaction(const Transaction& transaction);
    std::vector<std::shared_ptr<Transaction>> getTransactionsForClient(int clientId) const;
   std::vector<std::shared_ptr<Transaction>> getTransactionsByDateRange(time_t startDate, time_t endDate) const;
    void displayAllTransactions() const;
    
    // Report generation
   void generateFinancialReport(const std::string& fileName) const;
   void generateMonthlyRevenueReport(const std::string& fileName, int month, int year) const;
   void generateTrainerPerformanceReport(const std::string& fileName, int trainerId = 0) const;
    
    // Generic search function with predicates
    template<typename T>
    std::vector<std::shared_ptr<T>> search(
        const std::vector<std::shared_ptr<T>>& collection,
        Predicate<T> predicate,
        const std::string& searchTerm) const {
        
        std::vector<std::shared_ptr<T>> results;
        
        for (const auto& item : collection) {
            if (predicate(item, searchTerm)) {
                results.push_back(item);
            }
        }
        
        return results;
    }
    
    // Predicate functions for searching
    static bool clientNamePredicate(const std::shared_ptr<Client>& client, const std::string& name);
    static bool trainerNamePredicate(const std::shared_ptr<Trainer>& trainer, const std::string& name);
    static bool userNamePredicate(const std::shared_ptr<User>& user, const std::string& name);
};

#endif // FITNESS_CRM_H
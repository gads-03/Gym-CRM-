#include "FitnessCRM.h"
#include <sstream>
#include <iomanip>
#include <ctime>
#include <map>
using namespace std;
// Constructor
FitnessCRM::FitnessCRM(const std::string& usersFilePath, const std::string& transactionsFilePath)
    : usersFile(usersFilePath), transactionsFile(transactionsFilePath), currentUser(nullptr) {
    // Load data from files
    loadUsers();
    loadTransactions();
}

// Destructor
FitnessCRM::~FitnessCRM() {
    // Save data to files
    saveUsers();
    saveTransactions();
}

// User Management Methods
bool FitnessCRM::addUser(const User& user) {
    // Check if a user with the same ID already exists
    for (const auto& existingUser : users) {
        if (existingUser->getID() == user.getID()) {
            return false;
        }
    }
    
    // Add the new user
    users.push_back(std::make_shared<User>(user));
    return true;
}

bool FitnessCRM::removeUser(int id) {
    // Find and remove user with the given ID
    auto it = std::find_if(users.begin(), users.end(),
                          [id](const std::shared_ptr<User>& user) {
                              return user->getID() == id;
                          });
    
    if (it != users.end()) {
        users.erase(it);
        return true;
    }
    
    return false;
}

bool FitnessCRM::login(int id, const std::string& email) {
    // Find user with matching ID and email
    for (const auto& user : users) {
        if (user->getID() == id && user->getEmail() == email) {
            currentUser = user;
            std::cout << "Login successful. Welcome, " << user->getFirstName() << "!" << std::endl;
            return true;
        }
    }
    
    std::cout << "Login failed. Invalid ID or email." << std::endl;
    return false;
}

void FitnessCRM::logout() {
    currentUser = nullptr;
    std::cout << "You have been logged out." << std::endl;
}

std::shared_ptr<User> FitnessCRM::getCurrentUser() const {
    return currentUser;
}

std::vector<std::shared_ptr<User>> FitnessCRM::getUsers() const {
    return users;
}

void FitnessCRM::displayAllUsers() const {
    std::cout << "All Users:" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    if (users.empty()) {
        std::cout << "No users found." << std::endl;
        return;
    }
    
    for (const auto& user : users) {
        std::cout << *user << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
    }
}

// Trainer Management Methods
bool FitnessCRM::addTrainer(const Trainer& trainer) {
    // Check if a trainer with the same ID already exists
    for (const auto& existingTrainer : trainers) {
        if (existingTrainer->getID() == trainer.getID()) {
            return false;
        }
    }
    
    // Add the new trainer
    trainers.push_back(std::make_shared<Trainer>(trainer));
    
    // Also add the trainer to the users list
    users.push_back(std::make_shared<Trainer>(trainer));
    
    return true;
}

bool FitnessCRM::removeTrainer(int id) {
    // Find and remove trainer with the given ID
    auto it = std::find_if(trainers.begin(), trainers.end(),
                          [id](const std::shared_ptr<Trainer>& trainer) {
                              return trainer->getID() == id;
                          });
    
    if (it != trainers.end()) {
        trainers.erase(it);
        
        // Also remove from users list
        removeUser(id);
        
        return true;
    }
    
    return false;
}

std::shared_ptr<Trainer> FitnessCRM::getTrainer(int id) const {
    for (const auto& trainer : trainers) {
        if (trainer->getID() == id) {
            return trainer;
        }
    }
    
    return nullptr;
}

std::vector<std::shared_ptr<Trainer>> FitnessCRM::getTrainers() const {
    return trainers;
}

void FitnessCRM::displayAllTrainers() const {
    std::cout << "All Trainers:" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    if (trainers.empty()) {
        std::cout << "No trainers found." << std::endl;
        return;
    }
    
    for (const auto& trainer : trainers) {
        std::cout << *trainer << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
    }
}

// Client Management Methods
bool FitnessCRM::addClient(const Client& client) {
    // Check if a client with the same ID already exists
    for (const auto& existingClient : clients) {
        if (existingClient->getID() == client.getID()) {
            return false;
        }
    }
    
    // Add the new client
    clients.push_back(std::make_shared<Client>(client));
    
    // Also add the client to the users list
    users.push_back(std::make_shared<Client>(client));
    
    return true;
}

bool FitnessCRM::updateClient(int id, const Client& updatedClient) {
    for (auto& client : clients) {
        if (client->getID() == id) {
            // Update client details
            client = std::make_shared<Client>(updatedClient);
            
            // Also update in users list
            for (auto& user : users) {
                if (user->getID() == id) {
                    user = std::make_shared<Client>(updatedClient);
                    break;
                }
            }
            
            return true;
        }
    }
    
    return false;
}

bool FitnessCRM::removeClient(int id) {
    // Find and remove client with the given ID
    auto it = std::find_if(clients.begin(), clients.end(),
                          [id](const std::shared_ptr<Client>& client) {
                              return client->getID() == id;
                          });
    
    if (it != clients.end()) {
        clients.erase(it);
        
        // Also remove from users list
        removeUser(id);
        
        return true;
    }
    
    return false;
}

std::shared_ptr<Client> FitnessCRM::getClient(int id) const {
    for (const auto& client : clients) {
        if (client->getID() == id) {
            return client;
        }
    }
    
    return nullptr;
}

std::vector<std::shared_ptr<Client>> FitnessCRM::getClients() const {
    return clients;
}

void FitnessCRM::displayAllClients() const {
    std::cout << "All Clients:" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    if (clients.empty()) {
        std::cout << "No clients found." << std::endl;
        return;
    }
    
    for (const auto& client : clients) {
        std::cout << *client << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
    }
}

bool FitnessCRM::assignTrainerToClient(int clientId, int trainerId) {
    auto client = getClient(clientId);
    auto trainer = getTrainer(trainerId);
    
    if (!client || !trainer) {
        return false;
    }
    
    client->setPersonalTrainer(trainerId);
    return true;
}

// Sorting methods for clients
void FitnessCRM::sortClientsByName() {
    std::sort(clients.begin(), clients.end(),
             [](const std::shared_ptr<Client>& a, const std::shared_ptr<Client>& b) {
                 if (a->getLastName() == b->getLastName()) {
                     return a->getFirstName() < b->getFirstName();
                 }
                 return a->getLastName() < b->getLastName();
             });
}

void FitnessCRM::sortClientsByID() {
    std::sort(clients.begin(), clients.end(),
             [](const std::shared_ptr<Client>& a, const std::shared_ptr<Client>& b) {
                 return a->getID() < b->getID();
             });
}

void FitnessCRM::sortClientsByFee() {
    std::sort(clients.begin(), clients.end(),
             [](const std::shared_ptr<Client>& a, const std::shared_ptr<Client>& b) {
                 return a->getCost() < b->getCost();
             });
}

// Transaction management
bool FitnessCRM::createTransaction(const Transaction& transaction) {
    // Check if a transaction with the same ID already exists
    for (const auto& existingTransaction : transactions) {
        if (existingTransaction->getTransactionID() == transaction.getTransactionID()) {
            return false;
        }
    }
    
    transactions.push_back(std::make_shared<Transaction>(transaction));
    return true;
}

std::vector<std::shared_ptr<Transaction>> FitnessCRM::getTransactionsForClient(int clientId) const {
    std::vector<std::shared_ptr<Transaction>> clientTransactions;
    
    for (const auto& transaction : transactions) {
        if (transaction->getClientID() == clientId) {
            clientTransactions.push_back(transaction);
        }
    }
    
    return clientTransactions;
}

std::vector<std::shared_ptr<Transaction>> FitnessCRM::getTransactionsByDateRange(time_t startDate, time_t endDate) const {
    std::vector<std::shared_ptr<Transaction>> dateRangeTransactions;
    
    for (const auto& transaction : transactions) {
        time_t transactionDate = transaction->getDate();
        if (transactionDate >= startDate && transactionDate <= endDate) {
            dateRangeTransactions.push_back(transaction);
        }
    }
    
    return dateRangeTransactions;
}

void FitnessCRM::displayAllTransactions() const {
    std::cout << "All Transactions:" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    if (transactions.empty()) {
        std::cout << "No transactions found." << std::endl;
        return;
    }
    
    for (const auto& transaction : transactions) {
        std::cout << *transaction << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
    }
}

// Report generation
void FitnessCRM::generateFinancialReport(const std::string& fileName) const {
    std::ofstream reportFile(fileName);
    
    if (!reportFile) {
        std::cerr << "Error: Could not open file " << fileName << " for writing." << std::endl;
        return;
    }
    
    reportFile << "Financial Report" << std::endl;
    reportFile << "=======================================" << std::endl;
    reportFile << "Generated on: " << std::put_time(std::localtime(std::time_t()), "%Y-%m-%d %H:%M:%S") << std::endl;
    reportFile << "=======================================" << std::endl << std::endl;
    
    double totalRevenue = 0.0;
    
    reportFile << "Transaction Summary:" << std::endl;
    reportFile << "----------------------------------------" << std::endl;
    
    map<string, double> revenueByType;
    
    for (const auto& transaction : transactions) {
        totalRevenue += transaction->getAmount();
        revenueByType[transaction->getType()] += transaction->getAmount();
    }
    
    for (const auto& [type, amount] : revenueByType) {
        reportFile << type << ": $" << std::fixed << std::setprecision(2) << amount << std::endl;
    }
    
    reportFile << "----------------------------------------" << std::endl;
    reportFile << "Total Revenue: $" << std::fixed << std::setprecision(2) << totalRevenue << std::endl;
    
    reportFile.close();
    
    std::cout << "Financial report generated successfully: " << fileName << std::endl;
}

void FitnessCRM::generateMonthlyRevenueReport(const std::string& fileName, int month, int year) const {
    std::ofstream reportFile(fileName);
    
    if (!reportFile) {
        std::cerr << "Error: Could not open file " << fileName << " for writing." << std::endl;
        return;
    }
    
    reportFile << "Monthly Revenue Report - " << month << "/" << year << std::endl;
    reportFile << "=======================================" << std::endl;
    reportFile << "Generated on: " << std::put_time(std::localtime(std::time_t()), "%Y-%m-%d %H:%M:%S") << std::endl;
    reportFile << "=======================================" << std::endl << std::endl;
    
    double monthlyRevenue = 0.0;
    
    // Calculate start and end times for the month
    std::tm startTm = {0};
    startTm.tm_year = year - 1900;
    startTm.tm_mon = month - 1;
    startTm.tm_mday = 1;
    time_t startTime = std::mktime(&startTm);
    
    std::tm endTm = startTm;
    endTm.tm_mon++;
    if (endTm.tm_mon > 11) {
        endTm.tm_mon = 0;
        endTm.tm_year++;
    }
    time_t endTime = std::mktime(&endTm) - 1; // Last second of the month
    
    reportFile << "Transaction Summary:" << std::endl;
    reportFile << "----------------------------------------" << std::endl;
    
    std::map<std::string, double> revenueByType;
    int transactionCount = 0;
    
    for (const auto& transaction : transactions) {
        time_t transactionDate = transaction->getDate();
        if (transactionDate >= startTime && transactionDate <= endTime) {
            monthlyRevenue += transaction->getAmount();
            revenueByType[transaction->getType()] += transaction->getAmount();
            transactionCount++;
        }
    }
    
    for (const auto& [type, amount] : revenueByType) {
        reportFile << type << ": $" << std::fixed << std::setprecision(2) << amount << std::endl;
    }
    
    reportFile << "----------------------------------------" << std::endl;
    reportFile << "Total Transactions: " << transactionCount << std::endl;
    reportFile << "Total Monthly Revenue: $" << std::fixed << std::setprecision(2) << monthlyRevenue << std::endl;
    
    reportFile.close();
    
    std::cout << "Monthly revenue report generated successfully: " << fileName << std::endl;
}

void FitnessCRM::generateTrainerPerformanceReport(const std::string& fileName, int trainerId) const {
    std::ofstream reportFile(fileName);
    
    if (!reportFile) {
        std::cerr << "Error: Could not open file " << fileName << " for writing." << std::endl;
        return;
    }
    
    reportFile << "Trainer Performance Report" << std::endl;
    reportFile << "=======================================" << std::endl;
    reportFile << "Generated on: " << std::put_time(std::localtime(std::time_t()), "%Y-%m-%d %H:%M:%S") << std::endl;
    reportFile << "=======================================" << std::endl << std::endl;
    
    std::vector<std::shared_ptr<Trainer>> reportTrainers;
    
    if (trainerId == 0) {
        // Report for all trainers
        reportTrainers = trainers;
    } else {
        // Report for a specific trainer
        auto trainer = getTrainer(trainerId);
        if (trainer) {
            reportTrainers.push_back(trainer);
        } else {
            reportFile << "Error: Trainer with ID " << trainerId << " not found." << std::endl;
            reportFile.close();
            std::cout << "Error generating trainer performance report: Trainer not found." << std::endl;
            return;
        }
    }
    
    for (const auto& trainer : reportTrainers) {
        reportFile << "Trainer: " << trainer->getFirstName() << " " << trainer->getLastName() << " (ID: " << trainer->getID() << ")" << std::endl;
        reportFile << "----------------------------------------" << std::endl;
        
        // Count clients assigned to this trainer
        int clientCount = 0;
        for (const auto& client : clients) {
            if (client->getPersonalTrainer() == trainer->getID()) {
                clientCount++;
            }
        }
        
        reportFile << "Assigned Clients: " << clientCount << std::endl;
        reportFile << "Salary: $" << std::fixed << std::setprecision(2) << trainer->getsalary() << std::endl;
        
        // Calculate trainer's revenue contribution
        double trainerRevenue = 0.0;
        for (const auto& transaction : transactions) {
            if (transaction->getType() == "Personal Training" && 
                transaction->getProcessedByID() == trainer->getID()) {
                trainerRevenue += transaction->getAmount();
            }
        }
        
        reportFile << "Revenue Generated: $" << std::fixed << std::setprecision(2) << trainerRevenue << std::endl;
        reportFile << std::endl;
    }
    
    reportFile.close();
    
    std::cout << "Trainer performance report generated successfully: " << fileName << std::endl;
}

// Helper functions for loading and saving data
void FitnessCRM::loadUsers() {
    std::ifstream inFile(usersFile);
    
    if (!inFile) {
        std::cerr << "Warning: Could not open file " << usersFile << " for reading. Starting with empty user list." << std::endl;
        return;
    }
    
    std::string line;
    std::string role, firstName, lastName, email;
    int id;
    double salary, cost;
    int membershipPlanID;
    
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        
        ss >> role >> id >> firstName >> lastName >> email;
        
        if (role == "User") {
            users.push_back(std::make_shared<User>(id, firstName, lastName, email));
        } else if (role == "Trainer") {
            ss >> salary;
            auto trainer = std::make_shared<Trainer>(id, firstName, lastName, email, salary);
            users.push_back(trainer);
            trainers.push_back(trainer);
        } else if (role == "Client") {
            ss >> cost >> membershipPlanID;
            auto client = std::make_shared<Client>(id, firstName, lastName, email, cost, membershipPlanID);
            users.push_back(client);
            clients.push_back(client);
            
            // Load additional client data (class enrollments, personal trainer, etc.)
            int personalTrainerID;
            ss >> personalTrainerID;
            if (personalTrainerID >= 0) {
                client->setPersonalTrainer(personalTrainerID);
            }
            
            int numClasses;
            ss >> numClasses;
            for (int i = 0; i < numClasses; i++) {
                int classID;
                ss >> classID;
                client->addEnrolledClass(classID);
            }
            
            // Load attendance data
            int numAttendance;
            ss >> numAttendance;
            for (int i = 0; i < numAttendance; i++) {
                time_t attendanceDate;
                ss >> attendanceDate;
                client->recordAttendance(attendanceDate);
            }
            
            // Load membership dates
            time_t startDate, endDate;
            ss >> startDate >> endDate;
            client->setMembershipStartDate(startDate);
            client->setMembershipEndDate(endDate);
        } else if (role == "Cashier") {
            ss >> salary;
            auto cashier = std::make_shared< Cashier >(id, firstName, lastName, email, salary);
            users.push_back(cashier);
        }
    }
    
    inFile.close();
}

void FitnessCRM::saveUsers() {
    std::ofstream outFile(usersFile);
    
    if (!outFile) {
        std::cerr << "Error: Could not open file " << usersFile << " for writing." << std::endl;
        return;
    }
    
    for (const auto& user : users) {
        std::string role = user->getRole();
        outFile << role << " " << user->getID() << " " << user->getFirstName() << " " 
                << user->getLastName() << " " << user->getEmail();
        
        if (role == "Trainer") {
            auto trainer = std::static_pointer_cast<Trainer>(user);
            outFile << " " << trainer->getsalary();
        } else if (role == "Client") {
            auto client = std::static_pointer_cast<Client>(user);
            outFile << " " << client->getCost() << " " << client->getMembershipPlanID();
            
            // Save additional client data
            outFile << " " << client->getPersonalTrainer();
            
            // Save class enrollments
            const auto& enrolledClasses = client->getEnrolledClasses();
            outFile << " " << enrolledClasses.size();
            for (int classID : enrolledClasses) {
                outFile << " " << classID;
            }
            
            // Save attendance history
            const auto& attendance = client->getAttendanceHistory();
            outFile << " " << attendance.size();
            for (time_t date : attendance) {
                outFile << " " << date;
            }
            
            // Save membership dates
            outFile << " " << client->getMembershipStartDate() << " " << client->getMembershipEndDate();
        } else if (role == "Cashier") {
            auto cashier = std::static_pointer_cast<Cashier>(user);
            outFile << " " << cashier->getSalary();
        }
        
        outFile << std::endl;
    }
    
    outFile.close();
}

void FitnessCRM::loadTransactions() {
    std::ifstream inFile(transactionsFile);
    
    if (!inFile) {
        std::cerr << "Warning: Could not open file " << transactionsFile << " for reading. Starting with empty transaction list." << std::endl;
        return;
    }
    
    std::string line;
    int transactionID, clientID, processedByID;
    double amount;
    std::string type, description;
    time_t date;
    
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        
        ss >> transactionID >> clientID >> amount;
        
        // Extract the type (may contain spaces)
        std::getline(ss, type, '|');
        type = type.substr(1); // Remove leading space
        
        // Extract the description (may contain spaces)
        std::getline(ss, description, '|');
        
        ss >> date >> processedByID;
        
        transactions.push_back(std::make_shared<Transaction>(
            transactionID, clientID, amount, type, description, date, processedByID));
    }
    
    inFile.close();
}

void FitnessCRM::saveTransactions() {
    std::ofstream outFile(transactionsFile);
    
    if (!outFile) {
        std::cerr << "Error: Could not open file " << transactionsFile << " for writing." << std::endl;
        return;
    }
    
    for (const auto& transaction : transactions) {
        outFile << transaction->getTransactionID() << " "
                << transaction->getClientID() << " "
                << transaction->getAmount() << " "
                << transaction->getType() << "|"
                << transaction->getDescription() << "|"
                << transaction->getDate() << " "
                << transaction->getProcessedByID() << std::endl;
    }
    
    outFile.close();
}

// Predicate functions for searching
bool FitnessCRM::clientNamePredicate(const std::shared_ptr<Client>& client, const std::string& name) {
    std::string fullName = client->getFirstName() + " " + client->getLastName();
    std::string searchLower = name;
    std::string fullNameLower = fullName;
    
    // Convert both to lowercase for case-insensitive comparison
    transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);
    transform(fullNameLower.begin(), fullNameLower.end(), fullNameLower.begin(), ::tolower);
    
    return fullNameLower.find(searchLower) != std::string::npos;
}

bool FitnessCRM::trainerNamePredicate(const std::shared_ptr<Trainer>& trainer, const std::string& name) {
    std::string fullName = trainer->getFirstName() + " " + trainer->getLastName();
    std::string searchLower = name;
    std::string fullNameLower = fullName;
    
    // Convert both to lowercase for case-insensitive comparison
    transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);
    transform(fullNameLower.begin(), fullNameLower.end(), fullNameLower.begin(), ::tolower);
    
    return fullNameLower.find(searchLower) != std::string::npos;
}

bool FitnessCRM::userNamePredicate(const std::shared_ptr<User>& user, const std::string& name) {
    std::string fullName = user->getFirstName() + " " + user->getLastName();
    std::string searchLower = name;
    std::string fullNameLower = fullName;
    
    // Convert both to lowercase for case-insensitive comparison
    transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);
    transform(fullNameLower.begin(), fullNameLower.end(), fullNameLower.begin(), ::tolower);
    
    return fullNameLower.find(searchLower) != std::string::npos;
}
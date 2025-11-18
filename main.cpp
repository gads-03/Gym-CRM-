#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <limits>
#include <ctime>
#include <iomanip>

#include "User.h"
#include "Trainer.h"
#include "Client.h"
#include "Cashier.h"
#include "Class.h"
#include "MembershipPlan.h"
#include "Transaction.h"
#include "FitnessCRM.h"

using namespace std;

// Function prototypes
void displayMenu();
void handleUserManagement(FitnessCRM& crm);
void handleClientManagement(FitnessCRM& crm);
void handleTrainerManagement(FitnessCRM& crm);
void handleClassManagement(FitnessCRM& crm);
void handleMembershipManagement(FitnessCRM& crm);
void handleTransactionManagement(FitnessCRM& crm);

// Global variables for system data
vector<shared_ptr<Class>> classes;
vector<shared_ptr<MembershipPlan>> membershipPlans;

// Helper function to create a time_t from date components
time_t createDateTime(int year, int month, int day, int hour = 0, int min = 0) {
    struct tm timeinfo = {0};
    timeinfo.tm_year = year - 1900;
    timeinfo.tm_mon = month - 1;
    timeinfo.tm_mday = day;
    timeinfo.tm_hour = hour;
    timeinfo.tm_min = min;
    return mktime(&timeinfo);
}

// Helper function to clear input buffer
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Helper function to get a validated integer input
int getIntInput(const string& prompt) {
    int value;
    cout << prompt;
    while (!(cin >> value)) {
        cout << "Invalid input. Please enter a number: ";
        clearInputBuffer();
    }
    clearInputBuffer();
    return value;
}

// Helper function to get a validated double input
double getDoubleInput(const string& prompt) {
    double value;
    cout << prompt;
    while (!(cin >> value)) {
        cout << "Invalid input. Please enter a number: ";
        clearInputBuffer();
    }
    clearInputBuffer();
    return value;
}

// Helper function to get a string input
string getStringInput(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

// Initialize sample data for the system
void initializeSampleData(FitnessCRM& crm) {
    // Create some users
    string email1 = "john@example.com";
    string email2 = "sarah@example.com";
    string email3 = "mike@example.com";
    
    crm.addUser(User(1001, "John", "Doe", "admin@example.com"));
    
    // Create trainers
    Trainer trainer1(2001, "Sarah", "Johnson", email1, 35000.0);
    Trainer trainer2(2002, "Mike", "Smith", email2, 32000.0);
    
    crm.addTrainer(trainer1);
    crm.addTrainer(trainer2);
    
    // Create membership plans
    membershipPlans.push_back(make_shared<MembershipPlan>(
        1, "Basic", "Access to gym facilities only", 29.99, 1, false, false, 0, 0));
    
    membershipPlans.push_back(make_shared<MembershipPlan>(
        2, "Standard", "Access to gym and group classes", 49.99, 3, true, false, 8, 0));
    
    membershipPlans.push_back(make_shared<MembershipPlan>(
        3, "Premium", "Full access including personal training", 99.99, 6, true, true, 12, 4));
    
    // Create clients
    Client client1(3001, "Alice", "Brown", "alice@example.com", 49.99, 2);
    Client client2(3002, "Bob", "Wilson", "bob@example.com", 29.99, 1);
    Client client3(3003, "Carol", "White", "carol@example.com", 99.99, 3);
    
    // Add personal trainers to clients
    client1.setPersonalTrainer(2001);
    client3.setPersonalTrainer(2002);
    
    crm.addClient(client1);
    crm.addClient(client2);
    crm.addClient(client3);
    
    // Create cashier
    Cashier cashier(4001, "David", "Green", email3, 28000.0);
    
    // Create classes
    time_t tomorrow_9am = createDateTime(2025, 4, 25, 9, 0);
    time_t tomorrow_10am = createDateTime(2025, 4, 25, 10, 0);
    time_t tomorrow_5pm = createDateTime(2025, 4, 25, 17, 0);
    time_t tomorrow_6pm = createDateTime(2025, 4, 25, 18, 0);
    
    classes.push_back(make_shared<Class>(
        1, "Yoga Basics", "Introduction to yoga postures", tomorrow_9am, tomorrow_10am, 15, 2001));
    
    classes.push_back(make_shared<Class>(
        2, "HIIT Workout", "High-intensity interval training", tomorrow_5pm, tomorrow_6pm, 12, 2002));
    
    // Enroll clients in classes
    classes[0]->enrollClient(3001);
    classes[0]->enrollClient(3003);
    classes[1]->enrollClient(3002);
    
    // Create transactions
    crm.createTransaction(Transaction(
        1, 3001, 49.99, "Membership", "Standard 3-month membership", time(nullptr), 4001));
    
    crm.createTransaction(Transaction(
        2, 3002, 29.99, "Membership", "Basic 1-month membership", time(nullptr), 4001));
    
    crm.createTransaction(Transaction(
        3, 3003, 99.99, "Membership", "Premium 6-month membership", time(nullptr), 4001));
    
    // Record attendance for clients
    Client* client1Ptr = dynamic_cast<Client*>(crm.getClient(3001).get());
    if (client1Ptr) {
        client1Ptr->recordAttendance(time(nullptr) - 86400); // Yesterday
        client1Ptr->recordAttendance(time(nullptr));         // Today
    }
    
    Client* client3Ptr = dynamic_cast<Client*>(crm.getClient(3003).get());
    if (client3Ptr) {
        client3Ptr->recordAttendance(time(nullptr));         // Today
    }
    
    cout << "Sample data initialized successfully." << endl;
}

int main() {
    cout << "==============================================" << endl;
    cout << "     FITNESS CLUB MANAGEMENT SYSTEM          " << endl;
    cout << "==============================================" << endl;
    
    // Initialize the CRM system with file paths for persistence
    FitnessCRM crm("users.dat", "transactions.dat");
    
    // Initialize sample data
    initializeSampleData(crm);
    
    bool loggedIn = false;
    
    // Login loop
    while (!loggedIn) {
        cout << "\nPlease log in to continue:" << endl;
        int id = getIntInput("Enter your ID: ");
        clearInputBuffer();
        string email = getStringInput("Enter your email: ");
        
        loggedIn = crm.login(id, email);
        
        if (!loggedIn) {
            char tryAgain;
            cout << "Would you like to try again? (y/n): ";
            cin >> tryAgain;
            clearInputBuffer();
            
            if (tolower(tryAgain) != 'y') {
                cout << "Exiting program. Goodbye!" << endl;
                return 0;
            }
        }
    }
    
    // Main menu loop
    bool quit = false;
    while (!quit) {
        displayMenu();
        
        int choice = getIntInput("Enter your choice (1-7): ");
        
        switch (choice) {
            case 1:
                handleUserManagement(crm);
                break;
            case 2:
                handleClientManagement(crm);
                break;
            case 3:
                handleTrainerManagement(crm);
                break;
            case 4:
                handleClassManagement(crm);
                break;
            case 5:
                handleMembershipManagement(crm);
                break;
            case 6:
                handleTransactionManagement(crm);
                break;
            case 7:
                cout << "Logging out and exiting program. Goodbye!" << endl;
                crm.logout();
                quit = true;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    
    return 0;
}

void displayMenu() {
    cout << "\n==============================================" << endl;
    cout << "                MAIN MENU                    " << endl;
    cout << "==============================================" << endl;
    cout << "1. User Management" << endl;
    cout << "2. Client Management" << endl;
    cout << "3. Trainer Management" << endl;
    cout << "4. Class Management" << endl;
    cout << "5. Membership Plan Management" << endl;
    cout << "6. Transaction Management" << endl;
    cout << "7. Logout and Exit" << endl;
    cout << "==============================================" << endl;
}

void handleUserManagement(FitnessCRM& crm) {
    bool back = false;
    
    while (!back) {
        cout << "\n--- User Management ---" << endl;
        cout << "1. Display All Users" << endl;
        cout << "2. Add New User" << endl;
        cout << "3. Remove User" << endl;
        cout << "4. Back to Main Menu" << endl;
        
        int choice = getIntInput("Enter your choice (1-4): ");
        
        switch (choice) {
            case 1: {
                // Display all users
                crm.displayAllUsers();
                break;
            }
            case 2: {
                // Add new user
                int id = getIntInput("Enter user ID: ");
                clearInputBuffer();
                string firstName = getStringInput("Enter first name: ");
                string lastName = getStringInput("Enter last name: ");
                string email = getStringInput("Enter email: ");
                
                User newUser(id, firstName, lastName, email);
                
                if (crm.addUser(newUser)) {
                    cout << "User added successfully." << endl;
                } else {
                    cout << "Failed to add user. ID may already exist." << endl;
                }
                break;
            }
            case 3: {
                // Remove user
                int id = getIntInput("Enter ID of user to remove: ");
                
                if (crm.removeUser(id)) {
                    cout << "User removed successfully." << endl;
                } else {
                    cout << "Failed to remove user. ID not found." << endl;
                }
                break;
            }
            case 4:
                back = true;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void handleClientManagement(FitnessCRM& crm) {
    bool back = false;
    
    while (!back) {
        cout << "\n--- Client Management ---" << endl;
        cout << "1. Display All Clients" << endl;
        cout << "2. Add New Client" << endl;
        cout << "3. Update Client Information" << endl;
        cout << "4. Assign Trainer to Client" << endl;
        cout << "5. Record Client Attendance" << endl;
        cout << "6. Enroll Client in Class" << endl;
        cout << "7. Back to Main Menu" << endl;
        
        int choice = getIntInput("Enter your choice (1-7): ");
        
        switch (choice) {
            case 1: {
                // Display all clients
                crm.displayAllClients();
                break;
            }
            case 2: {
                // Add new client
                int id = getIntInput("Enter client ID: ");
                clearInputBuffer();
                string firstName = getStringInput("Enter first name: ");
                string lastName = getStringInput("Enter last name: ");
                string email = getStringInput("Enter email: ");
                double cost = getDoubleInput("Enter subscription cost: $");
                
                // Display available membership plans
                cout << "Available Membership Plans:" << endl;
                cout << "ID 0: No membership" << endl;
                for (const auto& plan : membershipPlans) {
                    cout << "ID " << plan->getPlanID() << ": " << plan->getName() 
                         << " - $" << plan->getMonthlyCost() << "/month" << endl;
                }
                
                int planId = getIntInput("Enter membership plan ID (0 for none): ");
                int actualPlanId = planId > 0 ? planId : -1;
                
                Client newClient(id, firstName, lastName, email, cost, actualPlanId);
                
                if (crm.addClient(newClient)) {
                    cout << "Client added successfully." << endl;
                } else {
                    cout << "Failed to add client. ID may already exist." << endl;
                }
                break;
            }
            case 3: {
                // Update client information
                int id = getIntInput("Enter ID of client to update: ");
                
                auto client = crm.getClient(id);
                if (!client) {
                    cout << "Client not found." << endl;
                    break;
                }
                
                cout << "Current client information:" << endl;
                cout << *client << endl;
                
                clearInputBuffer();
                string firstName = getStringInput("Enter new first name (leave blank to keep current): ");
                string lastName = getStringInput("Enter new last name (leave blank to keep current): ");
                string email = getStringInput("Enter new email (leave blank to keep current): ");
                
                if (!firstName.empty()) client->setFirstName(firstName);
                if (!lastName.empty()) client->setLastName(lastName);
                if (!email.empty()) client->setEmail(email);
                
                string costInput = getStringInput("Enter new subscription cost (leave blank to keep current): ");
                if (!costInput.empty()) {
                    try {
                        double cost = stod(costInput);
                        client->setSubscription(cost);
                    } catch (const exception& e) {
                        cout << "Invalid cost input. Keeping current cost." << endl;
                    }
                }
                
                cout << "Client updated successfully." << endl;
                cout << "Updated information:" << endl;
                cout << *client << endl;
                break;
            }
            case 4: {
                // Assign trainer to client
                int clientId = getIntInput("Enter client ID: ");
                
                // Display available trainers
                cout << "Available trainers:" << endl;
                for (const auto& trainer : crm.getTrainers()) {
                    cout << "ID " << trainer->getID() << ": " 
                         << trainer->getFirstName() << " " << trainer->getLastName() << endl;
                }
                
                int trainerId = getIntInput("Enter trainer ID to assign (or -1 to remove trainer): ");
                
                if (trainerId == -1) {
                    auto client = crm.getClient(clientId);
                    if (client) {
                        client->setPersonalTrainer(-1);
                        cout << "Trainer removed from client." << endl;
                    } else {
                        cout << "Client not found." << endl;
                    }
                } else if (crm.assignTrainerToClient(clientId, trainerId)) {
                    cout << "Trainer assigned to client successfully." << endl;
                } else {
                    cout << "Failed to assign trainer. Check client and trainer IDs." << endl;
                }
                break;
            }
            case 5: {
                // Record client attendance
                int clientId = getIntInput("Enter client ID: ");
                
                auto client = crm.getClient(clientId);
                if (!client) {
                    cout << "Client not found." << endl;
                    break;
                }
                
                time_t currentTime = time(nullptr);
                client->recordAttendance(currentTime);
                
                cout << "Attendance recorded for client " << client->getFirstName() 
                     << " " << client->getLastName() << " at " << ctime(&currentTime);
                break;
            }
            case 6: {
                // Enroll client in class
                int clientId = getIntInput("Enter client ID: ");
                
                auto client = crm.getClient(clientId);
                if (!client) {
                    cout << "Client not found." << endl;
                    break;
                }
                
                // Display available classes
                cout << "Available classes:" << endl;
                for (size_t i = 0; i < classes.size(); ++i) {
                    cout << i+1 << ". " << classes[i]->getClassName() 
                         << " (ID: " << classes[i]->getClassID() << ")" 
                         << " - " << classes[i]->getFormattedStartTime() << endl;
                }
                
                int classIndex = getIntInput("Enter class number to enroll in (1-" + to_string(classes.size()) + "): ");
                
                if (classIndex < 1 || classIndex > static_cast<int>(classes.size())) {
                    cout << "Invalid class number." << endl;
                    break;
                }
                
                auto selectedClass = classes[classIndex-1];
                
                if (selectedClass->enrollClient(clientId)) {
                    client->addEnrolledClass(selectedClass->getClassID());
                    cout << "Client enrolled in " << selectedClass->getClassName() << " successfully." << endl;
                } else {
                    cout << "Failed to enroll client. Class may be full or client already enrolled." << endl;
                }
                break;
            }
            case 7:
                back = true;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void handleTrainerManagement(FitnessCRM& crm) {
    bool back = false;
    
    while (!back) {
        cout << "\n--- Trainer Management ---" << endl;
        cout << "1. Display All Trainers" << endl;
        cout << "2. Add New Trainer" << endl;
        cout << "3. Update Trainer Information" << endl;
        cout << "4. Add Bonus to Trainer" << endl;
        cout << "5. Back to Main Menu" << endl;
        
        int choice = getIntInput("Enter your choice (1-5): ");
        
        switch (choice) {
            case 1: {
                // Display all trainers
                crm.displayAllTrainers();
                break;
            }
            case 2: {
                // Add new trainer
                int id = getIntInput("Enter trainer ID: ");
                clearInputBuffer();
                string firstName = getStringInput("Enter first name: ");
                string lastName = getStringInput("Enter last name: ");
                string email = getStringInput("Enter email: ");
                double salary = getDoubleInput("Enter salary: $");
                
                Trainer newTrainer(id, firstName, lastName, email, salary);
                
                if (crm.addTrainer(newTrainer)) {
                    cout << "Trainer added successfully." << endl;
                } else {
                    cout << "Failed to add trainer. ID may already exist." << endl;
                }
                break;
            }
            case 3: {
                // Update trainer information
                int id = getIntInput("Enter ID of trainer to update: ");
                
                auto trainer = crm.getTrainer(id);
                if (!trainer) {
                    cout << "Trainer not found." << endl;
                    break;
                }
                
                cout << "Current trainer information:" << endl;
                cout << *trainer << endl;
                
                clearInputBuffer();
                string firstName = getStringInput("Enter new first name (leave blank to keep current): ");
                string lastName = getStringInput("Enter new last name (leave blank to keep current): ");
                string email = getStringInput("Enter new email (leave blank to keep current): ");
                
                if (!firstName.empty()) trainer->setFirstName(firstName);
                if (!lastName.empty()) trainer->setLastName(lastName);
                if (!email.empty()) trainer->setEmail(email);
                
                string salaryInput = getStringInput("Enter new salary (leave blank to keep current): ");
                if (!salaryInput.empty()) {
                    try {
                        double salary = stod(salaryInput);
                        trainer->setsalary(salary);
                    } catch (const exception& e) {
                        cout << "Invalid salary input. Keeping current salary." << endl;
                    }
                }
                
                cout << "Trainer updated successfully." << endl;
                cout << "Updated information:" << endl;
                cout << *trainer << endl;
                break;
            }
            case 4: {
                // Add bonus to trainer
                int id = getIntInput("Enter ID of trainer to add bonus: ");
                
                auto trainer = crm.getTrainer(id);
                if (!trainer) {
                    cout << "Trainer not found." << endl;
                    break;
                }
                
                double bonus = getDoubleInput("Enter bonus amount: $");
                
                trainer->addBonus(bonus);
                cout << "Bonus of $" << fixed << setprecision(2) << bonus 
                     << " added to trainer " << trainer->getFirstName() << " " << trainer->getLastName() << endl;
                cout << "New salary: $" << fixed << setprecision(2) << trainer->getsalary() << endl;
                break;
            }
            case 5:
                back = true;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void handleClassManagement(FitnessCRM& crm) {
    bool back = false;
    
    while (!back) {
        cout << "\n--- Class Management ---" << endl;
        cout << "1. Display All Classes" << endl;
        cout << "2. Add New Class" << endl;
        cout << "3. Update Class Information" << endl;
        cout << "4. View Class Enrollments" << endl;
        cout << "5. Remove Client from Class" << endl;
        cout << "6. Back to Main Menu" << endl;
        
        int choice = getIntInput("Enter your choice (1-6): ");
        
        switch (choice) {
            case 1: {
                // Display all classes
                cout << "\n--- All Classes ---" << endl;
                for (const auto& cls : classes) {
                    cout << *cls << endl;
                }
                break;
            }
            case 2: {
                // Add new class
                int id = getIntInput("Enter class ID: ");
                clearInputBuffer();
                string name = getStringInput("Enter class name: ");
                string description = getStringInput("Enter class description: ");
                
                cout << "Enter start date and time:" << endl;
                int startYear = getIntInput("Year: ");
                int startMonth = getIntInput("Month (1-12): ");
                int startDay = getIntInput("Day: ");
                int startHour = getIntInput("Hour (0-23): ");
                int startMin = getIntInput("Minute: ");
                
                cout << "Enter end date and time:" << endl;
                int endYear = getIntInput("Year: ");
                int endMonth = getIntInput("Month (1-12): ");
                int endDay = getIntInput("Day: ");
                int endHour = getIntInput("Hour (0-23): ");
                int endMin = getIntInput("Minute: ");
                
                time_t startTime = createDateTime(startYear, startMonth, startDay, startHour, startMin);
                time_t endTime = createDateTime(endYear, endMonth, endDay, endHour, endMin);
                
                int capacity = getIntInput("Enter class capacity: ");
                
                // Display available trainers
                cout << "Available trainers:" << endl;
                for (const auto& trainer : crm.getTrainers()) {
                    cout << "ID " << trainer->getID() << ": " 
                         << trainer->getFirstName() << " " << trainer->getLastName() << endl;
                }
                
                int trainerId = getIntInput("Enter trainer ID for this class: ");
                
                try {
                    auto newClass = make_shared<Class>(id, name, description, startTime, endTime, capacity, trainerId);
                    classes.push_back(newClass);
                    cout << "Class added successfully." << endl;
                } catch (const exception& e) {
                    cout << "Failed to add class: " << e.what() << endl;
                }
                break;
            }
            case 3: {
                // Update class information
                cout << "Available classes:" << endl;
                for (size_t i = 0; i < classes.size(); ++i) {
                    cout << i+1 << ". " << classes[i]->getClassName() 
                         << " (ID: " << classes[i]->getClassID() << ")" << endl;
                }
                
                int classIndex = getIntInput("Enter class number to update (1-" + to_string(classes.size()) + "): ");
                
                if (classIndex < 1 || classIndex > static_cast<int>(classes.size())) {
                    cout << "Invalid class number." << endl;
                    break;
                }
                
                auto selectedClass = classes[classIndex-1];
                
                cout << "Current class information:" << endl;
                cout << *selectedClass << endl;
                
                clearInputBuffer();
                string name = getStringInput("Enter new class name (leave blank to keep current): ");
                string description = getStringInput("Enter new class description (leave blank to keep current): ");
                
                if (!name.empty()) selectedClass->setClassName(name);
                if (!description.empty()) selectedClass->setDescription(description);
                
                string capacityInput = getStringInput("Enter new capacity (leave blank to keep current): ");
                if (!capacityInput.empty()) {
                    try {
                        int capacity = stoi(capacityInput);
                        selectedClass->setCapacity(capacity);
                    } catch (const exception& e) {
                        cout << "Invalid capacity input or new capacity too small. Keeping current capacity." << endl;
                    }
                }
                
                cout << "Class updated successfully." << endl;
                cout << "Updated information:" << endl;
                cout << *selectedClass << endl;
                break;
            }
            case 4: {
                // View class enrollments
                cout << "Available classes:" << endl;
                for (size_t i = 0; i < classes.size(); ++i) {
                    cout << i+1 << ". " << classes[i]->getClassName() 
                         << " (ID: " << classes[i]->getClassID() << ")" << endl;
                }
                
                int classIndex = getIntInput("Enter class number to view enrollments (1-" + to_string(classes.size()) + "): ");
                
                if (classIndex < 1 || classIndex > static_cast<int>(classes.size())) {
                    cout << "Invalid class number." << endl;
                    break;
                }
                
                auto selectedClass = classes[classIndex-1];
                
                cout << "\n--- Enrollments for " << selectedClass->getClassName() << " ---" << endl;
                cout << "Current enrollment: " << selectedClass->getEnrollmentCount() 
                     << "/" << selectedClass->getCapacity() << endl;
                
                const auto& enrolledClients = selectedClass->getEnrolledClients();
                
                if (enrolledClients.empty()) {
                    cout << "No clients enrolled in this class." << endl;
                } else {
                    cout << "Enrolled clients:" << endl;
                    for (int clientId : enrolledClients) {
                        auto client = crm.getClient(clientId);
                        if (client) {
                            cout << "ID " << client->getID() << ": " 
                                 << client->getFirstName() << " " << client->getLastName() << endl;
                        } else {
                            cout << "ID " << clientId << ": Unknown client" << endl;
                        }
                    }
                }
                break;
            }
            case 5: {
                // Remove client from class
                cout << "Available classes:" << endl;
                for (size_t i = 0; i < classes.size(); ++i) {
                    cout << i+1 << ". " << classes[i]->getClassName() 
                         << " (ID: " << classes[i]->getClassID() << ")" << endl;
                }
                
                int classIndex = getIntInput("Enter class number (1-" + to_string(classes.size()) + "): ");
                
                if (classIndex < 1 || classIndex > static_cast<int>(classes.size())) {
                    cout << "Invalid class number." << endl;
                    break;
                }
                
                auto selectedClass = classes[classIndex-1];
                
                int clientId = getIntInput("Enter client ID to remove from class: ");
                
                auto client = crm.getClient(clientId);
                if (!client) {
                    cout << "Client not found." << endl;
                    break;
                }
                
                if (selectedClass->removeClient(clientId)) {
                    client->removeEnrolledClass(selectedClass->getClassID());
                    cout << "Client removed from class successfully." << endl;
                } else {
                    cout << "Client not enrolled in this class." << endl;
                }
                break;
            }
            case 6:
                back = true;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void handleMembershipManagement(FitnessCRM& crm) {
    bool back = false;
    
    while (!back) {
        cout << "\n--- Membership Plan Management ---" << endl;
        cout << "1. Display All Membership Plans" << endl;
        cout << "2. Add New Membership Plan" << endl;
        cout << "3. Update Membership Plan" << endl;
        cout << "4. Assign Membership Plan to Client" << endl;
        cout << "5. Back to Main Menu" << endl;
        
        int choice = getIntInput("Enter your choice (1-5): ");
        
        switch (choice) {
            case 1: {
                // Display all membership plans
                cout << "\n--- All Membership Plans ---" << endl;
                for (const auto& plan : membershipPlans) {
                    cout << *plan << endl;
                }
                break;
            }
            case 2: {
                // Add new membership plan
                int id = getIntInput("Enter plan ID: ");
                clearInputBuffer();
                string name = getStringInput("Enter plan name: ");
                string description = getStringInput("Enter plan description: ");
                double monthlyCost = getDoubleInput("Enter monthly cost: $");
                int duration = getIntInput("Enter duration in months: ");
                
                char includesClasses;
                cout << "Does this plan include classes? (y/n): ";
                cin >> includesClasses;
                clearInputBuffer();
                bool hasClasses = (tolower(includesClasses) == 'y');
                
                int classesPerMonth = 0;
                if (hasClasses) {
                    classesPerMonth = getIntInput("Enter number of classes per month: ");
                }
                
                char includesTraining;
                cout << "Does this plan include personal training? (y/n): ";
                cin >> includesTraining;
                clearInputBuffer();
                bool hasTraining = (tolower(includesTraining) == 'y');
                
                int trainingSessions = 0;
                if (hasTraining) {
                    trainingSessions = getIntInput("Enter number of personal training sessions per month: ");
                }
                
                try {
                    auto newPlan = make_shared<MembershipPlan>(
                        id, name, description, monthlyCost, duration, 
                        hasClasses, hasTraining, classesPerMonth, trainingSessions);
                    
                    membershipPlans.push_back(newPlan);
                    cout << "Membership plan added successfully." << endl;
                } catch (const exception& e) {
                    cout << "Failed to add membership plan: " << e.what() << endl;
                }
                break;
            }
            case 3: {
                // Update membership plan
                cout << "Available membership plans:" << endl;
                for (size_t i = 0; i < membershipPlans.size(); ++i) {
                    cout << i+1 << ". " << membershipPlans[i]->getName() 
                         << " (ID: " << membershipPlans[i]->getPlanID() << ")" << endl;
                }
                
                int planIndex = getIntInput("Enter plan number to update (1-" + to_string(membershipPlans.size()) + "): ");
                
                if (planIndex < 1 || planIndex > static_cast<int>(membershipPlans.size())) {
                    cout << "Invalid plan number." << endl;
                    break;
                }
                
                auto selectedPlan = membershipPlans[planIndex-1];
                
                cout << "Current plan information:" << endl;
                cout << *selectedPlan << endl;
                
                clearInputBuffer();
                string name = getStringInput("Enter new plan name (leave blank to keep current): ");
                string description = getStringInput("Enter new plan description (leave blank to keep current): ");
                
                if (!name.empty()) selectedPlan->setName(name);
                if (!description.empty()) selectedPlan->setDescription(description);
                
                string costInput = getStringInput("Enter new monthly cost (leave blank to keep current): ");
                if (!costInput.empty()) {
                    try {
                        double cost = stod(costInput);
                        selectedPlan->setMonthlyCost(cost);
                    } catch (const exception& e) {
                        cout << "Invalid cost input. Keeping current cost." << endl;
                    }
                }
                
                string durationInput = getStringInput("Enter new duration in months (leave blank to keep current): ");
                if (!durationInput.empty()) {
                    try {
                        int duration = stoi(durationInput);
                        selectedPlan->setDurationMonths(duration);
                    } catch (const exception& e) {
                        cout << "Invalid duration input. Keeping current duration." << endl;
                    }
                }
                
                cout << "Plan updated successfully." << endl;
                cout << "Updated information:" << endl;
                cout << *selectedPlan << endl;
                break;
            }
            case 4: {
                // Assign membership plan to client
                int clientId = getIntInput("Enter client ID: ");
                
                auto client = crm.getClient(clientId);
                if (!client) {
                    cout << "Client not found." << endl;
                    break;
                }
                
                // Display available membership plans
                cout << "Available membership plans:" << endl;
                cout << "0. No membership (remove current plan)" << endl;
                for (const auto& plan : membershipPlans) {
                    cout << plan->getPlanID() << ". " << plan->getName() 
                         << " - $" << plan->getMonthlyCost() << "/month" << endl;
                }
                
                int planId = getIntInput("Enter membership plan ID (0 for none): ");
                
                if (planId == 0) {
                    client->setMembershipPlanID(-1);
                    cout << "Membership plan removed from client." << endl;
                } else {
                    // Find the selected plan
                    bool planFound = false;
                    for (const auto& plan : membershipPlans) {
                        if (plan->getPlanID() == planId) {
                            planFound = true;
                            client->setMembershipPlanID(planId);
                            client->setSubscription(plan->getMonthlyCost());
                            
                            // Create a transaction for the new membership
                            crm.createTransaction(Transaction(
                                time(nullptr),  // Use current time as transaction ID
                                client->getID(),
                                plan->getMonthlyCost(),
                                "Membership",
                                plan->getName() + " membership plan",
                                time(nullptr),
                                crm.getCurrentUser()->getID()
                            ));
                            
                            cout << "Membership plan assigned to client successfully." << endl;
                            cout << "Client will be charged $" << fixed << setprecision(2) 
                                 << plan->getMonthlyCost() << " per month." << endl;
                            break;
                        }
                    }
                    
                    if (!planFound) {
                        cout << "Invalid plan ID. No changes made." << endl;
                    }
                }
                break;
            }
            case 5:
                back = true;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void handleTransactionManagement(FitnessCRM& crm) {
    bool back = false;
    
    while (!back) {
        cout << "\n--- Transaction Management ---" << endl;
        cout << "1. Display All Transactions" << endl;
        cout << "2. Create New Transaction" << endl;
        cout << "3. View Transactions for a Client" << endl;
        cout << "4. View Transactions by Date Range" << endl;
        cout << "5. Back to Main Menu" << endl;
        
        int choice = getIntInput("Enter your choice (1-5): ");
        
        switch (choice) {
            case 1: {
                // Display all transactions
                crm.displayAllTransactions();
                break;
            }
            case 2: {
                // Create new transaction
                // First, select a client
                cout << "Available clients:" << endl;
                for (const auto& client : crm.getClients()) {
                    cout << "ID " << client->getID() << ": " 
                         << client->getFirstName() << " " << client->getLastName() << endl;
                }
                
                int clientId = getIntInput("Enter client ID: ");
                
                auto client = crm.getClient(clientId);
                if (!client) {
                    cout << "Client not found." << endl;
                    break;
                }
                
                double amount = getDoubleInput("Enter transaction amount: $");
                
                cout << "Available transaction types:" << endl;
                cout << "1. Membership" << endl;
                cout << "2. Class" << endl;
                cout << "3. Personal Training" << endl;
                cout << "4. Day Pass" << endl;
                cout << "5. Other" << endl;
                
                int typeChoice = getIntInput("Enter transaction type (1-5): ");
                string type;
                
                switch (typeChoice) {
                    case 1: type = "Membership"; break;
                    case 2: type = "Class"; break;
                    case 3: type = "Personal Training"; break;
                    case 4: type = "Day Pass"; break;
                    case 5: type = "Other"; break;
                    default: type = "Other";
                }
                
                clearInputBuffer();
                string description = getStringInput("Enter transaction description: ");
                
                Transaction newTransaction(
                    time(nullptr),  // Use current time as transaction ID
                    clientId,
                    amount,
                    type,
                    description,
                    time(nullptr),
                    crm.getCurrentUser()->getID()
                );
                
                if (crm.createTransaction(newTransaction)) {
                    cout << "Transaction created successfully." << endl;
                    
                    // If it's a day pass, update the client's cost
                    if (type == "Day Pass") {
                        client->DayPass(amount);
                        cout << "Day pass fee added to client's total cost." << endl;
                    }
                } else {
                    cout << "Failed to create transaction." << endl;
                }
                break;
            }
            case 3: {
                // View transactions for a client
                int clientId = getIntInput("Enter client ID: ");
                
                auto client = crm.getClient(clientId);
                if (!client) {
                    cout << "Client not found." << endl;
                    break;
                }
                
                auto transactions = crm.getTransactionsForClient(clientId);
                
                cout << "\n--- Transactions for " << client->getFirstName() 
                     << " " << client->getLastName() << " ---" << endl;
                
                if (transactions.empty()) {
                    cout << "No transactions found for this client." << endl;
                } else {
                    double total = 0.0;
                    for (const auto& transaction : transactions) {
                        cout << *transaction << endl;
                        total += transaction->getAmount();
                    }
                    cout << "Total amount spent: $" << fixed << setprecision(2) << total << endl;
                }
                break;
            }
            case 4: {
                // View transactions by date range
                cout << "Enter start date:" << endl;
                int startYear = getIntInput("Year: ");
                int startMonth = getIntInput("Month (1-12): ");
                int startDay = getIntInput("Day: ");
                
                cout << "Enter end date:" << endl;
                int endYear = getIntInput("Year: ");
                int endMonth = getIntInput("Month (1-12): ");
                int endDay = getIntInput("Day: ");
                
                time_t startDate = createDateTime(startYear, startMonth, startDay, 0, 0);
                time_t endDate = createDateTime(endYear, endMonth, endDay, 23, 59);
                
                auto transactions = crm.getTransactionsByDateRange(startDate, endDate);
                
                cout << "\n--- Transactions from " << ctime(&startDate) 
                     << " to " << ctime(&endDate) << " ---" << endl;
                
                if (transactions.empty()) {
                    cout << "No transactions found in this date range." << endl;
                } else {
                    double total = 0.0;
                    for (const auto& transaction : transactions) {
                        cout << *transaction << endl;
                        total += transaction->getAmount();
                    }
                    cout << "Total amount: $" << fixed << setprecision(2) << total << endl;
                }
                break;
            }
            case 5:
                back = true;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}


Fitness Club Management System

A comprehensive C++ application for managing fitness club operations, including client memberships, trainer assignments, class scheduling, and financial transactions.

Overview

The Fitness Club Management System is a console-based CRM (Customer Relationship Management) application designed to streamline the administration of fitness clubs. It provides tools for managing users, clients, trainers, classes, membership plans, and transactions with persistent data storage.

Features

User Management
- Support for multiple user types: Users, Clients, Trainers, and Cashiers
- User authentication with ID and email
- Role-based functionality through inheritance hierarchy
- Add, remove, and display users

Client Management
- Client profiles with membership details
- Attendance tracking
- Class enrollment management
- Personal trainer assignment
- Membership status monitoring (active/inactive)
- Multiple sorting options (by name, ID, or fee)

Trainer Management
- Trainer profiles with salary information
- Bonus/salary adjustment capabilities
- Client assignment tracking
- Performance reporting

Class Management
- Class scheduling with start and end times
- Capacity management
- Client enrollment/removal
- Trainer assignment
- Real-time availability tracking

Membership Plans
- Flexible membership plan creation
- Multiple plan tiers (Basic, Standard, Premium)
- Customizable features (classes, personal training)
- Duration and cost management

Transaction Management
- Transaction recording for all financial activities
- Multiple transaction types (Membership, Classes, Personal Training, Day Pass)
- Date range filtering
- Client-specific transaction history
- Automated financial reporting

Reporting System
- Financial reports with revenue breakdown
- Monthly revenue analysis
- Trainer performance reports
- Revenue tracking by transaction type

System Architecture

Class Hierarchy

User (base class)
├── Client
├── Trainer
└── Cashier

Additional Classes:
- Class (fitness classes)
- MembershipPlan
- Transaction
- FitnessCRM (main system controller)

Key Design Patterns
- Inheritance: User base class with specialized derived classes
- Composition: FitnessCRM aggregates multiple entity types
- Smart Pointers: Used throughout for memory management
- Template Functions: Generic search functionality with predicates

Technical Requirements

Compiler
- C++11 or later
- Standard Template Library (STL)

Dependencies
- `<iostream>` - Input/output operations
- `<vector>` - Dynamic arrays
- `<memory>` - Smart pointers
- `<ctime>` - Date/time handling
- `<fstream>` - File operations
- `<algorithm>` - STL algorithms
- `<functional>` - Function objects

Installation & Compilation

Compilation
```bash
g++ -std= c++11 -o fitness_crm main.cpp User.cpp Client.cpp Trainer.cpp Cashier.cpp Class.cpp MembershipPlan.cpp Transaction.cpp FitnessCRM.cpp
```
Running the Application
```bash
./fitness_crm
```
Usage

Initial Login
The system comes with sample data pre-loaded. Default login credentials:
- Admin: ID: 1001, Email: admin@example.com
- Trainer 1: ID: 2001, Email: john@example.com
- Client 1: ID: 3001, Email: alice@example.com

Main Menu Options

1. User Management
   - Display all users
   - Add new users
   - Remove users

2. Client Management
   - View all clients
   - Add/update client information
   - Assign trainers
   - Record attendance
   - Enroll in classes

3. Trainer Management
   - View all trainers
   - Add/update trainer information
   - Manage salaries and bonuses

4. Class Management
   - View class schedules
   - Create new classes
   - Manage enrollments
   - Update class details

5. Membership Plan Management
   - View available plans
   - Create custom plans
   - Assign plans to clients

6. Transaction Management
   - Record transactions
   - View transaction history
   - Generate financial reports

 Data Persistence

The system automatically saves and loads data from two files:
- `users.dat` - Stores all user information (Users, Clients, Trainers, Cashiers)
- `transactions.dat` - Stores transaction records

Data is saved automatically when the application exits and loaded on startup.

Sample Data

The system initializes with:
- 1 Admin user
- 2 Trainers
- 3 Clients with various membership plans
- 1 Cashier
- 3 Membership plans (Basic, Standard, Premium)
- 2 Fitness classes
- Multiple sample transactions

Key Functions

Search Functionality
Generic template-based search with custom predicates:
```cpp
template<typename T>\
std::vector<std::shared_ptr<T>> search(\
    const std::vector<std::shared_ptr<T>>& collection,\
    Predicate<T> predicate,\
    const std::string& searchTerm)\
```
Sorting Options
- Sort clients by name (alphabetical)
- Sort clients by ID (numerical)
- Sort clients by fee (cost-based)

Error Handling

The system includes comprehensive error handling for:
- Invalid input validation
- Negative value prevention (costs, salaries)
- Date/time validation
- Capacity checks for classes
- Duplicate ID prevention
- File I/O error handling

Future Enhancements

Potential areas for expansion:
- Graphical user interface (GUI)
- Database integration (SQL)
- Email notifications
- Payment processing integration
- Mobile app companion
- Advanced reporting with charts
- Equipment inventory management
- Nutrition tracking features



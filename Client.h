#ifndef CLIENT_H
#define CLIENT_H

using namespace std;
#include "User.h"
#include <string>
#include <vector>
#include <ctime>
#include <memory>

class MembershipPlan;

class Client : public User {

    public:

    // Stream operators as friend functions
    friend ostream &operator<<(ostream &, const Client &);
    friend istream &operator>>(istream &, Client &);

    // Constructor 
    Client(const int ID, const string &FirstName, const string &LastName, const string &email, 
        double cost = 0.0, int membershipPlanID = -1);

    // Financial methods    
    void setSubscription(double Subscription);
    double getCost() const;
    void DayPass(double dayCost);

    //Membership plan methods
    void setMembershipPlanID(int planID);
    int getMembershipPlanID() const;
    std::time_t getMembershipStartDate() const;
    std::time_t getMembershipEndDate() const;
    void setMembershipStartDate(std::time_t startDate);
    void setMembershipEndDate(std::time_t endDate);
    bool isMembershipActive() const;


    // Class and trainer relationships
    void addEnrolledClass(int classID);
    void removeEnrolledClass(int classID);
    const std::vector<int>& getEnrolledClasses() const;
    bool isEnrolledInClass(int classID) const;

    void setPersonalTrainer(int trainerID);
    int getPersonalTrainer() const;

    // attendance tracking
    void recordAttendance(std::time_t date);
    std::vector<std::time_t> getAttendanceHistory() const;

    string getRole() const override {
        return "Client";
    }

    protected:
    double cost;

    private:

    //membership information
    int membershipPlanID;
    std::time_t membershipStartDate;
    std::time_t membershipEndDate;

    //Relationships
    std::vector<int> enrolledClasses;
    int personalTrainerID;

    //Attendance 
    std::vector <std::time_t> attendanceHistory;
    
};

#endif
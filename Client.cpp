#include "Client.h"
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <ctime>

using namespace std;

//constructor
Client::Client(const int ID, const string& FirstName, const string& LastName, const string& email,
     double cost, int membershipPlanID)

    :User (ID, FirstName, LastName, email),
    cost(cost), membershipPlanID(membershipPlanID), personalTrainerID(-1){

        if (membershipPlanID >= 0) {
            membershipStartDate = std::time(nullptr);
            // membership starts at 1 month
            membershipEndDate = membershipStartDate + (30 * 24 * 60 * 60); // 30 days in seconds
        } else {
            membershipStartDate = 0;
            membershipEndDate = 0;
        }

    }
    
    void Client::setSubscription (double SubscriptionCost){
        if(SubscriptionCost < 0.0){
            throw invalid_argument("Subscription cost can't be negative");
        }
        cost=SubscriptionCost;
    }

    void Client::DayPass(double dayCost){
        if(dayCost < 0.0){
            throw invalid_argument("Day pass cost can't be negative");
        }
        cost+=dayCost;
    }

    double Client::getCost() const{
        return cost;
    }

    void Client::setMembershipPlanID(int planID) {
        membershipPlanID = planID;
        if (planID >= 0) {
            //Reset membership date
            membershipStartDate = std::time(nullptr);

            membershipEndDate = membershipStartDate + (30 * 24 * 60 * 60);
        }
    }

    int Client::getMembershipPlanID() const {
        return membershipPlanID;
    }

    std::time_t Client::getMembershipStartDate() const {
        return membershipStartDate;
    }
 
    void Client::setMembershipStartDate(std::time_t startDate){
        membershipStartDate = startDate;
    }

    std::time_t Client::getMembershipEndDate() const {
        return membershipEndDate;
    }

    void Client::setMembershipEndDate(std::time_t endDate){
        membershipEndDate = endDate;
    }

    bool Client::isMembershipActive() const {
        // The membership is active when the current time is before the end date and after the start date
        std::time_t currentTime = std::time(nullptr);
        return (membershipPlanID >= 0 && currentTime >= membershipStartDate && currentTime <= membershipEndDate);
    }

    void Client::addEnrolledClass(int classID) {
        // check if enrolled
        for (int id : enrolledClasses) {
            if (id == classID) {
                return;
            }
        }

        enrolledClasses.push_back(classID);
    }

    void Client::removeEnrolledClass(int classID) {
        for (auto it = enrolledClasses.begin(); it != enrolledClasses.end(); ++it) {
            if (*it == classID) {
                enrolledClasses.erase(it);
                return;
            }
        }
    }

    const std::vector<int>& Client::getEnrolledClasses() const {
        return enrolledClasses;
    }

    
    bool Client::isEnrolledInClass(int classID) const {
        for(int id : enrolledClasses){
            if (id == classID) {
                return true;
            }
        }
        return false;
    }

    void Client::setPersonalTrainer(int trainerID){
        personalTrainerID = trainerID;
    }

    int Client::getPersonalTrainer() const {
        return personalTrainerID;
    }

    void Client::recordAttendance(std::time_t date) {
        attendanceHistory.push_back(date);
    }

    std::vector<std::time_t> Client::getAttendanceHistory() const {
        return attendanceHistory;
    }

   // Stream operators implementation
    ostream& operator<<(ostream& output, const Client& client) {

        // Output base class information
        output << static_cast<const User&>(client);
        
        // the output clients information
        output << "Cost: $" << fixed << setprecision(2) << client.getCost() << endl;
        output << "Membership Plan ID: " << client.getMembershipPlanID() << endl;
        
        if (client.isMembershipActive()) {
            output << "Membership Status: Active" << endl;
            
            // Format dates
            char startBuffer[80];
            char endBuffer[80];
            struct tm* timeinfo;
            
            std::time_t startDate = client.getMembershipStartDate();
            timeinfo = localtime(&startDate);
            strftime(startBuffer, 80, "%Y-%m-%d", timeinfo);
            
            std::time_t endDate = client.getMembershipEndDate();
            timeinfo = localtime(&endDate);
            strftime(endBuffer, 80, "%Y-%m-%d", timeinfo);
            
            output << "Start Date: " << startBuffer << endl;
            output << "End Date: " << endBuffer << endl;
        } else {
            output << "Membership Status: Inactive" << endl;
        }
        
        // Enrolled classes
        output << "Enrolled Classes: ";
        const auto& enrolledClasses = client.getEnrolledClasses();
        if (enrolledClasses.empty()) {
            output << "None";
        } else {
            for (size_t i = 0; i < enrolledClasses.size(); ++i) {
                if (i > 0) output << ", ";
                output << enrolledClasses[i];
            }
        }
        output << endl;
        
        // Personal trainer
        output << "Personal Trainer ID: " << (client.getPersonalTrainer() >= 0 ? 
                                to_string(client.getPersonalTrainer()) : "None") << endl;
        
        // Attendance history
        output << "Number of Visits: " << client.getAttendanceHistory().size() << endl;
        
        return output;
    }
    


    istream& operator>>(istream& input, Client& client) {
    
        // Input base class information
        input >> static_cast<User&>(client);

        // Input Client-specific information    
        double cost;
        cout << "Enter Cost: $";
        input >> cost;
        client.setSubscription(cost);    

        int membershipPlanID;    
        cout << "Enter Membership Plan ID (-1 for none): ";
        input >> membershipPlanID;
        client.setMembershipPlanID(membershipPlanID);
    
        return input;

    }

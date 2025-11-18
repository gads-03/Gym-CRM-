#include "Class.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
using namespace std;


Class::Class(int id, const string & name, const string & desc, time_t start, time_t end, 
    int cap, int trainer)
    : classID(id), className(name), description(desc), startTime(start), endTime(end), capacity(cap),trainerID(trainer){

        if (cap < 1) {
            throw invalid_argument("Class capacity must be at least 1");
        }
        if (end <= start){

            throw invalid_argument("End time must be after start time");

        }

    }

    // getters
    int Class::getClassID() const {
        return classID;
    }

    string Class::getClassName() const {
        return className;
    }

    string Class::getDescription() const {
        return description;
    }

    time_t Class::getStartTime() const {
        return startTime;
    }

    time_t Class::getEndTime() const {
        return endTime;
    }

    int Class::getCapacity() const {
        return capacity;
    }

    int Class::getTrainerID() const {
        return trainerID;
    }

    const vector<int> & Class::getEnrolledClients() const {
        return enrolledClients;
    }

    //Setters
    void Class::setClassName(const string & name) {
        className = name;
    }

    void Class::setDescription(const string & desc) {
        description = desc;
    }

    void Class::setStartTime(time_t start ){
        if (start >= endTime) {
            throw invalid_argument("Start time should be before end time");
        }
        startTime = start;
    }

    void Class::setEndTime(time_t end ) {
        if (end <= startTime) {
            throw invalid_argument("End time cannot be before the starting time");
        }
        endTime = end;
    }

    void Class::setCapacity(int cap) {
        if (cap < 1) {
            throw invalid_argument("Class capacity must be at least 1");
        }
        // static_cast implicitly conversion between different types 
        if(cap < static_cast<int>(enrolledClients.size())){
            throw invalid_argument("New capacity is less than currently enrolled");
        }
        capacity = cap;
    }

    void Class::setTrainerID(int trainer){
        trainerID = trainer;
    }

    // enrollment methods
    bool Class::enrollClient(int clientID){
        // if the class is full then you cannot enroll the client 
        if(isFull()) {
            return false;
        }
        if(isClientEnrolled(clientID)){
            return false; // enrolled already
        }

        enrolledClients.push_back(clientID);
        return true;
    }

    bool Class::removeClient(int clientID){
        // auto keyword allows any data type to be used whether it is int, string, etc..
        auto look = find(enrolledClients.begin(), enrolledClients.end(), clientID);
        if (look != enrolledClients.end()) {
            enrolledClients.erase(look);
            return true;
        }
        return false;
    }

    bool Class::isClientEnrolled(int clientID) const {
        return find(enrolledClients.begin(),enrolledClients.end(), clientID)
        != enrolledClients.end();
    }

    int Class::getEnrollmentCount() const {
        return static_cast<int>(enrolledClients.size());
    }

    bool Class::isFull() const {
        return getEnrollmentCount() >= capacity;
    }

    //utility methods
    string Class::getFormattedStartTime() const {
        char buffer[80];
        struct tm* timeinfo = localtime(&startTime);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", timeinfo);
        return string(buffer);
    }

    string Class::getFormattedEndTime() const {
        char buffer[80];
        struct tm* timeinfo = localtime(&endTime);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", timeinfo);
        return string(buffer);
    }

    ostream& operator<<(ostream& output, const Class& fitnessClass) {
        output << "Class ID: " << fitnessClass.classID << endl;
        output << "Name: " << fitnessClass.className << endl;
        output << "Description: " << fitnessClass.description << endl;
        output << "Start time: " << fitnessClass.getFormattedStartTime() << endl;
        output << "End time: " << fitnessClass.getFormattedEndTime() << endl;
        output << "Capacity: " << fitnessClass.capacity << endl;
        output << "Current Enrollment: " << fitnessClass.getEnrollmentCount() << "/" << fitnessClass.capacity << endl;
        output << "Trainer ID: " << fitnessClass.trainerID << endl;
        
        output << "Enrolled Clients: ";
        if (fitnessClass.enrolledClients.empty()) {
            output << "None";
        } else {
            for (size_t i = 0; i < fitnessClass.enrolledClients.size(); ++i) {
                if (i > 0) {
                    output << ", ";
                }
                output << fitnessClass.enrolledClients[i];
            }
        }
        output << endl;
        
        return output;
    }
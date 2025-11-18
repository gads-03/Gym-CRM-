#ifndef CLASS_H
#define CLASS_H

#include <string>
#include <vector>
#include <memory>
#include <ctime>

using namespace std;

class Trainer;
class Client;

class Class {
    private:

    int classID;
    string className;
    string description;
    time_t startTime;
    time_t endTime;
    int capacity;
    int trainerID;
    vector<int> enrolledClients;

    public:

    friend ostream& operator<<(ostream& output, const Class& fitnessClass);

    Class(int id, const string & name, const string & desc, time_t start, time_t end, int cap, int trainer);

    int getClassID() const;
    string getClassName() const;
    string getDescription() const;
    time_t getStartTime() const;
    time_t getEndTime() const;
    int getCapacity() const;
    int getTrainerID() const;
    const vector<int>& getEnrolledClients() const;

    void setClassName(const string& name);
    void setDescription(const string& desc);
    void setStartTime(time_t start);
    void setEndTime(time_t end);
    void setCapacity(int cap);
    void setTrainerID(int trainer);

    bool enrollClient(int clientID);
    bool removeClient(int clientID);
    bool isClientEnrolled(int clientID) const;
    int getEnrollmentCount() const;
    bool isFull() const;

    string getFormattedStartTime() const;
    string getFormattedEndTime() const;

};

#endif
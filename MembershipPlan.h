#ifndef MEMBERSHIP_PLAN_H
#define MEMBERSHIP_PLAN_H

#include <string>
#include <vector>
using namespace std;

class MembershipPlan {
    private:

    int planID;
    std::string name;
    std::string description;
    double monthlyCost;
    int durationMonths;
    bool includesClasses;
    bool includesPersonalTraining;
    int classesPerMonth;
    int personalTrainingSessionsPerMonth;
    
    public:

    friend ostream& operator<<(ostream& output, MembershipPlan& plan);

    // Constructor
    MembershipPlan(int id, const std::string& n, const std::string& desc, 
        double cost, int duration, bool classes, bool training, 
        int classCount, int trainingCount);

    // Getters
    int getPlanID() const;
    std::string getName() const;
    std::string getDescription() const;
    double getMonthlyCost() const;
    int getDurationMonths() const;
    bool getIncludesClasses() const;
    bool getIncludesPersonalTraining() const;
    int getClassesPerMonth() const;
    int getPersonalTrainingSessionsPerMonth() const;

    // Setters
    void setName(const std::string& n);
    void setDescription(const std::string& desc);
    void setMonthlyCost(double cost);
    void setDurationMonths(int duration);
    void setIncludesClasses(bool classes);
    void setIncludesPersonalTraining(bool training);
    void setClassesPerMonth(int classCount);
    void setPersonalTrainingSessionsPerMonth(int trainingCount);

    // Utility methods
    double getAnnualCost() const;
    std::string toString() const;
};

#endif // MEMBERSHIP_PLAN_H#ifndef MEMBERSHIP_PLAN_H






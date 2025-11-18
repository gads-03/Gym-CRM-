#include "MembershipPlan.h"
#include <sstream>
#include <iomanip>

// Constructor
MembershipPlan::MembershipPlan(int id, const std::string& n, const std::string& desc, 
                              double cost, int duration, bool classes, bool training, 
                              int classCount, int trainingCount)
    : planID(id), 
      name(n), 
      description(desc), 
      monthlyCost(cost), 
      durationMonths(duration), 
      includesClasses(classes), 
      includesPersonalTraining(training), 
      classesPerMonth(classCount), 
      personalTrainingSessionsPerMonth(trainingCount) {
          
    if (monthlyCost < 0.0) {
        throw std::invalid_argument("Monthly cost cannot be negative");
    }
    
    if (durationMonths < 1) {
        throw std::invalid_argument("Duration must be at least 1 month");
    }
    
    if (classesPerMonth < 0) {
        throw std::invalid_argument("Classes per month cannot be negative");
    }
    
    if (personalTrainingSessionsPerMonth < 0) {
        throw std::invalid_argument("Personal training sessions per month cannot be negative");
    }
}

// Getters
int MembershipPlan::getPlanID() const {
    return planID;
}

std::string MembershipPlan::getName() const {
    return name;
}

std::string MembershipPlan::getDescription() const {
    return description;
}

double MembershipPlan::getMonthlyCost() const {
    return monthlyCost;
}

int MembershipPlan::getDurationMonths() const {
    return durationMonths;
}

bool MembershipPlan::getIncludesClasses() const {
    return includesClasses;
}

bool MembershipPlan::getIncludesPersonalTraining() const {
    return includesPersonalTraining;
}

int MembershipPlan::getClassesPerMonth() const {
    return classesPerMonth;
}

int MembershipPlan::getPersonalTrainingSessionsPerMonth() const {
    return personalTrainingSessionsPerMonth;
}

// Setters
void MembershipPlan::setName(const std::string& n) {
    name = n;
}

void MembershipPlan::setDescription(const std::string& desc) {
    description = desc;
}

void MembershipPlan::setMonthlyCost(double cost) {
    if (cost < 0.0) {
        throw std::invalid_argument("Monthly cost cannot be negative");
    }
    monthlyCost = cost;
}

void MembershipPlan::setDurationMonths(int duration) {
    if (duration < 1) {
        throw std::invalid_argument("Duration must be at least 1 month");
    }
    durationMonths = duration;
}
void MembershipPlan::setIncludesClasses(bool classes) {
    includesClasses = classes;
}

void MembershipPlan::setIncludesPersonalTraining(bool training) {
    includesPersonalTraining = training;
}

void MembershipPlan::setClassesPerMonth(int classCount) {
    if (classCount < 0) {
        throw std::invalid_argument("Classes per month cannot be negative");
    }
    classesPerMonth = classCount;
}

void MembershipPlan::setPersonalTrainingSessionsPerMonth(int trainingCount) {
    if (trainingCount < 0) {
        throw std::invalid_argument("Personal training sessions per month cannot be negative");
    }
    personalTrainingSessionsPerMonth = trainingCount;
}

// Utility methods
double MembershipPlan::getAnnualCost() const {
    // Calculate the annual cost based on monthly cost
    // If duration is less than 12 months, prorate it
    return monthlyCost * std::min(durationMonths, 12);
}

ostream& operator<<(ostream& output, MembershipPlan& plan) {
    output << "Membership Plan ID: " << plan.planID << endl;
    output << "Name: " << plan.name << endl;
    output << "Description: " << plan.description << endl;
    output << "Monthly Cost: $" << fixed << setprecision(2) << plan.monthlyCost << endl;
    output << "Duration: " << plan.durationMonths << " months" << endl;
    output << "Includes Classes: " << (plan.includesClasses ? "Yes" : "No");
    
    if (plan.includesClasses) {
        output << " (" << plan.classesPerMonth << " per month)";
    }
    output << endl;
    
    output << "Includes Personal Training: " << (plan.includesPersonalTraining ? "Yes" : "No");
    if (plan.includesPersonalTraining) {
        output << " (" << plan.personalTrainingSessionsPerMonth << " per month)";
    }
    output << endl;
    
    output << "Annual Cost: $" << fixed << setprecision(2) << plan.getAnnualCost() << endl;
    
    return output;
}
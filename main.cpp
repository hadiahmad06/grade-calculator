#include <iostream>
#include <string>
#include <vector>
//#include "objects.h"

using namespace std;

class Layouts {
private:
    long nextId;

    Layouts() : nextId(0) {}
public:
    static Layouts& getInstance() {
        static Layouts instance;
        return instance;
    }

    long getNextId() {
        return nextId++;
    }
};

class Assignment {
private:
    string name;
    bool calculate;
    int max;
    int earned;

public:
    Assignment(string n, int m, bool c = true, int e = 0)
        : name(n), max(m), calculate(c), earned(e) {}

    void setEarned(int points) {
        earned = points;
    }

    float getPercentage() const {
        return (static_cast<float>(earned) / max) * 100;
    }

    void display() const {
        cout << "Assignment: " << name << ", Earned: " << earned << "/" << max << ", Percentage: " << getPercentage() << "%" << endl;
    }
};

class Section {
private:
    
    string name;
    float grade;
    float weight;
    bool include;
    vector<Assignment> assignments;

public:
    Section(string n, float w = -1, bool i = true) {
        name = n;
        weight = w;
        include = i;
        grade = 0;
    }

    void setInclude(bool value) {
        include = value;  // Set whether the section is contributing to total percentage
    }

    bool getInclude() const {
        return include;  // Return if the section contributes to the total percentage
    }
};

class Course {
private:
    long id;

public:
    string name;
    float grade;
    vector<Section> sections;  // Vector to hold sections

    Course() {
        id = Layouts::getInstance().getNextId(); 
        name = "Course" + to_string(id);
        grade = 100;
    }

    void addSection(string section) {
        sections.push_back(section);  // Add a section to the class
    }

    void display() {
        cout << name << " " << grade << "%" << endl;
        cout << "Sections: ";
        for (size_t i = 0; i < sections.size(); ++i) {
            cout << to_string(sections[i]) << " ";
        }       
        cout << endl;
    }
};





int main() {
    Course math;
    math.display();
    math.addSection("Tests");
}
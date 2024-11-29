#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

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
    bool include;
    float max;
    float earned;

public:
    Assignment(string n, float m, float e = 0, bool i = true)
        : name(n), max(m), include(i), earned(e) {}

    void setName(string n) { name = n; }
    string getName() { return name; }

    void setEarned(float e) { earned = e; }
    float getEarned() { return earned; }

    void setMax(float m) { max = m; }
    float getMax() { return max; }

    void setInclude(bool b) { include = b; }
    bool getInclude() { return include; }
    
    float getGrade() const { return ((earned) / max) * 100; }

    void display() const {
        cout << "(" + name + ") " << fixed << setprecision(1) << earned << "/" << fixed << setprecision(1) << max << " " << fixed << setprecision(2) << getGrade() << "% ";    }
};

class Section {
private:
    
    string name;
    float grade;
    float weight;
    bool include;
    vector<Assignment> assignments;
    int nextNum = 1;

public:
    Section(string n, float w = -1, bool i = true) 
        : name(n), weight(w), include(i), grade(0) {}

    void setName(string n) { name = n; }
    string getName() const { return name; }

    void setGrade(float g) { grade = g; }
    float getGrade() { 
        int sum = 0;
        float gradeSum = 0;
        for (int i = 0; i < assignments.size(); i++) {
            if (assignments[i].getInclude()) {
                gradeSum += assignments[i].getGrade();
                sum++;
            }
        }
        grade = gradeSum / sum;
        return grade;
    }

    void setWeight(float w) { weight = w; }
    float getWeight() { return weight; }

    void setInclude(bool value) { include = value; }
    bool getInclude() const { return include; }

    Assignment& newAssignmentDebug(string n, long e, long m = 100, bool i = 0) {
        assignments.emplace_back(n, e, m, i);
        nextNum++;
        return assignments.back();
    }
    void newAssignment() { 
        assignments.emplace_back("Assignment" + to_string(nextNum), 100, 0, true);
        nextNum++;
    }
    void removeAssignment(int i) {
        nextNum--;
        for (; i+1 < assignments.size(); i++) {
            assignments[i] = assignments[i+1];
        }
        assignments.pop_back();
    }

    Assignment getAssignment(int i) { return assignments[i]; }
    void setAssignment(int i, Assignment s) { assignments[i] = s; }

    void display() {
        for(int i = 0; i < assignments.size(); i++) {
            assignments[i].display();//cout << ("(" + assignments[i].getName() + ") " + to_string(assignments[i].getEarned()) + "/" + to_string(assignments[i].getMax()) + " " + to_string(assignments[i].getGrade()) + "% ");
        }
    }
};

class Course {
private:
    long id;

public:
    string name;
    float grade;
    vector<Section> sections;  // Vector to hold sections
    int nextNum = 1;

    Course() {
        id = Layouts::getInstance().getNextId(); 
        name = "Course" + to_string(id);
        grade = 100;
    }

    Section& addSectionDebug(string n, float w = 100, bool i = true) {
        sections.emplace_back(n, w, i);
        nextNum++;
        return sections.back();
    }
    void addSection() {
        sections.emplace_back("Section" + to_string(nextNum), 100, true);
        nextNum++;
    }
    void removeSection(int i) {
        nextNum--;
        for (; i+1 < sections.size(); i++) {
            sections[i] = sections[i+1];
        }
        sections.pop_back();
    }

    void display() {
        cout << name << " " << grade << "%" << endl;
        cout << "Sections: ";
        for (size_t i = 0; i < sections.size(); ++i) {
            cout << ("\n" + sections[i].getName() + ": ");
            sections[i].display();
        }       
        cout << endl;
    }
};





int main() {
    Course math;
    Section& s1 = math.addSectionDebug("Homework", 30);
    s1.newAssignmentDebug("HW1", 40, 10);
    s1.newAssignmentDebug("HW2", 20, 17);
    Section& s2 = math.addSectionDebug("Exams", 70);
    s2.newAssignmentDebug("Final Exam", 250, 20);
    math.display();
}
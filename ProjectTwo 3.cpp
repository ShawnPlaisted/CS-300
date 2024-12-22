#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Define a structure to hold course data
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Function to split a string by a delimiter
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to load courses from a file into a map
void loadCourses(const string& fileName, map<string, Course>& courses) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << fileName << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        vector<string> parts = split(line, ',');
        if (parts.size() < 2) {
            cerr << "Error: Malformed line in file." << endl;
            continue;
        }

        Course course;
        course.courseNumber = parts[0];
        course.courseTitle = parts[1];

        for (size_t i = 2; i < parts.size(); ++i) {
            course.prerequisites.push_back(parts[i]);
        }

        courses[course.courseNumber] = course;
    }

    file.close();
    cout << "Courses loaded successfully!" << endl;
}

// Function to print courses in alphanumeric order
void printCourseList(const map<string, Course>& courses) {
    cout << "\nCourse List:" << endl;
    for (const auto& [courseNumber, course] : courses) {
        cout << courseNumber << ": " << course.courseTitle << endl;
    }
}

// Function to print information about a specific course
void printCourseInfo(const map<string, Course>& courses, const string& courseNumber) {
    auto it = courses.find(courseNumber);
    if (it != courses.end()) {
        const Course& course = it->second;
        cout << "\nCourse Number: " << course.courseNumber << endl;
        cout << "Course Title: " << course.courseTitle << endl;
        if (course.prerequisites.empty()) {
            cout << "Prerequisites: None" << endl;
        } else {
            cout << "Prerequisites: ";
            for (const string& prereq : course.prerequisites) {
                cout << prereq << " ";
            }
            cout << endl;
        }
    } else {
        cout << "Error: Course not found." << endl;
    }
}

// Main menu function
void menu(map<string, Course>& courses) {
    int choice;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Load Course Data" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Course Information" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string fileName;
                cout << "Enter the course data file name: ";
                cin >> fileName;
                loadCourses(fileName, courses);
                break;
            }
            case 2:
                printCourseList(courses);
                break;
            case 3: {
                string courseNumber;
                cout << "Enter the course number: ";
                cin >> courseNumber;
                printCourseInfo(courses, courseNumber);
                break;
            }
            case 9:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Error: Invalid choice. Please try again." << endl;
        }
    } while (choice != 9);
}

int main() {
    map<string, Course> courses;
    menu(courses);
    return 0;
}
/*
 * =====================================================
 *   Student Management System - C++ Console Application
 *   Features: Add, Update, Delete, Display Students
 *             File Handling for Persistent Storage
 *             Menu-Driven Interface
 * =====================================================
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

// ─────────────────────────────────────────────
//  Student Structure
// ─────────────────────────────────────────────
struct Student {
    int    id;
    string name;
    int    age;
    string course;
    float  gpa;
};

// ─────────────────────────────────────────────
//  File name constant
// ─────────────────────────────────────────────
const string FILE_NAME = "students.dat";

// ─────────────────────────────────────────────
//  Utility: Clear input buffer
// ─────────────────────────────────────────────
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ─────────────────────────────────────────────
//  Utility: Display a decorative header
// ─────────────────────────────────────────────
void printHeader(const string& title) {
    int width = 55;
    string line(width, '=');
    int padding = (width - (int)title.size()) / 2;

    cout << "\n" << line << "\n";
    cout << string(padding, ' ') << title << "\n";
    cout << line << "\n\n";
}

// ─────────────────────────────────────────────
//  Serialize one student to a CSV line
// ─────────────────────────────────────────────
string serialize(const Student& s) {
    return to_string(s.id) + "," +
           s.name + "," +
           to_string(s.age) + "," +
           s.course + "," +
           to_string(s.gpa);
}

// ─────────────────────────────────────────────
//  Deserialize one CSV line to a Student
// ─────────────────────────────────────────────
bool deserialize(const string& line, Student& s) {
    stringstream ss(line);
    string token;

    try {
        getline(ss, token, ','); s.id     = stoi(token);
        getline(ss, token, ','); s.name   = token;
        getline(ss, token, ','); s.age    = stoi(token);
        getline(ss, token, ','); s.course = token;
        getline(ss, token, ','); s.gpa    = stof(token);
        return true;
    } catch (...) {
        return false;
    }
}

// ─────────────────────────────────────────────
//  Load all students from file
// ─────────────────────────────────────────────
vector<Student> loadStudents() {
    vector<Student> students;
    ifstream fin(FILE_NAME);
    if (!fin.is_open()) return students;   // file doesn't exist yet

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        Student s;
        if (deserialize(line, s))
            students.push_back(s);
    }
    fin.close();
    return students;
}

// ─────────────────────────────────────────────
//  Save all students to file (overwrite)
// ─────────────────────────────────────────────
void saveStudents(const vector<Student>& students) {
    ofstream fout(FILE_NAME);
    if (!fout.is_open()) {
        cerr << "[ERROR] Cannot open file for writing.\n";
        return;
    }
    for (const auto& s : students)
        fout << serialize(s) << "\n";
    fout.close();
}

// ─────────────────────────────────────────────
//  Check if an ID already exists
// ─────────────────────────────────────────────
bool idExists(const vector<Student>& students, int id) {
    for (const auto& s : students)
        if (s.id == id) return true;
    return false;
}

// ─────────────────────────────────────────────
//  Display a single student row
// ─────────────────────────────────────────────
void printTableHeader() {
    cout << left
         << setw(6)  << "ID"
         << setw(22) << "Name"
         << setw(6)  << "Age"
         << setw(18) << "Course"
         << setw(6)  << "GPA"
         << "\n";
    cout << string(58, '-') << "\n";
}

void printStudentRow(const Student& s) {
    cout << left
         << setw(6)  << s.id
         << setw(22) << s.name
         << setw(6)  << s.age
         << setw(18) << s.course
         << fixed << setprecision(2) << setw(6) << s.gpa
         << "\n";
}

// ─────────────────────────────────────────────
//  1. Add Student
// ─────────────────────────────────────────────
void addStudent() {
    printHeader("ADD NEW STUDENT");
    vector<Student> students = loadStudents();
    Student s;

    cout << "Enter Student ID   : ";
    while (!(cin >> s.id) || s.id <= 0) {
        cout << "[!] Invalid ID. Try again: ";
        clearInput();
    }
    clearInput();

    if (idExists(students, s.id)) {
        cout << "[!] A student with ID " << s.id << " already exists.\n";
        return;
    }

    cout << "Enter Name         : ";
    getline(cin, s.name);

    cout << "Enter Age          : ";
    while (!(cin >> s.age) || s.age < 1 || s.age > 120) {
        cout << "[!] Invalid age. Try again: ";
        clearInput();
    }
    clearInput();

    cout << "Enter Course       : ";
    getline(cin, s.course);

    cout << "Enter GPA (0-4.0)  : ";
    while (!(cin >> s.gpa) || s.gpa < 0.0f || s.gpa > 4.0f) {
        cout << "[!] GPA must be between 0.0 and 4.0. Try again: ";
        clearInput();
    }
    clearInput();

    students.push_back(s);
    saveStudents(students);

    cout << "\n[+] Student added successfully!\n";
}

// ─────────────────────────────────────────────
//  2. Display All Students
// ─────────────────────────────────────────────
void displayAllStudents() {
    printHeader("ALL STUDENTS");
    vector<Student> students = loadStudents();

    if (students.empty()) {
        cout << "  No student records found.\n";
        return;
    }

    printTableHeader();
    for (const auto& s : students)
        printStudentRow(s);
    cout << "\nTotal records: " << students.size() << "\n";
}

// ─────────────────────────────────────────────
//  3. Search / Display One Student
// ─────────────────────────────────────────────
void searchStudent() {
    printHeader("SEARCH STUDENT");
    vector<Student> students = loadStudents();

    int id;
    cout << "Enter Student ID to search: ";
    while (!(cin >> id)) { clearInput(); cout << "Invalid input: "; }
    clearInput();

    for (const auto& s : students) {
        if (s.id == id) {
            printTableHeader();
            printStudentRow(s);
            return;
        }
    }
    cout << "[!] Student with ID " << id << " not found.\n";
}

// ─────────────────────────────────────────────
//  4. Update Student
// ─────────────────────────────────────────────
void updateStudent() {
    printHeader("UPDATE STUDENT");
    vector<Student> students = loadStudents();

    int id;
    cout << "Enter Student ID to update: ";
    while (!(cin >> id)) { clearInput(); cout << "Invalid input: "; }
    clearInput();

    for (auto& s : students) {
        if (s.id == id) {
            cout << "\nCurrent record:\n";
            printTableHeader();
            printStudentRow(s);
            cout << "\nEnter new details (press Enter to keep current value):\n";

            string tmp;

            cout << "Name [" << s.name << "]: ";
            getline(cin, tmp);
            if (!tmp.empty()) s.name = tmp;

            cout << "Age  [" << s.age << "]: ";
            getline(cin, tmp);
            if (!tmp.empty()) {
                try { s.age = stoi(tmp); } catch (...) {}
            }

            cout << "Course [" << s.course << "]: ";
            getline(cin, tmp);
            if (!tmp.empty()) s.course = tmp;

            cout << "GPA [" << fixed << setprecision(2) << s.gpa << "]: ";
            getline(cin, tmp);
            if (!tmp.empty()) {
                try {
                    float g = stof(tmp);
                    if (g >= 0.0f && g <= 4.0f) s.gpa = g;
                    else cout << "[!] GPA out of range. Keeping old value.\n";
                } catch (...) {}
            }

            saveStudents(students);
            cout << "\n[+] Student updated successfully!\n";
            return;
        }
    }
    cout << "[!] Student with ID " << id << " not found.\n";
}

// ─────────────────────────────────────────────
//  5. Delete Student
// ─────────────────────────────────────────────
void deleteStudent() {
    printHeader("DELETE STUDENT");
    vector<Student> students = loadStudents();

    int id;
    cout << "Enter Student ID to delete: ";
    while (!(cin >> id)) { clearInput(); cout << "Invalid input: "; }
    clearInput();

    auto it = remove_if(students.begin(), students.end(),
                        [id](const Student& s){ return s.id == id; });

    if (it == students.end()) {
        cout << "[!] Student with ID " << id << " not found.\n";
        return;
    }

    cout << "\nRecord to delete:\n";
    printTableHeader();
    printStudentRow(*it);

    cout << "\nAre you sure? (y/n): ";
    char confirm;
    cin >> confirm;
    clearInput();

    if (tolower(confirm) == 'y') {
        students.erase(it, students.end());
        saveStudents(students);
        cout << "[+] Student deleted successfully!\n";
    } else {
        cout << "[-] Deletion cancelled.\n";
    }
}

// ─────────────────────────────────────────────
//  6. Display Statistics
// ─────────────────────────────────────────────
void showStatistics() {
    printHeader("STATISTICS");
    vector<Student> students = loadStudents();

    if (students.empty()) {
        cout << "  No records to compute statistics.\n";
        return;
    }

    float totalGpa = 0, maxGpa = students[0].gpa, minGpa = students[0].gpa;
    for (const auto& s : students) {
        totalGpa += s.gpa;
        if (s.gpa > maxGpa) maxGpa = s.gpa;
        if (s.gpa < minGpa) minGpa = s.gpa;
    }
    float avgGpa = totalGpa / students.size();

    cout << "  Total Students : " << students.size() << "\n";
    cout << fixed << setprecision(2);
    cout << "  Average GPA    : " << avgGpa << "\n";
    cout << "  Highest GPA    : " << maxGpa << "\n";
    cout << "  Lowest GPA     : " << minGpa << "\n";
}

// ─────────────────────────────────────────────
//  Main Menu
// ─────────────────────────────────────────────
void showMenu() {
    printHeader("STUDENT MANAGEMENT SYSTEM");
    cout << "  1. Add Student\n";
    cout << "  2. Display All Students\n";
    cout << "  3. Search Student by ID\n";
    cout << "  4. Update Student\n";
    cout << "  5. Delete Student\n";
    cout << "  6. Show Statistics\n";
    cout << "  0. Exit\n\n";
    cout << "  Enter your choice: ";
}

// ─────────────────────────────────────────────
//  Entry Point
// ─────────────────────────────────────────────
int main() {
    int choice;
    do {
        showMenu();
        while (!(cin >> choice)) {
            clearInput();
            cout << "  Invalid input. Try again: ";
        }
        clearInput();

        switch (choice) {
            case 1: addStudent();        break;
            case 2: displayAllStudents(); break;
            case 3: searchStudent();      break;
            case 4: updateStudent();      break;
            case 5: deleteStudent();      break;
            case 6: showStatistics();     break;
            case 0: cout << "\n  Goodbye!\n\n"; break;
            default: cout << "\n  [!] Invalid option. Try 0-6.\n"; break;
        }

        if (choice != 0) {
            cout << "\n  Press Enter to return to menu...";
            cin.get();
        }

    } while (choice != 0);

    return 0;
}
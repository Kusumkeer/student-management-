#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Student {
    int id;
    string name;
    float marks;

public:
    void input() {
        cout << "Enter ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() const {
        cout << setw(10) << id << setw(20) << name << setw(10) << marks << endl;
    }

    int getID() const {
        return id;
    }

    void modify() {
        cout << "Modify Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Modify Marks: ";
        cin >> marks;
    }
};

void addStudent() {
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);
    s.input();
    file.write(reinterpret_cast<char*>(&s), sizeof(s));
    file.close();
    cout << "Student added successfully.\n";
}

void displayStudents() {
    Student s;
    ifstream file("students.dat", ios::binary);
    cout << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Marks" << endl;
    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        s.display();
    }
    file.close();
}

void searchStudent(int targetID) {
    Student s;
    bool found = false;
    ifstream file("students.dat", ios::binary);
    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.getID() == targetID) {
            cout << "Student found:\n";
            s.display();
            found = true;
            break;
        }
    }
    if (!found) cout << "Student not found.\n";
    file.close();
}

void deleteStudent(int targetID) {
    Student s;
    ifstream inFile("students.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);
    bool deleted = false;

    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.getID() != targetID) {
            outFile.write(reinterpret_cast<char*>(&s), sizeof(s));
        } else {
            deleted = true;
        }
    }

    inFile.close();
    outFile.close();
    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (deleted)
        cout << "Student deleted successfully.\n";
    else
        cout << "Student not found.\n";
}

void modifyStudent(int targetID) {
    Student s;
    fstream file("students.dat", ios::binary | ios::in | ios::out);
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.getID() == targetID) {
            cout << "Current data:\n";
            s.display();
            s.modify();
            file.seekp(-static_cast<int>(sizeof(s)), ios::cur);
            file.write(reinterpret_cast<char*>(&s), sizeof(s));
            found = true;
            cout << "Record updated.\n";
            break;
        }
    }

    if (!found) cout << "Student not found.\n";
    file.close();
}

int main() {
    int choice, id;
    do {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student by ID\n";
        cout << "4. Modify Student\n";
        cout << "5. Delete Student\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            displayStudents();
            break;
        case 3:
            cout << "Enter ID to search: ";
            cin >> id;
            searchStudent(id);
            break;
        case 4:
            cout << "Enter ID to modify: ";
            cin >> id;
            modifyStudent(id);
            break;
        case 5:
            cout << "Enter ID to delete: ";
            cin >> id;
            deleteStudent(id);
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
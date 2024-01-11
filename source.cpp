#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <regex>

using namespace std;


class Student{
private:
    string name;
    int id;



public:
    void addStudent();
    void viewDetails();
};


class Login{
private:
    string username;
    string password;

public:
    bool authenticate();
    bool registerUser();
};

bool Login::authenticate(){
    cout<<"Enter your username: ";
    cin>>username;
    
    ifstream userFile("users.txt");
    string storedUsername, storedPassword;

    while(userFile>>storedUsername>>storedPassword) {
        if(storedUsername==username) {
            cout<<"Enter your password: ";
            cin>>password;

            
            
            if(storedPassword==password) {
                cout<<"Login successful!"<<endl;
                userFile.close();
                return true;
            } 
            else{
                cout<<"Incorrect password. Exiting."<<endl;
                userFile.close();
                return false;
            }
        }
    }

    cout<<"Username not found. Exiting." <<endl;
    userFile.close();
    return false;
}

bool Login::registerUser() {
    cout<<"Enter a new username: ";
    cin>>username;

    
    ifstream userFile("users.txt");
    string storedUsername, storedPassword;

    while(userFile>>storedUsername>>storedPassword) {
        if(storedUsername==username) {
            cout<<"Username already exists. Choose another username." <<endl;
            userFile.close();
            return false;
        }
    }

    
    cout<<"Enter a password: ";
    cin>>password;

    
    ofstream newUserFile("users.txt", ios::app);
    newUserFile<<username<<" "<<password <<endl;
    newUserFile.close();

    cout<<"Registration successful! You can now log in." <<endl;

    return true;
}

void Student::addStudent(){
    cout<<"Enter the name of the student: ";
    cin.ignore();
    getline(cin, name);
    cout<<"Enter the student ID: ";
    cin>>id;

    
    ofstream studentFile("students.txt", ios::app);
    studentFile<<id<<" "<<name<<endl;
    studentFile.close();

    cout<<"Student added successfully." <<endl;
}

void Student::viewDetails(){
    int studentId;
    cout<< "Enter the student ID: ";
    cin>>studentId;

    
    ifstream studentFile("students.txt");
    int currentId;
    string currentName;

    while(studentFile>>currentId>>currentName) {
        if(currentId==studentId) {
            cout<<"Student Name: "<<currentName<<endl;
            cout<< "Student ID: "<<currentId<<endl;
        
            break;
        }
    }

    studentFile.close();
}



int main(){
    Login login;
    bool loggedIn=login.authenticate();

    if (!loggedIn)
    {
        char choice;
        cout<<"User not logged in. Do you want to register? (y/n): ";
        cin>>choice;

        if(choice!='y'&&choice!='Y') 
        {
            cout<<"Exiting."<<endl;
            return 0;
        }

        loggedIn=login.registerUser();
        if(!loggedIn)
        {
            cout<< "Registration failed. Exiting."<<endl;
            return 0;
        }
    }

    Student student;

    int choice;
    do {
        cout<<"\n===== Library Management System =====\n";
        cout<<"------------------------------------------" <<endl;
        cout<<"------------------------------------------" <<endl;
        cout<<"1: Add Student"<<endl;
        cout<<"2: View Student Detail" <<endl;
        cout<<"Enter your choice (Enter 0 to exit): " <<endl;
        cout<<"------------------------------------------" <<endl;
        cout<<"------------------------------------------" <<endl;
        cin>>choice;

        switch(choice)
        {
            case 1:
                student.addStudent();
                break;

            case 2:
                student.viewDetails();
                break;

            case 0:
                cout << "Exiting program." << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } 
    while(choice != 0);

    return 0;
}

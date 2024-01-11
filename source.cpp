#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <regex>

using namespace std;

class Book{
private:
    string title;
    int bookId;
    bool isIssued;


public:
    void addBook();
    void displayBooks();
    void issueBook();
    void returnBook();



};

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

void Book::addBook() {
    cout<<"Enter the title of the book: ";
    cin.ignore();
    getline(cin, title);
    cout<<"Enter the book ID: ";
    cin>>bookId;
    isIssued=false;

    
    ofstream bookFile("books.txt", ios::app);
    if(isIssued){

        bookFile<<bookId<<" "<<title<<"1"<<endl;
    } else 
    {
        bookFile<<bookId<<" "<<title<<" 0"<<endl;
    }
    bookFile.close();

    cout<<"Book added successfully." <<endl;
}

void Book::displayBooks(){
    ifstream bookFile("books.txt");
    int currentBookId;
    string currentTitle;
    bool currentIsIssued;

    while(bookFile>>currentBookId>>currentTitle>>currentIsIssued){
        cout<<"Book ID: "<<currentBookId<<"|Title:"<<currentTitle<<" |Status: ";
        if(currentIsIssued){
            cout<<"Checked Out" <<endl;
        } 
        else 
        {
            cout<<"Available"<<endl;
        }

    }

    bookFile.close();
}


void Book::issueBook(){
    int bookId;
    cout<<"Enter the Book ID to issue: ";
    cin>>bookId;

    ifstream bookFile("books.txt");
    ofstream tempFile("temp.txt", ios::app);

    int currentBookId;
    string currentTitle;
    bool currentIsIssued;

    while(bookFile>>currentBookId>>currentTitle>>currentIsIssued) {
        if(currentBookId==bookId) {
            if(currentIsIssued){
                cout<<"Book is already checked out."<<endl;
            } 
            else 
            {
                currentIsIssued=true;
                cout<<"Book issued successfully." <<endl;
            }
        }
        tempFile<<currentBookId<<" "<<currentTitle<<" "<<currentIsIssued<<endl;
    }

    bookFile.close();
    tempFile.close();

    

    remove("books.txt");
    rename("temp.txt", "books.txt");
}

void Book::returnBook(){
    int bookId;
    cout<<"Enter the Book ID to return: ";
    cin>>bookId;

    ifstream bookFile("books.txt");
    ofstream tempFile("temp.txt", ios::app);

    int currentBookId;
    string currentTitle;
    bool currentIsIssued;

    while(bookFile>>currentBookId>>currentTitle>>currentIsIssued) 
    {
        if(currentBookId==bookId) 
        {
            if(!currentIsIssued)
             {
                cout<<"Book is not checked out." <<endl;
            } 
            else
            {
                currentIsIssued=false;
                cout<<"Book returned successfully." <<endl;
            }
        }
        tempFile<<currentBookId<<" "<<currentTitle<<" "<<currentIsIssued <<endl;
    }

    bookFile.close();
    tempFile.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");
}


int main() {
    Login login;
    bool loggedIn=login.authenticate();

    if(!loggedIn)
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
            cout<<"Registration failed. Exiting." <<endl;
            return 0;
        }
    }

    Student student;
    Book book;

    int choice;
    do{
        
        cout<<"\n===== Library Management System =====\n";
        cout<<"------------------------------------------"<<endl;
        cout<<"------------------------------------------"<<endl;
        cout<<"1: Add Student"<<endl;
        cout<<"2: View Student Detail"<<endl;
        cout<<"3: Add Book"<<endl;
        cout<<"4: Display Books"<<endl;
        cout<<"5: Issue Book "<<endl;
        cout<<"6: Return Book"<<endl;
        cout<<"Enter your choice (Enter 0 to exit): "<<endl;
        cout<<"------------------------------------------"<<endl;
        cout<<"------------------------------------------"<<endl;
        cin>>choice;

        switch(choice)
        {
            case 1:
                student.addStudent();
                break;
            
            case 2:
                student.viewDetails();
                break;
            
            case 3:
                book.addBook();
                break;
            
            case 4:
                book.displayBooks();
                break;
            
            
            case 5:
                book.issueBook();  
                break;
            
            case 6:
                book.returnBook();  
                break;
            case 0:
                cout<<"Exiting program." <<endl;
                break;
            default:
                cout<<"Invalid choice. Please try again."<<endl;
                break;
        }
    } 
    while(choice!=0);

    return 0;
}

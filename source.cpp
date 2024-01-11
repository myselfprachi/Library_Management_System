#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <regex>

using namespace std;

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


    return 0;
}

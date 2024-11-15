// #ifndef USER_H
// #define USER_H

// #include <string>
// #include <iostream>

// using namespace std;

// class User {
// protected:
//     string username;
//     string password;
//     string role;  
//     static const int MAX_USERS = 100;
//     static User* users[MAX_USERS];
//     static int userCount; 

// public:
//     User(const string& username, const string& password, const string& role);
//     string getUsername() const;
//     string getRole() const;
//     static bool registerUser(const string& username, const string& password, const string& role);
//     static bool login(const string& username, const string& password);
//     virtual void display() const;
//     virtual ~User() {}
// };

// #endif 



// user.h

#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

using namespace std;

class User {
public:
    // Constructor to initialize username and password
    User(const std::string& username, const std::string& password, const std::string& role)
        : username(username), password(password), role(role) {}

    // Virtual method to display user info (can be overridden by derived classes)


    // Getter for username
    std::string getUsername() const{
        return username;
    };

    // Getter for password
    std::string getPassword() const{
        return password;
    };
    std::string getRole() const{
        return role;
    };
    static bool registerUser(const string& username, const string& password, const string& role);
    static bool login(const string& username, const string& password);
    static int getUserCount();
    static User* getUser(int index);

protected:
    std::string username;
    std::string password;
    std::string role;
    static const int MAX_USERS = 100;
    static User* users[MAX_USERS];
    static int userCount;
};

#endif // USER_H

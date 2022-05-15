#include <iostream>
#include <stdlib.h>
#include "Models/Context.hpp"

using std::cin;
using std::cout;
using std::cerr;

void registerUser(User &currenUser){

    char username[DEFAULT_STRING_SIZE], password[DEFAULT_STRING_SIZE], email[DEFAULT_STRING_SIZE];

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    cout << "Enter email: ";
    cin >> email;
    cin.ignore();

    try{ currenUser = User(username, password, email); }
    catch(const InvalidFormatException &e){ throw e; }

}

User &loginUser(Vector<User> &users){

    char username[DEFAULT_STRING_SIZE], password[DEFAULT_STRING_SIZE];

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    cin.ignore();

    bool correctUsername = false, correctPassword;
    size_t index = 0;

    for(size_t i = 0; i < users.size(); i++)
        if(!strcmp(users[i].getUsername(), username)){

            correctUsername = true;
            index = i;
            break;

        }

    correctPassword = !strcmp(users[index].getPassword(), password); 

    if(!correctUsername) throw InvalidFormatException("Username does not exist!");
    if(!correctPassword) throw InvalidFormatException("Wrong password!");

    return users[index];

}

Vector<Travel> getAllTravelToDestination(Vector<User> &users){

    char destination[DEFAULT_STRING_SIZE];

    cout << "Where do you want to go?\n: ";
    cin.getline(destination, DEFAULT_STRING_SIZE);

    Vector<Travel> result;
    
    for(size_t i = 0; i < users.size(); i++){

        Vector<Travel> travels = users[i].getTravels();
        for(size_t j = 0; j < travels.size(); j++)
            if(!strcmp(travels[j].getDestination(), destination))
                result.pushBack(travels[j]);

    }

    if(result.size()) return result;
    throw InvalidFormatException("Nobody has traveled to this destination");

}

void addTravel(User &user){

    char destination[DEFAULT_STRING_SIZE], comment[DEFAULT_STRING_SIZE], photos[DEFAULT_STRING_SIZE];
    unsigned char grade;
    Date start, end;

    cout << "Enter destination\n: ";
    cin.getline(destination, DEFAULT_STRING_SIZE);

    cout << "Enter from date\n: ";
    cin >> start;
    cout << "Enter to date\n: ";
    cin >> end;

    cout << "Enter grade\n: ";
    cin >> grade;
    cin.ignore();

    cout << "Enter comment\n: ";
    cin.getline(comment, DEFAULT_STRING_SIZE);

    cout << "Enter photos(\"end\" to end your input)\n: ";
    cin.getline(photos, DEFAULT_STRING_SIZE);

    Travel newTravel;
    try{ newTravel = Travel(destination, start, end, grade, comment, photos); }
    catch(const InvalidFormatException &e){ throw e; }

    user.addTravel(newTravel);

}

void platform(User &currentUser, Vector<User> &users){

    unsigned short choice = 0;

    while(choice != 3){

        system("cls");
        cout << "Select one:\n1.Add travel\n2.Search travel destination\n3.Logout\n: ";
        cin >> choice;
        cin.ignore();

        switch (choice){

            case 1:
                try{ for(size_t i = 0; i < users.size(); i++) if(!strcmp(users[i].getUsername(), currentUser.getUsername())) addTravel(users[i]); }
                catch(const InvalidFormatException &e){ cerr << e.what() << '\n'; cin.get(); }
                break;

            case 2:
                try{
                    
                    Vector<Travel> travels = getAllTravelToDestination(users);
                    size_t sumGrade = 0;

                    for(size_t i = 0; i < travels.size(); i++){

                        cout << "From: " << travels[i].getFromDate()
                            << "\nTo: " << travels[i].getToDate()
                            << "\nGraded: " << travels[i].getGrade()
                            << "\nCommented: " << travels[i].getComment()
                            << "\nPhotos: " << travels[i].getPhotos() << "\n\n";

                        sumGrade += travels[i].getGrade() - '0';

                    }

                    cout << "Average grade is: " << sumGrade * 1.0 / travels.size() << '\n';
                    cin.get();
                    
                }
                catch(const InvalidFormatException &e){ cerr << e.what() << '\n'; cin.get(); }
                break;

            default:
                break;

        }
        
    }

}

void save(const Vector<User> &users){

    ofstream ofs("Database/users.db", ios::binary | ios::trunc);
    for(size_t i = 0; i < users.size(); i++)
        users[i].write(ofs);
    ofs.close();

}

void authentication(){

    Vector<User> users;
    Context::getUsersFromDB(users);
    unsigned short choice = 0;
    User currentUser;

    while(choice != 3){

        system("cls");
        cout << "Welcome to the platoform\nSelect one of the following:\n1.Register\n2.Log in\n3.Exit\n: ";
        cin >> choice;

        switch (choice){

            case 1:
                try{ registerUser(currentUser); users.pushBack(currentUser); platform(currentUser, users); }
                catch(const InvalidFormatException &e){ cerr << e.what() << '\n'; cin.get(); }
                break;
            
            case 2:
                try{ currentUser = loginUser(users); platform(currentUser, users); }
                catch(const InvalidFormatException &e){ cerr << e.what() << '\n'; cin.get(); }

            case 3:
                save(users);
                break;
            
            default:
                break;

        }

    }

}

int main(){

    authentication();

}

/*

2
Hristo
Hello_world2
1
Sofia
22 06 2002
26 06 2002
5
A very bussy city filled with cool stuff
sunset.png hello.jpeg
2
Sofia

1
Krash
Hi!there1
Krash@mail.bg

*/
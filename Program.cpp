#include <iostream>
#include "Models/User.hpp"

void registerUser(const User &newUser){

    ofstream ofs("Database/users.db", ios::binary | ios::app | ios::ate);
    newUser.write(ofs);
    ofs.close();

}

void loginUser(){

    char *username = new char[1024], *password = new char[1024];
    std::cin >> username >> password;

}



Vector<Travel> getAllTravelToDestination(const Vector<User> &users, const char *destination){

    Vector<Travel> result;

    for(size_t i = 0; i < users.size(); i++){

        Vector<Travel> travels = users[i].getTravels();
        for(size_t j = 0; j < travels.size(); j++)
            if(!strcmp(travels[j].getDestination(), destination))
                result.pushBack(travels[j]);

    }

    return result;

}

void createTravel(){

    // Travel otherTravel("Sofia", Date(2, 5, 2018), Date(30, 12, 2019), 3, "Big city with loads of oppurtunities\nfor business and money.", "sofia.jpeg\nVitosha.png\nflat.jpeg");

    // std::ofstream ofs("my.db", std::ios::app | std::ios::binary | std::ios::ate);
    // myTravel.write(ofs);
    // otherTravel.write(ofs);
    // ofs.close();

    // Travel newTravel;
    // std::ifstream ifs("my.db", std::ios::binary);
    // newTravel.read(ifs);
    // newTravel.read(ifs);

    // std::cout << newTravel.getDestination() << '\n'
    //         << newTravel.getFromDate().toString() << '\n'
    //         << newTravel.getToDate().toString() << '\n'
    //         << (int)newTravel.getGrade() << '\n'
    //         << newTravel.getComment() << '\n'
    //         << newTravel.getPhotos() << '\n';

    // ifs.close();

}

int main(){

    char username[] = "Krash";
    char password[] = "Helloworld_2";
    char email[] = "Krash@mail.bg";

    try{

        User newUser(username, password, email);
        registerUser(newUser);

    }
    catch(const std::exception &e){

        std::cerr << e.what() << '\n';
        return -1;

    }
    
    Vector<char *> photos;
    char *photo1;
    char *photo2;
    char *photo3;
    strcpy(photo1, "burgas.jpeg");
    strcpy(photo2, "locumfest.png");
    strcpy(photo3, "sunrise_on_the_coast.jpeg");
    photos.pushBack(photo1);
    photos.pushBack(photo2);
    photos.pushBack(photo3);
    Travel myTravel("Burgas", Date(5, 7, 2019), Date(29, 7, 2019), 5, "A beautiful city on the\nBlack Sea coast. I\nspent two\nunforgettable weeks\nthere, meeting new\npeople.", photos);

    // Something wrong with the travels
    Vector<User> users = User::getUsersFromDB();
    for(size_t i = 0; i < users.size(); i++) if(!strcmp(users[i].getUsername(), "Krash")) users[i].addTravel(myTravel);
    Vector<Travel> travels = getAllTravelToDestination(users, "Burgas");
    for(size_t i = 0; i < travels.size(); i++) std::cout << travels[i].getComment() << '\n';

}
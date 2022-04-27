#include <iostream>
#include <fstream>
#include "Models/Travel.hpp"

int main(){

    Travel myTravel("Burgas", Date(5, 7, 2019), Date(29, 7, 2019), 5, "A beautiful city on the\nBlack Sea coast. I\nspent two\nunforgettable weeks\nthere, meeting new\npeople.", "burgas.jpeg\nlocumfest.png\nsunrise_on_the_coast.jpeg");
    Travel otherTravel("Sofia", Date(2, 5, 2018), Date(30, 12, 2019), 3, "Big city with loads of oppurtunities\nfor business and money.", "sofia.jpeg\nVitosha.png\nflat.jpeg");

    std::ofstream ofs("my.db", std::ios::app | std::ios::binary | std::ios::ate);
    myTravel.write(ofs);
    otherTravel.write(ofs);
    ofs.close();

    Travel newTravel;
    std::ifstream ifs("my.db", std::ios::binary);
    newTravel.read(ifs);
    newTravel.read(ifs);

    std::cout << newTravel.getDestination() << '\n'
            << newTravel.getFromDate().toString() << '\n'
            << newTravel.getToDate().toString() << '\n'
            << (int)newTravel.getGrade() << '\n'
            << newTravel.getComment() << '\n'
            << newTravel.getPhotos() << '\n';

    ifs.close();

}
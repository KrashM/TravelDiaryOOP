#include <iostream>
#include <fstream>
#include "Models/Travel.hpp"

int main(){

    Travel myTravel("Burgas", Date(5, 7, 2019), Date(29, 7, 2019), 5, "A beautiful city on the\nBlack Sea coast. I\nspent two\nunforgettable weeks\nthere, meeting new\npeople.", "burgas.jpeg\nlocumfest.png\nsunrise_on_the_coast.jpeg");
    Travel otherTravel("Sofia", Date(2, 5, 2018), Date(30, 12, 2019), 3, "Big city with loads of oppurtunities\nfor business and money.", "sofia.jpeg\nVitosha.png\nflat.jpeg");

    // std::ofstream ofs("my.db", std::ios_base::app | std::ios::ate);
    // ofs << myTravel << '\n';

    // Writing is fine
    // Writes 80 bytes consitantly to the file(40 for each object)
    std::ofstream ofs("my.db", std::ios::app | std::ios::binary | std::ios::ate);
    ofs.write((const char *)&myTravel, sizeof(myTravel));
    ofs.write((const char *)&otherTravel, sizeof(otherTravel));
    ofs.close();

    // TODO:
    // Cursor is out of order
    Travel newTravel;
    // Tried with regular text
    // std::ifstream ifs("my.db");
    // ifs >> newTravel;
    std::ifstream ifs("my.db", std::ios::binary);
    // std::cout << ifs.tellg();
    // ifs.seekg(sizeof(Travel), std::ios::beg);
    // WARNING:
    // Could it be because of the dynamic char * type unknown size of the string
    // How can I overwrite the read method to read properly
    ifs.read((char *)&newTravel, sizeof(newTravel));

    // All of these methods say that the reading was correct and no information was lost
    std::cout << ifs.good() << ifs.fail() << ifs.bad() << '\n';

    // In the rare case it spits out a text it only gives me the two dates and the grade
    // e.g. the strings are blank
    std::cout << newTravel.getDestination() << '\n'
            << newTravel.getFromDate().toString() << '\n'
            << newTravel.getToDate().toString() << '\n'
            << (int)newTravel.getGrade() << '\n'
            << newTravel.getComment() << '\n'
            << newTravel.getPhotos() << '\n';

    ifs.close();

}
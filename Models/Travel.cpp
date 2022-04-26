#include "Travel.hpp"
#include <cstring>

void Travel::erase(){

    delete[] this -> destination;
    delete[] this -> comment;
    delete[] this -> photos;

}

void Travel::copy(const Travel &other){

    this -> destination = new char[strlen(other.destination) + 1];
    strcpy(this -> destination, other.destination);

    this -> from = other.from;
    this -> to = other.to;

    this -> grade = other.grade;

    this -> comment = new char[strlen(other.comment) + 1];
    strcpy(this -> comment, other.comment);

    this -> photos = new char[strlen(other.photos) + 1];
    strcpy(this -> photos, other.photos);

}

Travel::Travel(): destination(nullptr), from(Date()), to(Date()), grade(0), comment(nullptr), photos(nullptr){}
Travel::Travel(const char *destination, const Date &from, const Date &to, const unsigned char grade, const char *comment, const char *photos){

    this -> destination = new char[strlen(destination) + 1];
    strcpy(this -> destination, destination);

    this -> from = from;
    this -> to = to;

    this -> grade = grade;

    this -> comment = new char[strlen(comment) + 1];
    strcpy(this -> comment, comment);

    this -> photos = new char[strlen(photos) + 1];
    strcpy(this -> photos, photos);

}
Travel::Travel(const Travel &other){ this -> copy(other); }
Travel::~Travel(){ this -> erase(); }

Travel &Travel::operator =(const Travel &other){

    if(this != &other){

        this -> erase();
        this -> copy(other);

    }

    return *this;

}

ostream &operator <<(ostream &os, const Travel &obj){

    os << obj.destination << ' ' << obj.from << ' ' << obj.to << ' ' << (int)obj.grade << ' ' << obj.comment << ' ' << obj.photos;
    return os;

}

istream &operator >>(istream &in, Travel &obj){

    in >> obj.destination >> obj.from >> obj.to >> obj.grade >> obj.comment >> obj.photos;
    return in;

}

void Travel::setDestination(const char *destination){

    this -> destination = new char[strlen(destination) + 1];
    strcpy(this -> destination, destination);

}

void Travel::setFromDate(const Date &from){ this -> from = from; }
void Travel::setToDate(const Date &to){ this -> to = to; }
void Travel::setGrade(const unsigned short grade){ this -> grade = grade; }

void Travel::setComment(const char *comment){
    
    this -> comment = new char[strlen(comment) + 1];
    strcpy(this -> comment, comment);

}

void Travel::setPhotos(const char *photos){
    
    this -> photos = new char[strlen(photos) + 1];
    strcpy(this -> photos, photos);

}

char *Travel::getDestination() const{ return this -> destination; }
Date Travel::getFromDate() const{ return this -> from; }
Date Travel::getToDate() const{ return this -> to; }
unsigned char Travel::getGrade() const{ return this -> grade; }
char *Travel::getComment() const{ return this -> comment; }
char *Travel::getPhotos() const{ return this -> photos; }
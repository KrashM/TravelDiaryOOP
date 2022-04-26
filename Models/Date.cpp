#include "Date.hpp"

void Date::copy(const Date &other){

    this -> day = other.day;
    this -> mounth = other.mounth;
    this -> year = other.year;

}

Date::Date(): day(0), mounth(0), year(0){}
Date::Date(unsigned char day, unsigned mounth, unsigned year): day(day), mounth(mounth), year(year){}
Date::Date(const Date &other){ copy(other); }

Date &Date::operator =(const Date &other){

    if(this != &other) copy(other);
    return *this;

}

ostream &operator <<(ostream &os, const Date &obj){

    os << obj.toString();
    return os;

}

istream &operator >>(istream &is, Date &obj){

    char separator;

    is >> obj.day >> separator >> obj.mounth >> separator >> obj.year;
    return is;

}

void Date::setDay(unsigned char day){ this -> day = day; }
void Date::setMounth(unsigned char mounth){ this -> mounth = mounth; }
void Date::setYear(unsigned short year){ this -> year = year; }

unsigned char Date::getDay() const{ return this -> day; }
unsigned char Date::getMounth() const{ return this -> mounth; }
unsigned short Date::getYear() const{ return this -> year; }

unsigned short pow(unsigned short n, unsigned char power){ return !power ? 1 : pow(n, power - 1) * n; }
unsigned char digitsInYear(unsigned short year){

    if(!year) return 1;
    unsigned char digits = 0;
    do ++digits; while(year /= 10);
    return digits;

}

const char *Date::toString() const{

    char *result = new char[12];
    result[0] = '\0';

    result[0] = '0' + this -> day / 10;
    result[1] = '0' + this -> day % 10;
    result[2] = ':';
    result[3] = '0' + this -> mounth / 10;
    result[4] = '0' + this -> mounth % 10;
    result[5] = ':';

    unsigned char index = 6;
    unsigned char digits = digitsInYear(this -> year);
    unsigned short powTen = pow(10, digits - 1);
    do result[index++] = '0' + (this -> year / powTen) % 10; while(powTen /= 10);
    result[index] = '\0';

    return result;

}
#pragma once

#include <iostream>

using std::istream;
using std::ostream;

class Date{

    private:
        unsigned short year;
        unsigned char day, mounth;

        void copy(const Date &other);

    public:
        Date();
        Date(unsigned char day, unsigned mounth, unsigned year);
        Date(const Date &other);

        Date &operator =(const Date &other);
        friend ostream &operator <<(ostream &os, const Date &obj);
        friend istream &operator >>(istream &is, Date &obj);

        void setDay(unsigned char day);
        void setMounth(unsigned char mounth);
        void setYear(unsigned short year);

        unsigned char getDay() const;
        unsigned char getMounth() const;
        unsigned short getYear() const;

        const char *toString() const;

};
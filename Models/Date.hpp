#pragma once

#include <fstream>

using std::istream;
using std::ostream;

class Date{

    private:
        unsigned short year;
        unsigned char day, mounth;

        void copy(const Date &);

    public:
        Date();
        Date(unsigned char, unsigned, unsigned);
        Date(const Date &);

        Date &operator =(const Date &);
        friend bool operator >(const Date &, const Date &);
        friend ostream &operator <<(ostream &, const Date &);
        friend istream &operator >>(istream &, Date &);

        void setDay(unsigned char);
        void setMounth(unsigned char);
        void setYear(unsigned short);

        unsigned char getDay() const;
        unsigned char getMounth() const;
        unsigned short getYear() const;

        const char *toString() const;

};
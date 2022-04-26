#pragma once

class Date{

    private:
        unsigned char day, mounth;
        unsigned short year;

        void copy(const Date &other);

    public:
        Date();
        Date(unsigned char day, unsigned mounth, unsigned year);
        Date(const Date &other);

        Date &operator =(const Date &other);

        void setDay(unsigned char day);
        void setMounth(unsigned char mounth);
        void setYear(unsigned short year);

        unsigned char getDay() const;
        unsigned char getMounth() const;
        unsigned short getYear() const;

        const char *toString() const;

};
#pragma once

#include "Date.hpp"

class Travel{

    private:
        char *destination, *comment, *photos;
        Date from, to;
        unsigned char grade;

        void erase();
        void copy(const Travel &other);

    public:
        Travel();
        Travel(const char *destination, const Date &from, const Date &to, const unsigned char grade, const char *comment, const char *photos);
        Travel(const Travel &other);
        ~Travel();

        Travel &operator =(const Travel &other);
        friend ostream &operator <<(ostream &os, const Travel &obj);
        friend istream &operator >>(istream &is, Travel &obj);

        void setDestination(const char *destination);
        void setFromDate(const Date &from);
        void setToDate(const Date &to);
        void setGrade(const unsigned short grade);
        void setComment(const char *comment);
        void setPhotos(const char *photos);

        char *getDestination() const;
        Date getFromDate() const;
        Date getToDate() const;
        unsigned char getGrade() const;
        char *getComment() const;
        char *getPhotos() const;

};
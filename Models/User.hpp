#pragma once

#include "Travel.hpp"

class User
{
    private:
        char *username;
        char *password;
        char *email;
        Travel *travels;
        
        void erase();
        void copy(const User &);

    public:
        User();
        User(const char *, const char *, const char *);
        User(const User &);
        ~User();

        User &operator =(const User &);
        friend ostream &operator <<(ostream &, const User &) const;
        friend istream &operator >>(istream &, User &);

        void write(ofstream &ofs) const;
        void read(ifstream &ifs);

        void addTravel(const Travel *);

        void setUsername(const char *username);

}
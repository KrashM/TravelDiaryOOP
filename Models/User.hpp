#pragma once

#include "Travel.hpp"
#include "../../includes/Vector.h"

class User{

    private:
        char *username;
        char *password;
        char *email;
        Vector<Travel> travels;
        
        void erase();
        void copy(const User &);

    public:
        User();
        User(const char *, const char *, const char *);
        User(const User &);
        ~User();

        User &operator =(const User &);

        void write(ofstream &) const;
        void read(ifstream &);

        void addTravel(const Travel &);

        void setUsername(const char *);
        void setPassword(const char *);
        void setEmail(const char *);

        char *getUsername() const;
        char *getPassword() const;
        char *getEmail() const;

        static void validateUsername(const char *, Vector<User> &);
        static void validatePassword(const char *);
        static void validateEmail(const char *);

        const char *toString() const;

};
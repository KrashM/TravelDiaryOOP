#include "User.hpp"
#include "InvalidFormatException.hpp"

void User::erase(){

    delete[] this -> username;
    delete[] this -> password;
    delete[] this -> email;

}

void User::copy(const User &other){

    this -> username = new char[strlen(other.username) + 1];
    strcpy(this -> username, other.username);
    this -> password = new char[strlen(other.password) + 1];
    strcpy(this -> password, other.password);
    this -> email = new char[strlen(other.email) + 1];
    strcpy(this -> email, other.email);
    this -> travels = other.travels;

}

User::User(): username(nullptr), password(nullptr), email(nullptr){}
User::User(const char *username, const char *password, const char *email){

    this -> username = new char[strlen(username) + 1];
    strcpy(this -> username, username);
    this -> password = new char[strlen(password) + 1];
    strcpy(this -> password, password);
    this -> email = new char[strlen(email) + 1];
    strcpy(this -> email, email);

}
User::User(const User &other){ this -> copy(other); }
User::~User(){ this -> erase(); }

User &User::operator =(const User &other){

    if(this != &other){

        this -> erase();
        this -> copy(other);

    }

    return *this;

}

void User::write(ofstream &ofs) const{

    size_t usernameLenght = strlen(this -> username);
    ofs.write((const char *)&usernameLenght, sizeof(size_t));
    ofs.write(this -> username, usernameLenght);

    size_t passwordLenght = strlen(this -> password);
    ofs.write((const char *)&passwordLenght, sizeof(size_t));
    ofs.write(this -> password, passwordLenght);

    size_t emailLenght = strlen(this -> email);
    ofs.write((const char *)&emailLenght, sizeof(size_t));
    ofs.write(this -> email, emailLenght);

}
void User::read(ifstream &ifs){

    size_t usernameLenght;
    ifs.read((char *)&usernameLenght, sizeof(size_t));
    this -> username = new char[usernameLenght + 1];
    ifs.read(this -> username, usernameLenght);
    this -> username[usernameLenght] = '\0';
    
    size_t passwordLenght;
    ifs.read((char *)&passwordLenght, sizeof(size_t));
    this -> password = new char[passwordLenght + 1];
    ifs.read(this -> password, passwordLenght);
    this -> username[passwordLenght] = '\0';
    
    size_t emailLenght;
    ifs.read((char *)&emailLenght, sizeof(size_t));
    this -> email = new char[emailLenght + 1];
    ifs.read(this -> email, emailLenght);
    this -> username[emailLenght] = '\0';

}

void User::addTravel(const Travel &travel){ this -> travels.pushBack(travel); }

void User::setUsername(const char *username){ this -> username = new char[strlen(username) + 1]; strcpy(this -> username, username); }
void User::setPassword(const char *password){ this -> password = new char[strlen(password) + 1]; strcpy(this -> password, password); }
void User::setEmail(const char *email){ this -> email = new char[strlen(email) + 1]; strcpy(this -> email, email); }

char *User::getUsername() const{ return this -> username; }
char *User::getPassword() const{ return this -> password; }
char *User::getEmail() const{ return this -> email; }

void User::validateUsername(const char *username, Vector<User> users){

    for(size_t i = 0; i < users.size(); i++)
        if(!strcmp(users[i].getUsername(), username)) throw InvalidFormatException("Username exists");

}

bool contains(const char *symbols, const char symbol){

    bool flag = false;
    for(size_t i = 0; i < strlen(symbols); i++)
        flag = flag || symbols[i] == symbol;

    return flag;

}

void User::validatePassword(const char *password){

    const char lowerCaseLetters[] = "abcdefghijklmnopqrstuvwxyz";
    const char upperCaseLetters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char digits[] = "0123456789";
    const char otherChars[] = "~`!@#$%^&*()_-+={[}]|\\:;\"\'<,>.?/";

    bool hasLowerCase = false, hasUpperCase = false, hasDigit = false, hasOtherChar = false;

    for(size_t i = 0; i < strlen(password); i++){

        if(hasLowerCase && hasUpperCase && hasDigit && hasOtherChar) return;

        hasLowerCase = hasLowerCase || contains(lowerCaseLetters, password[i]);
        hasUpperCase = hasUpperCase || contains(upperCaseLetters, password[i]);
        hasDigit = hasDigit || contains(digits, password[i]);
        hasOtherChar = hasOtherChar || contains(otherChars, password[i]);

    }

    if(!(hasLowerCase && hasUpperCase && hasDigit && hasOtherChar)) throw InvalidFormatException("Password does not meet requirements!");

}

void User::validateEmail(const char *email){

    char mailEnding[] = "@mail.bg";
    bool flag = false;
    size_t index = 0;
    for(size_t i = 0; i < strlen(email); i++)
        if(!flag && email[i] == mailEnding[index]) flag = true;
        else if(flag && email[i] != mailEnding[++index]) throw InvalidFormatException("Email is invalid");

    if(!flag) throw InvalidFormatException("Email is invalid");

}
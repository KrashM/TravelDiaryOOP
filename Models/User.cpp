#include "User.hpp"

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

void User::createUserDB() const{

    char *path = new char[strlen(this -> username) + 13];
    strcpy(path, "Database/");
    strcat(path, this -> username);
    strcat(path, ".db");
    ofstream { path };

}

User::User(): username(nullptr), password(nullptr), email(nullptr){}
User::User(const char *username, const char *password, const char *email){

    User::validateUsername(username);
    User::validatePassword(password);
    User::validateEmail(email);

    this -> username = new char[strlen(username) + 1];
    strcpy(this -> username, username);
    this -> password = new char[strlen(password) + 1];
    strcpy(this -> password, password);
    this -> email = new char[strlen(email) + 1];
    strcpy(this -> email, email);

    this -> createUserDB();

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

void User::setUsername(const char *username){ this -> username = new char[strlen(username) + 1]; strcpy(this -> username, username); }
void User::setPassword(const char *password){ this -> password = new char[strlen(password) + 1]; strcpy(this -> password, password); }
void User::setEmail(const char *email){ this -> email = new char[strlen(email) + 1]; strcpy(this -> email, email); }
void User::addTravel(const Travel &travel){ this -> travels.pushBack(travel); }

char *User::getUsername() const{ return this -> username; }
char *User::getPassword() const{ return this -> password; }
char *User::getEmail() const{ return this -> email; }
Vector<Travel> User::getTravels() const{ return this -> travels; }

void User::validateUsername(const char *username){

    const size_t usernameSize = strlen(username);
    for(size_t i = 0; i < usernameSize; i++)
        if(!(StringChecker::isLower(username[i])
        || StringChecker::isUpper(username[i])
        || StringChecker::isDigit(username[i])))
            throw InvalidFormatException("Username contains unknown characters");

    // Other way is to check if database exists for the given user
    char *path = new char[strlen(username) + 13];
    strcpy(path, "Database/");
    strcat(path, username);
    strcat(path, ".db");
    ifstream temp(path);
    bool exists = temp.good();
    temp.close();
    if(exists) throw InvalidFormatException("Username exists");

    // Check if username exists in the user database
    // Vector<User> users;
    // ifstream ifs("Database/users.db", ios::binary);

    // while(ifs.peek() != EOF){

    //     User temp;
    //     temp.read(ifs);
    //     users.pushBack(temp);

    // }

    // ifs.close();

    // for(size_t i = 0; i < users.size(); i++)
    //     if(!strcmp(users[i].getUsername(), username)) throw InvalidFormatException("Username exists");

}

void User::validatePassword(const char *password){ if(!StringChecker::isPassword(password)) throw InvalidFormatException("Password does not meet requirements!"); }
void User::validateEmail(const char *email){ if(!StringChecker::isEmail(email)) throw InvalidFormatException("Email is invalid"); }

Vector<User> User::getUsersFromDB(){

    Vector<User> users;
    ifstream ifs("Database/users.db", ios::binary);

    while(ifs.peek() != EOF){

        User temp;
        temp.read(ifs);
        users.pushBack(temp);

    }

    ifs.close();

    return users;

}

const char *User::toString() const{

    char *result = new char[strlen(this -> username) + strlen(this -> password) + strlen(this -> email) + 3];
    strcpy(result, this -> username);
    strcat(result, " ");
    strcat(result, this -> password);
    strcat(result, " ");
    strcat(result, this -> email);
    strcat(result, "\0");

    return result;

}
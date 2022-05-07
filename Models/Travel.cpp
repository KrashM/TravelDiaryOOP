#include "Travel.hpp"

void Travel::erase(){

    delete[] this -> destination;
    delete[] this -> comment;

}

void Travel::copy(const Travel &other){

    this -> destination = new char[strlen(other.destination) + 1];
    strcpy(this -> destination, other.destination);

    this -> from = other.from;
    this -> to = other.to;

    this -> grade = other.grade;

    this -> comment = new char[strlen(other.comment) + 1];
    strcpy(this -> comment, other.comment);

    this -> photos = other.photos;

}

Travel::Travel(): destination(new char[1]), from(Date()), to(Date()), grade(0), comment(new char[1]){}
Travel::Travel(const char *destination, const Date &from, const Date &to, const unsigned char grade, const char *comment, const Vector<char *> &photos){

    if(to > from) throw InvalidFormatException("To date is before from date");
    if(grade < 0 || grade > 5) throw InvalidFormatException("Grade is invalid");
    for(size_t i = 0; i < photos.size(); i++)
        if(!StringChecker::isPhoto(photos[i]))
            throw InvalidFormatException("Photo is invalid");

    this -> destination = new char[strlen(destination) + 1];
    strcpy(this -> destination, destination);

    this -> from = from;
    this -> to = to;

    this -> grade = grade;

    this -> comment = new char[strlen(comment) + 1];
    strcpy(this -> comment, comment);

    this -> photos = photos;

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

    os << obj.destination << '\n' << obj.from << '\n' << obj.to << '\n' << (int)obj.grade << "\nComment\n" << obj.comment << "\nPhotos\n" << obj.photos;
    return os;

}

istream &operator >>(istream &is, Travel &obj){

    // Edit this to work with text formating
    // P.S. It's very error prone
    std::string temp;
    is >> temp >> temp >> temp >> temp >> temp >> temp >> temp;
    std::cout << temp << '\n';
    is >> obj.destination >> obj.from >> obj.to >> obj.grade >> obj.comment;
    return is;

}

void Travel::write(ofstream &ofs) const{

    size_t destSize = strlen(this -> destination);
    ofs.write((const char *)&destSize, sizeof(size_t));
    ofs.write(this -> destination, destSize);

    ofs.write((const char *)&this -> from, sizeof(Date));

    ofs.write((const char *)&this -> to, sizeof(Date));
    
    ofs.write((const char *)&this -> grade, sizeof(unsigned char));

    size_t commentSize = strlen(this -> comment);
    ofs.write((const char *)&commentSize, sizeof(size_t));
    ofs.write(this -> comment, commentSize);

    // size_t photosSize = photos.size();
    // ofs.write((const char *)&photosSize, sizeof(size_t));
    ofs.write((const char*)&this -> photos, sizeof(Vector<char *>));

}

void Travel::read(ifstream &ifs){

    size_t destSize;
    ifs.read((char *)&destSize, sizeof(size_t));

    this -> destination = new char[destSize + 1];
    ifs.read(this -> destination, destSize);
    this -> destination[destSize] = '\0';

    ifs.read((char *)&this -> from, sizeof(Date));
    ifs.read((char *)&this -> to, sizeof(Date));
    ifs.read((char *)&this -> grade, sizeof(unsigned char));

    size_t commentSize;
    ifs.read((char *)&commentSize, sizeof(size_t));

    this -> comment = new char[commentSize + 1];
    ifs.read(this -> comment, commentSize);
    this -> comment[commentSize] = '\0';
    
    // size_t photosSize;
    // ifs.read((char *)&photosSize, sizeof(size_t));

    // this -> photos = new char[photosSize + 1];
    // ifs.read(this -> photos, photosSize);
    // this -> photos[photosSize] = '\0';

    ifs.read((char *)&this -> photos, sizeof(Vector<char *>));

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
void Travel::setPhotos(const Vector<char *> &photos){ this -> photos = photos; }

char *Travel::getDestination() const{ return this -> destination; }
Date Travel::getFromDate() const{ return this -> from; }
Date Travel::getToDate() const{ return this -> to; }
unsigned char Travel::getGrade() const{ return this -> grade; }
char *Travel::getComment() const{ return this -> comment; }
Vector<char *> Travel::getPhotos() const{ return this -> photos; }
#include "Context.hpp"

Vector<User> Context::getUsersFromDB(){

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
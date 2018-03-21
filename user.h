#ifndef USER_H
#define USER_H

//C++

//Qt
#include "QString"
//ADT
#include "genlist.h"
#include "permission.h"
#include "abs_data.h"
#include <QMessageBox>

class User{

public:

    int VrPos;
    UserInfo* UserData;
    GenList<Permission*>* NuclearList;

    //(^< ............ ............ ............ Constructor: Set
    User(UserInfo* UserData){
        this->VrPos       = 0;
        this->UserData    = UserData;
        this->NuclearList = new GenList<Permission*>();
    }
};

#endif // USER_H

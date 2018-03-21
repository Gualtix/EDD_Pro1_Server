#ifndef PERMISSION_H
#define PERMISSION_H

//C++

//Qt

//ADT
#include "genlist.h"
#include "abs_data.h"

class Permission{

public:

    int HrPos;
    int VrPos;
    PermissionInfo* PermissionData;
    //Links
    Permission* Previous;
    Permission* Next;
    Permission* Top;
    Permission* Bottom;

    //(^< ............ ............ ............ Constructor: Default NULL
    Permission(){
        this->PermissionData   = NULL;
        this->Previous    = NULL;
        this->Next        = NULL;
        this->Top         = NULL;
        this->Bottom      = NULL;
    }

    //(^< ............ ............ ............ Constructor: Set
    Permission(int HrPos,int VrPos,PermissionInfo* PermissionData){
        this->HrPos = HrPos;
        this->VrPos = VrPos;
        this->PermissionData = PermissionData;
    }

    //(^< ............ ............ ............ Constructor: Set
    Permission(PermissionInfo* PermissionData){
        this->PermissionData = PermissionData;
    }
};

#endif // PERMISSION_H

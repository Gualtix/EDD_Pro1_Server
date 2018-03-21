#ifndef ARCHIVE_H
#define ARCHIVE_H

//C++

//Qt
#include "QString"
//ADT
#include "genlist.h"
#include "permission.h"
#include "abs_data.h"

class Archive{

public:

    int HrPos;
    ArchiveInfo* ArchiveData;
    GenList<Permission*>* NuclearList;

    //(^< ............ ............ ............ Constructor: Set
    Archive(ArchiveInfo* ArchiveData){
        this->HrPos       = 0;
        this->ArchiveData = ArchiveData;
        this->NuclearList = new GenList<Permission*>();
    }
};

#endif // ARCHIVE_H

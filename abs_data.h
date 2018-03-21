#ifndef ABS_DATA_H
#define ABS_DATA_H

#include "QString"

class GraphInfo{

public:
    QString TAG     = "";
    QString NODE_ID = "";

    int ARCH_INDEX   = 0;
};

class ArchiveInfo : public GraphInfo{
public:

    QString Name;
    QString Type;
    QString Creator;
    QString Creation_Date;
    QString Modification_Date;
    QString Modifier_Nickname;
    QString State;
    QString JSon_URL;

    //(^< ............ ............ ............ Constructor: Default NULL
    ArchiveInfo(){
        this->Name = "";
        this->Type = "";
        this->Creator = "";
        this->Creation_Date = "";
        this->Modification_Date = "";
        this->Modifier_Nickname = "";
        this->State = "";
        this->JSon_URL = "";
    }

    //(^< ............ ............ ............ Constructor: Set
    //ArchiveInfo(){

    //}
};

class UserInfo : public GraphInfo{

public:

    QString Name;
    QString EMail;
    QString Nickname;
    QString Password;
    //Lista de Archivos que lo Preceden


    //(^< ............ ............ ............ Constructor: Default NULL
    UserInfo(){
        this->Name = "";
        this->EMail = "";
        this->Nickname = "";
        this->Password = "";
    }

    //(^< ............ ............ ............ Constructor: Set
    //UserInfo(){

    //}
};

class PermissionInfo : public GraphInfo{
public:


    QString ARCH;
    QString USR;
    QString Type;

    //(^< ............ ............ ............ Constructor: Default NULL
    PermissionInfo(){
        this->ARCH = "";
        this->USR = "";
        this->Type = "";
    }

    //(^< ............ ............ ............ Constructor: Set
    //PermissionInfo(int ID,double Nota,QString Feedback){

    //}
};

#endif // ABS_DATA_H

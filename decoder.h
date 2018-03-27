#ifndef DECODER_H
#define DECODER_H

//C++

//Qt
#include "QDebug"

//ADT
#include "genlist.h"
#include "mystring.h"
#include "sparsematrix.h"
#include "static_storage.h"
#include "mainwindow.h"


class Decoder{

public:

    GenList<MyString*>* WList;

    //(^< ............ ............ ............ Constructor: Default
    Decoder(){
        WList = new GenList<MyString*>();
    }

    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    //(^< ............ ............ ............ ............ ............ Tools
    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

    void GetStack_of_Instructions(QString msg){

        int cnt = 0;
        QString Tomcat = "";
        QString Ch = "";

        while(cnt < msg.size()){

            Ch = msg.mid(cnt,1);

            if(Ch == "#"){
                WList->EndInsert(new MyString(Tomcat));
                Tomcat = "";
            }
            else{
                Tomcat.append(Ch);
            }
            cnt++;
        }
    }

    QString Answer_Request(SparseMatrix* Mtx){

        if(WList->ListSize > 0){
            QString Req = WList->First->Data->Cad;
            if(Req == "Log_In"){
                if(Log_In(Mtx)){
                    return "Log_In#SUCCESS#New User Successfully Registered#";
                }
                return "Log_In#ERROR#New User Nickname is Already in Use, Please Try Again...#";
            }
            else if(Req == "Sign_In"){
                if(Sign_In(Mtx)){
                    return "Sign_In#SUCCESS#Welcome to Shared Files Management#";
                }
                return "Sign_In#ERROR#Password dont Match with Nickname, Please Try Again...#";
            }
            else if(Req == "Get_User_Files"){
                return Get_User_Files(Mtx);
            }
            else if(Req == "Get_File_Content"){

            }
            else if(Req == "Create_File"){

            }
            else if(Req == "Block_File"){

            }
            else if(Req == "Release_File"){

            }
            else if(Req == "Save_File"){

            }
        }

        return "ERROR#Peticion No Aceptada#";
    }

    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    //(^< ............ ............ ............ ............ ............ APP
    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

    QString Get_User_Files(SparseMatrix* Mtx){

        QString Answer = "Get_User_Files";
        Answer.append("#");

        GeNode<User*>* Us = Mtx->Get_I_User_Header_Node_By_String(Static_Storage::Nickname);
        GenList<Permission*>* NL = Us->Data->NuclearList;

        Answer.append(QString::number(NL->ListSize));
        Answer.append("#");

        if(NL->ListSize > 0){

            //GenList<Archive*>* ArList = new GenList<Archive*>();
            //GenList<MyString*>* PermList = new GenList<MyString*>();

            int cnt = 0;
            GeNode<Permission*>* Tmp = NL->First;
            while(cnt < NL->ListSize){

                Archive* ArInfo = Mtx->Get_J_Archive_Header_Node_By_String(Tmp->Data->PermissionData->ARCH)->Data;
                QString Permiso = Tmp->Data->PermissionData->Type;

                Answer.append(Permiso);
                Answer.append("#");

                Answer.append(ArInfo->ArchiveData->Name);
                Answer.append("#");

                Answer.append(ArInfo->ArchiveData->Type);
                Answer.append("#");

                Answer.append(ArInfo->ArchiveData->Creator);
                Answer.append("#");

                Answer.append(ArInfo->ArchiveData->Creation_Date);
                Answer.append("#");

                Answer.append(ArInfo->ArchiveData->Creation_Date);
                Answer.append("#");

                Answer.append(ArInfo->ArchiveData->Modifier_Nickname);
                Answer.append("#");

                Answer.append(ArInfo->ArchiveData->Modification_Date);
                Answer.append("#");

                Answer.append(ArInfo->ArchiveData->JSon_URL);
                Answer.append("#");

                Answer.append("^");
                Answer.append("#");

                Tmp = Tmp->Next;
                cnt++;
            }
        }

        return Answer;
    }

    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    //(^< ............ ............ ............ ............ ............ Login
    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............


    bool Log_In(SparseMatrix* Mtx){

        QString Nick = WList->GetNode(1)->Data->Cad;
        QString Pass = WList->GetNode(2)->Data->Cad;

        GeNode<User*>* UsNode = Mtx->Get_I_User_Header_Node_By_String(Nick);

        if(UsNode && UsNode->Data->UserData->Password == Pass){
            Static_Storage::Nickname = Nick;
            return true;
        }

        return false;
    }

    bool Sign_In(SparseMatrix* Mtx){

        QString Nick = WList->GetNode(1)->Data->Cad;
        if(!Mtx->Get_I_User_Header_Node_By_String(Nick)){
            UserInfo* UsInfo = new UserInfo();

            UsInfo->Nickname = Nick;
            UsInfo->Password = WList->GetNode(2)->Data->Cad;
            UsInfo->Name = WList->GetNode(3)->Data->Cad;
            UsInfo->EMail = WList->GetNode(4)->Data->Cad;

            //TAG
            UsInfo->TAG = UsInfo->Nickname;

            User* USR = new User(UsInfo);
            Mtx->LstVertical->EndInsert(USR);
            Mtx->LstVertical->Last->TAG = UsInfo->Name;
            Mtx->LstVertical->Last->NICK = UsInfo->Nickname;
            Mtx->LstVertical->Last->Data->VrPos = Mtx->LstVertical->ListSize;

            Static_Storage::Nickname = Nick;
            return true;

        }

        return false;
    }
};

#endif // DECODER_H

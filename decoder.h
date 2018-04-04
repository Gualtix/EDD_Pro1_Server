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
    int Num_Files = -1;
    int Num_Users = -1;

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
                    Static_Storage::Repy_Status = "SUCCESS";
                    return "Log_In#SUCCESS#Welcome to Shared Files Management#";
                    //return "Log_In#SUCCESS#";
                }
                Static_Storage::Repy_Status = "FAIL";
                return "Log_In#ERROR#New User Nickname is Already in Use, Please Try Again...#";
                //return "Log_In#ERROR#";
            }



            else if(Req == "Sign_In"){
                if(Sign_In(Mtx)){
                    Static_Storage::Repy_Status = "SUCCESS";
                    return "Sign_In#SUCCESS#New User Successfully Registered#";
                    //return "Sign_In#SUCCESS#";
                }
                Static_Storage::Repy_Status = "FAIL";
                return "Sign_In#ERROR#Password dont Match with Nickname, Please Try Again...#";
            }



            else if(Req == "Get_User_Files"){

                QString Ans = Get_User_Files(Mtx);
                Static_Storage::Repy_Status = QString::number(Num_Files)+" File(s) were sent";
                return Ans;
            }



            else if(Req == "Get_File_Content"){
                QString JSon_URL = WList->GetNode(1)->Data->Cad;
                QString Ans = Get_File_Content(JSon_URL);
                if(!Ans.size() == 18){
                    Static_Storage::Repy_Status = "JSon Content Send";
                    return Ans;
                }
                Static_Storage::Repy_Status = "File Requested Not Found";
                return "Get_User_Files#ERROR#";
            }



            else if(Req == "Get_Available_Users"){
                QString Ans = Get_Available_Users(Mtx);
                Static_Storage::Repy_Status = QString::number(Num_Users)+" User(s) Nickname(s) were sent";
                return Ans;
            }



            else if(Req == "Create_File"){
                QString FileName = WList->GetNode(2)->Data->Cad;
                if(Create_File(FileName,Mtx)){
                    QString Ans = "Create_File#SUCCESS#New File Successfully Created#";
                    Static_Storage::Repy_Status = "SUCCESS";
                    return Ans;
                }
                    Static_Storage::Repy_Status = "FAIL";
                    return "Create_File#ERROR#File Name Alrady Exist#";
            }

            else if(Req == "Delete_File"){
                QString FileName = WList->GetNode(2)->Data->Cad;
                if(Delete_File(FileName,Mtx)){
                    QString Ans = "Delete_File#SUCCESS#File "+FileName+" was Deleted#";
                    Static_Storage::Repy_Status = "SUCCESS";
                    return Ans;
                }
                Static_Storage::Repy_Status = "FAIL";
                return "Delete_File#ERROR#File could not be Deleted#";
            }



            else if(Req == "Get_Permission"){
                QString FileName = WList->GetNode(2)->Data->Cad;
                QString Ans = Get_Permission(FileName,Mtx);
                return Ans;

            }


            else if(Req == "Update_Permission"){
                QString FileName = WList->GetNode(2)->Data->Cad;
                Update_Permission(FileName,Mtx);
                return "Get_Permission#SUCCESS#File Permision Updated#";
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

    bool Update_Permission(QString File_Name,SparseMatrix* Mtx){

        //(^< ............ D E L E T E
        int cnt = 0;
        while(cnt < Mtx->LstVertical->ListSize){
            QString Us = Mtx->LstVertical->GetNode(cnt)->Data->UserData->Nickname;
            GeNode<Permission*>* ND = Mtx->Get_J_I_Node_By_String(File_Name,Us);
            if(ND != NULL && ND->Data->PermissionData->Type != "dueño"){
                Mtx->DeleteNode_By_String(File_Name,Us);
            }
            cnt++;
        }

        //(^< ............ A D D
        int NP = WList->GetNode(3)->Data->Cad.toInt();
        cnt = 4;
        while(cnt < ((NP * 2) + 4)){

            QString User_Name = WList->GetNode(cnt)->Data->Cad;
            QString Type = WList->GetNode(cnt+1)->Data->Cad;

            Add_New_Permission(Mtx,User_Name,File_Name,Type);

            cnt++;
            cnt++;
        }
    }

    QString Get_Permission(QString File_Name,SparseMatrix* Mtx){
        QString Answer = "Get_Permission";
        Answer.append("#");

        Answer.append(File_Name);
        Answer.append("#");

        GeNode<Archive*>* ND = Mtx->LstHorizontal->GetNode_By_String(File_Name);

        int NPer = ND->Data->NuclearList->ListSize;

        if(NPer == 1){
            NPer = 0;
        }
        else if (NPer > 1){
            NPer--;
        }

        Answer.append(QString::number(NPer));
        Answer.append("#");

        int cnt = 0;
        //while(cnt < ND->Data->NuclearList->ListSize){
        while(cnt < (NPer + 1)){

            QString Nick = ND->Data->NuclearList->GetNode(cnt)->Data->PermissionData->USR;
            QString Type = ND->Data->NuclearList->GetNode(cnt)->Data->PermissionData->Type;

            if(Type != "dueño"){
                Answer.append(Nick);
                Answer.append("#");

                Answer.append(Type);
                Answer.append("#");
            }

            cnt++;
        }

        return Answer;
    }

    bool Delete_File(QString File_Name,SparseMatrix* Mtx){
        int cnt = 0;
        while(cnt < Mtx->LstVertical->ListSize){
            QString Us = Mtx->LstVertical->GetNode(cnt)->Data->UserData->Nickname;
            GeNode<Permission*>* ND = Mtx->Get_J_I_Node_By_String(File_Name,Us);
            if(ND != NULL){
                Mtx->DeleteNode_By_String(File_Name,Us);
            }
            cnt++;
        }

        int CR = Mtx->LstHorizontal->GetNode_By_String(File_Name)->CORREL;
        Mtx->LstHorizontal->DeleteNode(CR);
    }

    bool Create_File(QString File_Name,SparseMatrix* Mtx){

        if(!Mtx->LstHorizontal->GetNode_By_Nickname(File_Name)){

            ArchiveInfo* AR_Data = new ArchiveInfo();

            AR_Data->Name = WList->GetNode(2)->Data->Cad;
            AR_Data->Creator = WList->GetNode(3)->Data->Cad;
            AR_Data->Creation_Date = WList->GetNode(4)->Data->Cad;
            AR_Data->Modifier_Nickname = WList->GetNode(5)->Data->Cad;
            AR_Data->Modification_Date = WList->GetNode(6)->Data->Cad;
            AR_Data->Type = WList->GetNode(7)->Data->Cad;
            //AR_Data->Permiso = WList->GetNode(8)->Data->Cad;
            AR_Data->State = WList->GetNode(9)->Data->Cad;
            AR_Data->JSon_URL = WList->GetNode(10)->Data->Cad;

            AR_Data->TAG = AR_Data->Name;

            Archive* AR = new Archive(AR_Data);

            Mtx->LstHorizontal->EndInsert(AR);
            Mtx->LstHorizontal->Last->NICK = AR_Data->Name;
            Mtx->LstHorizontal->Last->TAG = AR_Data->Name;
            Mtx->LstHorizontal->Last->Data->HrPos = Mtx->LstHorizontal->ListSize - 1;

            //(^< ............ ............ ............ ............ ............ P E R M I S O S
            QString Arch_Name = AR->ArchiveData->Name;

            int NP = WList->GetNode(11)->Data->Cad.toInt();

            //(^< ............ ............ ............ ............ ............ Sin permisos
            if(NP == 0){
                QString US = WList->GetNode(1)->Data->Cad;
                QString AR = WList->GetNode(2)->Data->Cad;
                Add_New_Permission(Mtx,US,AR,"dueño");
                return true;
            }

            QString TR = "NOT";

            int cnt = 12;
            while(cnt < ((NP * 2) + 12)){


                QString User_Name = WList->GetNode(cnt)->Data->Cad;
                QString Type = WList->GetNode(cnt+1)->Data->Cad;

                //(^< ............ ............ ............ ............ ............ Dueño Incluido
                if(User_Name == WList->GetNode(1)->Data->Cad){
                    Type = "dueño";
                    TR = User_Name;
                }

                Add_New_Permission(Mtx,User_Name,Arch_Name,Type);

                cnt++;
                cnt++;
            }

            //(^< ............ ............ ............ ............ ............ Dueño NO Incluido
            if(TR == "NOT"){
                QString US = WList->GetNode(1)->Data->Cad;
                QString AR = WList->GetNode(2)->Data->Cad;
                Add_New_Permission(Mtx,US,AR,"dueño");
                return true;
            }

            return true;
        }

        return false;
    }

    void Add_New_Permission(SparseMatrix* Mtx,QString US,QString AR,QString TP){
        PermissionInfo* NewPermInfo = new PermissionInfo();

        NewPermInfo->USR = US;
        NewPermInfo->ARCH = AR;
        NewPermInfo->Type = TP;
        NewPermInfo->TAG = TP;

        Permission* NewPerm = new Permission();
        NewPerm->PermissionData = NewPermInfo;

        Mtx->InsertNode_By_String(AR,US,NewPerm);
    }

    QString Get_Available_Users(SparseMatrix* Mtx){
        QString Answer = "Get_Available_Users";
        Answer.append("#");

        int cnt = 0;
        GeNode<User*>* Us = Mtx->LstVertical->First;

        if(Us != NULL){
            while(cnt < Mtx->LstVertical->ListSize){

                QString NK = Us->Data->UserData->Nickname;
                if(NK != Static_Storage::Nickname){
                    Answer.append(Us->Data->UserData->Nickname);
                    Answer.append("#");
                }

                Us = Us->Next;
                cnt++;
            }
        }

        return Answer;
    }

    QString Get_File_Content(QString JSon_URL){
        QString Answer = "Get_File_Content";
        Answer.append("#");

        //(^< ............ User Load
        QString Input_JSon_URL = JSon_URL;

        QFile MyFile(Input_JSon_URL);
        MyFile.open(QIODevice::ReadOnly | QIODevice::Text);

        QTextStream out(&MyFile);
        QString JSon_Plain_String = out.readAll();

        if(JSon_Plain_String.size() > 0){
            Answer.append("ERROR");
            Answer.append("#");
        }

        Answer.append(JSon_Plain_String);
        Answer.append("#");

        MyFile.close();

        return Answer;
    }

    QString Get_User_Files(SparseMatrix* Mtx){

        QString Answer = "Get_User_Files";
        Answer.append("#");

        GeNode<User*>* Us = Mtx->Get_I_User_Header_Node_By_String(Static_Storage::Nickname);
        GenList<Permission*>* NL = Us->Data->NuclearList;

        Answer.append(QString::number(NL->ListSize));
        Answer.append("#");

        Num_Files = NL->ListSize;

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

                Answer.append(ArInfo->ArchiveData->State);
                Answer.append("#");

                Answer.append(ArInfo->ArchiveData->Modifier_Nickname);
                Answer.append("#");

                Answer.append(ArInfo->ArchiveData->Modification_Date);
                Answer.append("#");

                Answer.append(ArInfo->ArchiveData->JSon_URL);
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
            Mtx->Update_JSon_Users(USR);
            return true;

        }

        return false;
    }
};

#endif // DECODER_H

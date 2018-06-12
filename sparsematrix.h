#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

//C++
#include <stdexcept>

//Qt
#include "QFile"
#include "QTextStream"
#include "QString"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>

//ADT
#include "archive.h"
#include "user.h"
#include "genlist.h"
#include "permission.h"
#include "myint.h"
#include "jsonreader.h"

class SparseMatrix{

public:

    int HrLimit;
    int VrLimint;
    int NodeCounter;

    GenList<Archive*>* LstHorizontal;
    GenList<User*>*    LstVertical;


    //(^< ............ ............ ............ Constructor: Set
    SparseMatrix(){
        this->HrLimit       = -1;
        this->VrLimint      = -1;
        this->NodeCounter   = 0;
        this->LstHorizontal = new GenList<Archive*>();
        this->LstVertical   = new GenList<User*>();
    }

    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    //(^< ............ ............ ............ ............ ............ Insert By QString
    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

    void InsertNode_By_String(QString Arch,QString Usr,Permission* Prog){

        GeNode<Archive*>* ND_AR = this->LstHorizontal->GetNode_By_String(Arch);
        GeNode<User*>* ND_US = this->LstVertical->GetNode_By_Nickname(Usr);

        int j = ND_AR->CORREL;
        int i = ND_US->CORREL;

        InsertNode(j,i,Prog);

    }

    void Update_to_NewNode_By_String(QString Arch,QString Usr,Permission* Prog){

        GeNode<Archive*>* ND_AR = this->LstHorizontal->GetNode_By_String(Arch);
        GeNode<User*>* ND_US = this->LstVertical->GetNode_By_Nickname(Usr);

        int j = ND_AR->CORREL;
        int i = ND_US->CORREL;

        Update_to_NewNode(j,i,Prog);
    }

    void DeleteNode_By_String(QString Arch,QString Usr){

        GeNode<Archive*>* ND_AR = this->LstHorizontal->GetNode_By_String(Arch);
        GeNode<User*>* ND_US = this->LstVertical->GetNode_By_Nickname(Usr);

        int j = ND_AR->CORREL;
        int i = ND_US->CORREL;

        DeleteNode(j,i);
    }

    GeNode<Permission*>* Get_J_I_Node_By_String(QString Arch,QString Usr){

        GeNode<Archive*>* ND_AR = this->LstHorizontal->GetNode_By_String(Arch);
        GeNode<User*>* ND_US = this->LstVertical->GetNode_By_Nickname(Usr);

        if(ND_AR != NULL && ND_US != NULL){
            int j = ND_AR->CORREL;
            int i = ND_US->CORREL;

            return Get_J_I_Node(j,i);
        }

        return NULL;
    }

    GeNode<Archive*>* Get_J_Archive_Header_Node_By_String(QString Arch){
        return this->LstHorizontal->GetNode_By_String(Arch);
    }

    GeNode<User*>* Get_I_User_Header_Node_By_String(QString Usr){
        return this->LstVertical->GetNode_By_Nickname(Usr);
    }

    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    //(^< ............ ............ ............ ............ ............ JSon-Handle
    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

    //(^< ............ ............ ............ Cargar Encabezado Horizontal: Archivos
    void Load_JSon_Horizontal_Headers(QString JSon_URL){

        if(JSon_URL.isEmpty())
            return;

        QFile MyFile(JSon_URL);

        if (!MyFile.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QByteArray BA = MyFile.readAll();

        GenList<PermissionInfo*>* LsPermInfo = new GenList<PermissionInfo*>();
        JSonReader::Load_Horizontal_Archives(BA,LstHorizontal,LsPermInfo);


        //(^< ............ Carga de Permisos
        int cnt = 0;
        while(cnt < LsPermInfo->ListSize){

            GeNode<PermissionInfo*>* INFO_NODE = LsPermInfo->GetNode(cnt);

            QString Arch = INFO_NODE->Data->ARCH;
            QString Usr = INFO_NODE->Data->USR;

            Permission* NW_PERM = new Permission();
            NW_PERM->PermissionData = INFO_NODE->Data;

            InsertNode_By_String(Arch,Usr,NW_PERM);

            cnt++;
        }
    }

    //(^< ............ ............ ............ Cargar Encabezado Vertical: Usuarios
    void Load_JSon_Vertical_Headers(QString JSon_URL){
        if(JSon_URL.isEmpty())
            return;

        QFile MyFile(JSon_URL);

        if (!MyFile.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QByteArray BA = MyFile.readAll();

        JSonReader::Load_Vertical_Users(BA,LstVertical);
    }

    //(^< ............ ............ ............ Actualizar JSon-Archives
    void Update_JSonArchives(){

        QString Js = "";

        if(LstHorizontal->ListSize > 0){
            Js.append("[\n");

            int cnt = 0;
            GeNode<Archive*>* Tmp;
            while(cnt < LstHorizontal->ListSize){
                Tmp = LstHorizontal->GetNode(cnt);

                Js.append("\t{\n");

                Js.append("\t\t\"nombre\": \""+Tmp->Data->ArchiveData->Name+"\",\n");
                Js.append("\t\t\"tipo\": \""+Tmp->Data->ArchiveData->Type+"\",\n");
                Js.append("\t\t\"creador\": \""+Tmp->Data->ArchiveData->Creator+"\",\n");
                Js.append("\t\t\"fecha_creacion\": \""+Tmp->Data->ArchiveData->Creation_Date+"\",\n");
                Js.append("\t\t\"modificador\": \""+Tmp->Data->ArchiveData->Modifier_Nickname+"\",\n");
                Js.append("\t\t\"fecha_modificacion\": \""+Tmp->Data->ArchiveData->Modification_Date+"\",\n");
                Js.append("\t\t\"ruta_contenido\": \""+Tmp->Data->ArchiveData->JSon_URL+"\",\n");

                Js.append("\t\t\"permisos\":\n");
                Js.append("\t\t\[\n");
                if(Tmp->Data->NuclearList->ListSize > 0){
                    int dnt = 0;
                    GeNode<Permission*>* Prm;
                    while(dnt < Tmp->Data->NuclearList->ListSize){
                        Prm = Tmp->Data->NuclearList->GetNode(dnt);
                        Js.append("\t\t\t{\n");

                        Js.append("\t\t\t\t\"usuario\":\""+Prm->Data->PermissionData->USR+"\",\n");
                        Js.append("\t\t\t\t\"permiso\":\""+Prm->Data->PermissionData->Type+"\"\n");

                        if(dnt == (Tmp->Data->NuclearList->ListSize - 1)){
                            Js.append("\t\t\t}\n");
                        }
                        else{
                            Js.append("\t\t\t},\n");
                        }
                        dnt++;
                    }
                }
                Js.append("\t\t\]\n");

                if(cnt == (LstHorizontal->ListSize - 1)){
                    Js.append("\t}\n");
                }
                else{
                    Js.append("\t},\n");
                }

                cnt++;
            }

            Js.append("]");

        }
        else{
            Js.append("Empty");
        }

        //(^< ............ Archive Update
        QString Output_JSon_URL = "ARCH_DIR/archivos.json";
        QFile Fl(Output_JSon_URL);
        if (Fl.open(QFile::WriteOnly)) {
            QTextStream stream(&Fl);
            stream << Js << endl;
            Fl.close();
        }
    }

    //(^< ............ ............ ............ Actualizar JSon-Users
    void Update_JSon_Users(User* NewUser){

        //(^< ............ User Load
        QString Input_JSon_URL = "US_DIR/usuarios.json";

        QFile MyFile(Input_JSon_URL);
        MyFile.open(QIODevice::ReadOnly | QIODevice::Text);

        QTextStream out(&MyFile);
        QString JSon_Plain_String = out.readAll();

        MyFile.close();

        //(^< ............ Adjustment
        QString Ls = JSon_Plain_String.right(1);
        if(Ls == "\n"){
            //JSon_Plain_String.remove(JSon_Plain_String.size() - 1,1);
            JSon_Plain_String.chop(1);
        }

        //(^< ............ Edit
        //int Last_Char_Pos = JSon_Plain_String.size() - 1;
        //JSon_Plain_String.remove(Last_Char_Pos-1,2);
        JSon_Plain_String.chop(1);
        JSon_Plain_String.chop(1);

        JSon_Plain_String.append(",\n");
        JSon_Plain_String.append("\t{\n");

        JSon_Plain_String.append("\t\t\"nombre\":\""+NewUser->UserData->Name+"\",\n");
        JSon_Plain_String.append("\t\t\"correo\":\""+NewUser->UserData->EMail+"\",\n");
        JSon_Plain_String.append("\t\t\"nickname\":\""+NewUser->UserData->Nickname+"\",\n");
        JSon_Plain_String.append("\t\t\"clave\":\""+NewUser->UserData->Password+"\"\n");

        JSon_Plain_String.append("\t}\n");
        JSon_Plain_String.append("]");

        //(^< ............ User Update
        QString Output_JSon_URL = "US_DIR/usuarios.json";
        QFile Fl(Output_JSon_URL);
        if (Fl.open(QFile::WriteOnly)) {
            QTextStream stream(&Fl);
            stream << JSon_Plain_String << endl;
            Fl.close();
        }
    }

    //(^< ............ ............ ............ Actualizar JSon-Document

    //(^< ............ ............ ............ Actualizar JSon-Canvas

    //(^< ............ ............ ............ Actualizar JSon-Presentation


    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    //(^< ............ ............ ............ ............ ............ Ordering
    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

    //(^< ............ ............ ............ ............ ............ Obtener Nodo Cabecera: Vr = i , Hr = j

    //(^< ............ ............ ............ Get_i_Header
    GeNode<User*>* Get_i_Header_Vertical(int i){
        GeNode<User*>* TmpNode = LstVertical->First;
        int cnt = 0;
        while(cnt < LstVertical->ListSize){
            if(TmpNode->Data->VrPos == i){
                return TmpNode;
            }
            TmpNode = TmpNode->Next;
            cnt++;
        }
        return NULL;
    }

    //(^< ............ ............ ............ Get_j_Header
    GeNode<Archive*>* Get_j_Header_Horizontal(int j){
        GeNode<Archive*>* TmpNode = LstHorizontal->First;
        int cnt = 0;
        while(cnt < LstHorizontal->ListSize){
            if(TmpNode->Data->HrPos == j){
                return TmpNode;
            }
            TmpNode = TmpNode->Next;
            cnt++;
        }
        return NULL;
    }

    //(^< ............ ............ ............ ............ ............ Indices de Insercion Ordenada en Cabeceras

    //(^< ............ ............ ............ Obtener Indice de Insercion Horizontal
    int GetHorizontal_OrderedIndex(int Hx){
        int cnt = 0;
        int LSize = LstHorizontal->ListSize;
        GeNode<Archive*>* TmpNode = LstHorizontal->First;
        while(cnt < LSize){
            if(TmpNode->Data->HrPos > Hx){
                return cnt;
            }
            TmpNode = TmpNode->Next;
            cnt++;
        }
        return LSize;
    }

    //(^< ............ ............ ............ Obtener Indice de Insercion Vertical
    int GetVertical_OrderedIndex(int Vx){

        int cnt = 0;
        int LSize = LstVertical->ListSize;
        GeNode<User*>* TmpNode = LstVertical->First;
        while(cnt < LSize){
            if(TmpNode->Data->VrPos > Vx){
                return cnt;
            }
            TmpNode = TmpNode->Next;
            cnt++;
        }
        return LSize;
    }

    //(^< ............ ............ ............ ............ ............ Indices de Insercion Ordenada en Listas Internas

    //(^< ............ ............ ............ Obtener Indice Lista Hr
    int GetInside_HrPos_OrderedIndex(int Vx,GenList<Permission*>* NuclearList){

        int cnt = 0;
        int LSize = NuclearList->ListSize;
        GeNode<Permission*>* TmpProg = NuclearList->First;
        while (cnt < LSize) {
            //if(TmpProg->Data->VrPos > Vx){
            if(TmpProg->Data->VrPos >= Vx){
                return cnt;
            }
            TmpProg = TmpProg->Next;
            cnt++;

        }
        return LSize;
    }

    //(^< ............ ............ ............ Obtener Indice Lista Vr
    int GetInside_VrPos_OrderedIndex(int Hx,GenList<Permission*>* NuclearList){

        int cnt = 0;
        int LSize = NuclearList->ListSize;
        GeNode<Permission*>* TmpProg = NuclearList->First;
        while (cnt < LSize) {
            //if(TmpProg->Data->HrPos > Hx){
            if(TmpProg->Data->HrPos >= Hx){
                return cnt;
            }
            TmpProg = TmpProg->Next;
            cnt++;
        }
        return LSize;
    }

    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    //(^< ............ ............ ............ ............ ............ Support
    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

    //(^< ............ ............ ............ GetHorizontal_Used
    GenList<MyInt*>* GetHorizontal_Used(){

        GenList<MyInt*>* LsHor_Index = new GenList<MyInt*>();

        int cnt = 0;
        GeNode<Archive*>* TmpAlu = LstHorizontal->First;
        while(cnt < LstHorizontal->ListSize){

            if(TmpAlu->Data->NuclearList->ListSize > 0){
                MyInt* TmpMyInt = new MyInt(cnt);
                LsHor_Index->EndInsert(TmpMyInt);
            }
            TmpAlu = TmpAlu->Next;
            cnt++;
        }

        return LsHor_Index;
    }

    //(^< ............ ............ ............ GetHorizontal_Used
    GenList<MyInt*>* GetVertical_Used(){

        GenList<MyInt*>* LsVer_Index = new GenList<MyInt*>();

        int cnt = 0;
        GeNode<User*>* TmpAlu = LstVertical->First;
        while(cnt < LstVertical->ListSize){

            if(TmpAlu->Data->NuclearList->ListSize > 0){
                MyInt* TmpMyInt = new MyInt(cnt);
                LsVer_Index->EndInsert(TmpMyInt);
            }
            TmpAlu = TmpAlu->Next;
            cnt++;
        }

        return LsVer_Index;
    }

    //(^< ............ ............ ............ Get_I_J_Node
    GeNode<Permission*>* Get_J_I_Node(int j,int i){

        //GeNode<Archive*>* ArNode = GetHorizontalNode_ByHr(j);
        GeNode<Archive*>* ArNode = Get_j_Header_Horizontal(j);
        GeNode<Permission*>* TMP = ArNode->Data->NuclearList->First;

        int cnt = 0;
        while(cnt < ArNode->Data->NuclearList->ListSize){

            if(TMP->Data->VrPos == i){
                return TMP;
            }
            TMP = TMP->Next;
            cnt++;
        }
        return NULL;
    }

    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    //(^< ............ ............ ............ ............ ............ Insert
    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

    //(^< ............ ............ ............ Actualiza Nodo Exisntente
    void Update_to_NewNode(int j,int i,Permission* Prog){

        Prog->HrPos = j;
        Prog->VrPos = i;

        GeNode<Archive*>* TmpAlu = Get_j_Header_Horizontal(j);
        GeNode<User*>*  TmpCrs = Get_i_Header_Vertical(i);

        if(TmpAlu != NULL && TmpCrs != NULL){
            GeNode<Permission*>* DNode = Get_J_I_Node(j,i);

            if(DNode != NULL){
                Delete_to_Update_NewNode(j,i,DNode);
            }

            int Hr_Ordered_Correlative = GetInside_HrPos_OrderedIndex(i,TmpAlu->Data->NuclearList);
            int Vr_Ordered_Correlative = GetInside_VrPos_OrderedIndex(j,TmpCrs->Data->NuclearList);

            TmpAlu->Data->NuclearList->InsertAt(Hr_Ordered_Correlative,Prog);
            TmpCrs->Data->NuclearList->InsertAt(Vr_Ordered_Correlative,Prog);

            GeNode<Permission*>* AluProg = TmpAlu->Data->NuclearList->GetNode(Hr_Ordered_Correlative);
            GeNode<Permission*>* CrsProg = TmpCrs->Data->NuclearList->GetNode(Vr_Ordered_Correlative);

            //(^< ............ ............ ............ Linking
            NodeLinking(AluProg,CrsProg);
            UpdateLimits(i,j);
            NodeCounter++;
        }
        else{
            throw std::invalid_argument( "Update_to_NewNode: Una Cabecera NO Existe." );
        }
    }

    //(^< ............ ............ ............ Insertar Cabecera en Orden Horizontal
    bool InsertSortered_Horizontal(int Hx,Archive* Alu){
        int Ps = GetHorizontal_OrderedIndex(Hx);
        LstHorizontal->InsertAt(Ps,Alu);
    }

    //(^< ............ ............ ............ Insertar Cabecera en Orden Vertical
    bool InsertSortered_Vertical(int Vx,User* Crs){
        int Ps = GetVertical_OrderedIndex(Vx);
        LstVertical->InsertAt(Ps,Crs);
    }

    //(^< ............ ............ ............ Insertar Nodo Cabecera Horizontal en Poscion j
    bool Hr_Insert(int j,Archive* Alu){
        //if(j >= 0 && !Horizontal_j_Exist(j)){
        if(j >= 0 && Get_j_Header_Horizontal(j) == NULL){
            Alu->HrPos=j;
            this->InsertSortered_Horizontal(j,Alu);
            return true;
        }
        return false;
    }

    //(^< ............ ............ ............ Insertar Nodo Cabecera Vertical en Poscion i
    bool Vr_Insert(int i,User* Crs){
        //if(i >= 0 && !Vertical_i_Exist(i)){
        if(i >= 0 && Get_i_Header_Vertical(i) == NULL){
            Crs->VrPos = i;
            this->InsertSortered_Vertical(i,Crs);
            return true;
        }
        return false;
    }

    //(^< ............ ............ ............ Insertar Nodo en la Posicion i , j
    bool InsertNode(int j,int i,Permission* Prog){

        Prog->HrPos = j;
        Prog->VrPos = i;

        GeNode<Archive*>* TmpAlu = Get_j_Header_Horizontal(j);
        GeNode<User*>*  TmpCrs = Get_i_Header_Vertical(i);

        if(TmpAlu != NULL && TmpCrs != NULL){

            GeNode<Permission*>* DNode = Get_J_I_Node(j,i);
            if(DNode == NULL){

                int Hr_Ordered_Correlative = GetInside_HrPos_OrderedIndex(i,TmpAlu->Data->NuclearList);
                int Vr_Ordered_Correlative = GetInside_VrPos_OrderedIndex(j,TmpCrs->Data->NuclearList);

                TmpAlu->Data->NuclearList->InsertAt(Hr_Ordered_Correlative,Prog);
                TmpCrs->Data->NuclearList->InsertAt(Vr_Ordered_Correlative,Prog);

                GeNode<Permission*>* AluProg = TmpAlu->Data->NuclearList->GetNode(Hr_Ordered_Correlative);
                GeNode<Permission*>* CrsProg = TmpCrs->Data->NuclearList->GetNode(Vr_Ordered_Correlative);

                //(^< ............ ............ ............ Linking
                NodeLinking(AluProg,CrsProg);
                UpdateLimits(i,j);
                NodeCounter++;
                return true;
            }

            else{
                //throw std::invalid_argument( "InsertNode: El Nodo: "+std::to_string(j)+","+std::to_string(i)+" Ya Existe");
            }
        }
    }

    //(^< ............ ............ ............ Update Limits
    void UpdateLimits(int i, int j){
        if(i > VrLimint){
            VrLimint = i;
        }
        if(j > HrLimit){
            HrLimit = j;
        }
    }

    //(^< ............ ............ ............ DeleteNode
    void DeleteNode(int j,int i){

        GeNode<Permission*>* DNode = Get_J_I_Node(j,i);

        if(DNode != NULL){
            Permission* NuclearNode = DNode->Data;
            NodeUnlinking(NuclearNode);

            GeNode<Archive*>* AT = Get_j_Header_Horizontal(j);
            GeNode<User*>* UT = Get_i_Header_Vertical(i);

            int i_Delete = GetInside_HrPos_OrderedIndex(i,AT->Data->NuclearList);
            int j_Delete = GetInside_VrPos_OrderedIndex(j,UT->Data->NuclearList);

            AT->Data->NuclearList->DeleteNode(i_Delete);
            UT->Data->NuclearList->DeleteNode(j_Delete);

            NodeCounter--;
        }
        else{
            throw std::invalid_argument( "DeleteNode: El Nodo: "+std::to_string(j)+","+std::to_string(i)+" No Existe" );
        }
    }

    //(^< ............ ............ ............ Delete_to_Update_NewNode
    void Delete_to_Update_NewNode(int j,int i,GeNode<Permission*>* DNode){

        Permission* NuclearNode = DNode->Data;
            NodeUnlinking(NuclearNode);

            GeNode<Archive*>* AT = Get_j_Header_Horizontal(j);
            GeNode<User*>* UT = Get_i_Header_Vertical(i);

            int i_Delete = GetInside_HrPos_OrderedIndex(i,AT->Data->NuclearList);
            int j_Delete = GetInside_VrPos_OrderedIndex(j,UT->Data->NuclearList);

            AT->Data->NuclearList->DeleteNode(i_Delete);
            UT->Data->NuclearList->DeleteNode(j_Delete);

            NodeCounter--;
    }

    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    //(^< ............ ............ ............ ............ ............ Node Connections
    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

    //(^< ............ ............ ............ NodeLinking
    void NodeLinking(GeNode<Permission*>* AluProg,GeNode<Permission*>* CrsProg){
        Permission* NuclearNode = AluProg->Data;

        //(^< ............ Top
        if(AluProg->Previous != NULL){
            NuclearNode->Top = AluProg->Previous->Data;
            AluProg->Previous->Data->Bottom = NuclearNode;
        }

        //(^< ............ Bottom
        if(AluProg->Next != NULL){
            NuclearNode->Bottom = AluProg->Next->Data;
            AluProg->Next->Data->Top = NuclearNode;
        }

        //(^< ............ Previous
        if(CrsProg->Previous != NULL){
            NuclearNode->Previous =CrsProg->Previous->Data;
            CrsProg->Previous->Data->Next = NuclearNode;
        }

        //(^< ............ Next
        if(CrsProg->Next != NULL){
            NuclearNode->Next = CrsProg->Next->Data;
            CrsProg->Next->Data->Previous = NuclearNode;
        }
    }

    //(^< ............ ............ ............ NodeUnlinking
    void NodeUnlinking(Permission* NuclearNode){

        //(^< ............ Top
        if(NuclearNode->Top != NULL){
            NuclearNode->Top->Bottom = NuclearNode->Bottom;
        }

        //(^< ............ Bottom
        if(NuclearNode->Bottom != NULL){
            NuclearNode->Bottom->Top = NuclearNode->Top;
        }

        //(^< ............ Previous
        if(NuclearNode->Previous != NULL){
            NuclearNode->Previous->Next = NuclearNode->Next;
        }

        //(^< ............ Next
        if(NuclearNode->Next != NULL){
            NuclearNode->Next->Previous = NuclearNode->Previous;
        }

        NuclearNode->Top = NULL;
        NuclearNode->Bottom = NULL;
        NuclearNode->Previous = NULL;
        NuclearNode->Next = NULL;
    }

    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
    //(^< ............ ............ ............ ............ ............ Graph
    //(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

    //(^< ............ ............ ............ DrawMatrix
    void DrawMatrix(){
        if(LstHorizontal->ListSize > 0 && LstVertical->ListSize > 0){

            GenList<MyInt*>* LsHor_Index = GetHorizontal_Used();
            GenList<MyInt*>* LsVer_Index = GetVertical_Used();

            int Hr_User_Used = LsHor_Index->ListSize;
            int Vr_Arch_Used = LsVer_Index->ListSize;

            QString NodeBf = "";
            QString LinkBf = "";
            QString RankBf = "";

            QFile Fl("Sparce_Matrix.dot");
            if(Fl.open(QFile::WriteOnly | QFile::Text)){
                QTextStream DotBf(&Fl);
                DotBf<<"digraph Sparce_Matrix {\n";

                DotBf<<"\n";
                DotBf<<"    node [shape=box]\n";

                DotBf<<"\n";
                //DotBf<<"    Mt [label = \"Matrix\" width = 1.5 style = filled, fillcolor = firebrick1];\n";
                DotBf<<"    Mt [label = \"Matrix\", width = 1.5, style = filled, fillcolor = firebrick1, group = 1];\n";

                //DotBf<<"\n";
                //DotBf<<"\    e0[ shape = point, width = 0 ];\n";
                //DotBf<<"\    e1[ shape = point, width = 0 ];\n";

                DotBf<<"\n";
                DotBf<<"    //(^< ............ ............ ............ ............ ............ U S U A R I O S\n";

                Create_Nodes_U(NodeBf,LinkBf);
                DotBf<<NodeBf;

                DotBf<<"\n";
                DotBf<<"    //(^< ............ Links\n";
                DotBf<<LinkBf;

                DotBf<<"\n";
                DotBf<<"    //(^< ............ ............ ............ ............ ............ A R C H I V O S\n";

                Create_Nodes_A(NodeBf,LinkBf,RankBf);
                DotBf<<NodeBf;

                DotBf<<"\n";
                DotBf<<"    //(^< ............ Links\n";
                DotBf<<LinkBf;

                DotBf<<"\n";
                DotBf<<"    Mt -> U0;\n";
                DotBf<<"    Mt -> A0 { constraint = true };\n";

                DotBf<<"\n";
                DotBf<<"    { rank = same; Mt; "+RankBf+"}\n";

                DotBf<<"\n";
                DotBf<<"    //(^< ............ ............ ............ ............ ............ P E R M I S O S\n";

                //DotBf<<"    //(^< ............ ............ L E V E L   \n";
                Create_NL(NodeBf,LsHor_Index,LsVer_Index);
                DotBf<<NodeBf;

                DotBf<<"\n";
                DotBf<<"    //(^< ............ ............ ............ ............ ............ L I N K I N G\n";

                SetNode_Linking(NodeBf,LsHor_Index,LsVer_Index);
                DotBf<<NodeBf;

                //DotBf<<"\n";
                //DotBf<<"\    { rank = same; U2; e0 }\n";
                //DotBf<<"\    { rank = same; U3; e1 }\n";
                //DotBf<<"\n";

                //DotBf<<"    A4 -> e0 -> e1[ dir = none ];\n";
                //DotBf<<"    e1 -> N2_L4;\n";

                DotBf<<"\n";
                DotBf<<"}";

                Fl.close();
                system("xdg-open ./Sparce_Matrix.dot");
            }
        }
    }

    //(^< ............ ............ ............ SetNode_Linking
    void SetNode_Linking(QString &Bf,GenList<MyInt*>* HrUsed,GenList<MyInt*>* VrUsed){
        Bf = "";
        QString Rk = "";
        int cnt = 0;
        while(cnt < VrUsed->ListSize){
            int ins = 0;
            int Level = VrUsed->GetNode(cnt)->Data->Cont;
            Bf.append("    //(^< ............ ............ L E V E L   "+QString::number(Level)+"\n");
            Bf.append("\n");
            GeNode<User*>* Occupied_VrHeader = LstVertical->GetNode(VrUsed->GetNode(cnt)->Data->Cont);
            GeNode<Permission*>* TmpPer = Occupied_VrHeader->Data->NuclearList->First;
            while(ins < Occupied_VrHeader->Data->NuclearList->ListSize){

                Rk.append(TmpPer->Data->PermissionData->NODE_ID+";");

                //Previous
                if(TmpPer->Previous == NULL){
                    Bf.append("    "+Occupied_VrHeader->Data->UserData->NODE_ID+" -> "+TmpPer->Data->PermissionData->NODE_ID+";\n");
                }
                else{
                    Bf.append("    "+TmpPer->Previous->Data->PermissionData->NODE_ID+" -> "+TmpPer->Data->PermissionData->NODE_ID+";\n");
                    Bf.append("    "+TmpPer->Data->PermissionData->NODE_ID+" -> "+TmpPer->Previous->Data->PermissionData->NODE_ID+";\n");
                }

                //Top
                int ID = TmpPer->Data->PermissionData->ARCH_INDEX;
                GeNode<Archive*>* Occupied_HrHeader = LstHorizontal->GetNode(ID);
                if(TmpPer->Data->Top == NULL){
                    //int ID = GetHorizontal_USEDINDEX(TmpPer->Data->PermissionData->ARCH_INDEX,HrUsed);

                    Bf.append("    "+Occupied_HrHeader->Data->ArchiveData->NODE_ID+" -> "+TmpPer->Data->PermissionData->NODE_ID+";\n");

                    //GetHorizontal_USEDINDEX
                }
                else{

                    //Bf.append("    "+TmpPer->Data->PermissionData->NODE_ID+" ->"+TmpPer->Data->Top->PermissionData->NODE_ID+";\n");
                    Bf.append("    "+TmpPer->Data->PermissionData->NODE_ID+" ->"+TmpPer->Data->Top->PermissionData->NODE_ID+";\n");
                    Bf.append("    "+TmpPer->Data->Top->PermissionData->NODE_ID+" ->"+TmpPer->Data->PermissionData->NODE_ID+";\n");

                }

                //Next

                //Bottom

                TmpPer = TmpPer->Next;
                ins++;
            }

            //{ rank = same; A1; N1_L1; N2_L1; N3_L1 }
            Bf.append("\n");

            Bf.append("    { rank = same; "+Occupied_VrHeader->Data->UserData->NODE_ID+"; "+Rk+" }\n");

            /*
            if(cnt != (VrUsed->ListSize - 1)){
                Bf.append("    { rank = same; "+Occupied_VrHeader->Data->UserData->NODE_ID+"; "+Rk+" }\n");
            }
            else{
                Bf.append("    { rank = same; "+Rk+" }\n");
            }
            //Bf.append("    { rank = same; "+Occupied_VrHeader->Data->UserData->NODE_ID+"; "+Rk+" }\n");
            */
            Rk = "";
            cnt++;
        }
    }

    //(^< ............ ............ ............ Create_NL
    void Create_NL(QString &Bf,GenList<MyInt*>* HrUsed,GenList<MyInt*>* VrUsed){
        Bf = "";
        int cnt = 0;
        while(cnt < VrUsed->ListSize){

            int ins = 0;
            int Level = VrUsed->GetNode(cnt)->Data->Cont;
            Bf.append("    //(^< ............ ............ L E V E L   "+QString::number(Level)+"\n");
            GeNode<User*>* Occupied_VrHeader = LstVertical->GetNode(VrUsed->GetNode(cnt)->Data->Cont);
            GeNode<Permission*>* TmpPer = Occupied_VrHeader->Data->NuclearList->First;
            while(ins < Occupied_VrHeader->Data->NuclearList->ListSize){
                //Bf.append("    N"+QString::number(ins)+"_L"+QString::number(Level)+" [label = \""+TmpPer->Data->PermissionData->TAG+"\", width = 1.5,  group = "+QString::number(VrUsed->GetNode(cnt)->Data->Cont+2)+"];\n");
                //Bf.append("    N"+QString::number(ins)+"_L"+QString::number(Level)+" [label = \""+TmpPer->Data->PermissionData->TAG+"\", width = 1.5,  group = "+QString::number(HrUsed->GetNode(ins)->Data->Cont+2)+"];\n");

                int Lk = 0;
                GeNode<Archive*>* TA = LstHorizontal->First;
                while(Lk < LstHorizontal->ListSize){
                    if(TmpPer->Data->HrPos == TA->Data->HrPos){
                        break;
                    }
                    TA = TA->Next;
                    Lk++;
                }

                Bf.append("    N"+QString::number(ins)+"_L"+QString::number(Level)+" [label = \""+TmpPer->Data->PermissionData->TAG+"\", width = 1.5,  group = "+QString::number(Lk+2)+"];\n");
                TmpPer->Data->PermissionData->NODE_ID = "N"+QString::number(ins)+"_L"+QString::number(Level);
                TmpPer = TmpPer->Next;
                ins++;
            }
            Bf.append("\n");
            cnt++;
        }

        cnt = 0;
        while(cnt < HrUsed->ListSize){

            int ins = 0;
            int Column = HrUsed->GetNode(cnt)->Data->Cont;
            GeNode<Archive*>* Occupied_HrHeader = LstHorizontal->GetNode(HrUsed->GetNode(cnt)->Data->Cont);
            GeNode<Permission*>* TmpPer = Occupied_HrHeader->Data->NuclearList->First;

            while(ins < Occupied_HrHeader->Data->NuclearList->ListSize){
                TmpPer->Data->PermissionData->ARCH_INDEX = Column;
                TmpPer = TmpPer->Next;
                ins++;
            }
            cnt++;
        }

    }

    //(^< ............ ............ ............ Create_Nodes_A
    void Create_Nodes_A(QString &Bf,QString &Lf,QString &Rk){
        Bf = "";
        Lf = "";
        Rk = "";
        int cnt = 0;
        while(cnt < LstHorizontal->ListSize){
            //Bf.append("    A"+QString::number(cnt)+" [label = \""+LstHorizontal->GetNode(cnt)->Data->ArchiveData->TAG+"\" width = 1.5 style = filled, fillcolor = lightskyblue];\n");
            Bf.append("    A"+QString::number(cnt)+" [label = \""+LstHorizontal->GetNode(cnt)->Data->ArchiveData->TAG+"\", width = 1.5, style = filled, fillcolor = lightskyblue, group = "+QString::number(cnt+2)+"];\n");
            LstHorizontal->GetNode(cnt)->Data->ArchiveData->NODE_ID = "A"+QString::number(cnt);
            if(cnt < (LstHorizontal->ListSize - 1)){
                Lf.append(QString("    A"+QString::number(cnt))+" -> A"+QString::number(cnt+1)+";\n");
                Lf.append(QString("    A"+QString::number(cnt+1))+" -> A"+QString::number(cnt)+";\n");
            }
            Rk.append("A"+QString::number(cnt)+"; ");
            cnt++;
        }
    }

    //(^< ............ ............ ............ Create_Nodes_U
    void Create_Nodes_U(QString &Bf,QString &Lf){
        Bf = "";
        Lf = "";
        int cnt = 0;
        while(cnt < LstVertical->ListSize){
            //Bf.append("    U"+QString::number(cnt)+" [label = \""+LstVertical->GetNode(cnt)->Data->UserData->TAG+"\" width = 1.5 style = filled, fillcolor = bisque1];\n");
            Bf.append("    U"+QString::number(cnt)+" [label = \""+LstVertical->GetNode(cnt)->Data->UserData->TAG+"\", width = 1.5 style = filled, fillcolor = bisque1, group = 1];\n");
            LstVertical->GetNode(cnt)->Data->UserData->NODE_ID = "U"+QString::number(cnt);
            if(cnt < (LstVertical->ListSize - 1)){
                Lf.append(QString("    U"+QString::number(cnt))+" -> U"+QString::number(cnt+1)+" { constraint = true };\n");
                Lf.append(QString("    U"+QString::number(cnt+1))+" -> U"+QString::number(cnt)+" { constraint = true };\n");
            }
            cnt++;
        }
    }

};

#endif // SPARSEMATRIX_H

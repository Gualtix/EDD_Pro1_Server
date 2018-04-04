#ifndef JSONREADER_H
#define JSONREADER_H

//C++
#include <stdexcept>
#include "time.h"

//Qt
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

//ADT
#include "genlist.h"
#include "archive.h"
#include "user.h"

class JSonReader{

public:


    //(^< ............ ............ ............ Carga de Archivos
    void static Load_Horizontal_Archives(QByteArray JSon_File,GenList<Archive*>* LstHorizontal,GenList<PermissionInfo*>* LsPermInfo){

        //GenList<PermissionInfo*>* LsPermInfo = new GenList<PermissionInfo*>();

        QJsonDocument Doc = QJsonDocument::fromJson(JSon_File);
        if(!Doc.isArray()){
            QMessageBox::warning(nullptr, "JSON Archivos", "Error en el archivo, el elemento raíz debe ser un arreglo");
            return;
        }

        QJsonArray Array = Doc.array();
        int MaxSize = Array.size();

        for(int A = 0; A < MaxSize; A++) {
            QJsonValueRef Ref = Array[A];
            if(! Ref.isObject())
                continue;

            QJsonObject Obj = Ref.toObject();

            //Nombre
            QJsonValue nameValue = Obj["nombre"];
            if(nameValue.isUndefined() || nameValue.isNull())
                continue;

            //Tipo
            QJsonValue typelValue = Obj["tipo"];
            if(typelValue.isUndefined() || typelValue.isNull())
                continue;

            //Creador
            QJsonValue creatorValue = Obj["creador"];
            if(creatorValue.isUndefined() || creatorValue.isNull())
                continue;

            //Fecha de Creacion
            QJsonValue  creation_dateValue = Obj["fecha_creacion"];
            if(creation_dateValue.isUndefined() || creation_dateValue.isNull())
                continue;

            //Modificador
            QJsonValue modifier_nicknameValue = Obj["modificador"];
            if(modifier_nicknameValue.isUndefined() || modifier_nicknameValue.isNull())
                continue;

            //Fecha de Modificacion
            QJsonValue modification_dateValue = Obj["fecha_modificacion"];
            if(modification_dateValue.isUndefined() || modification_dateValue.isNull())
                continue;

            //Ruta de Contenido
            QJsonValue json_urlValue = Obj["ruta_contenido"];
            if(json_urlValue.isUndefined() || json_urlValue.isNull())
                continue;

            //(^< ............ P E R M I S O S
            QJsonArray Permisos = Obj["permisos"].toArray();
            int maxPermisos = Permisos.size();



            for(int j = 0; j < maxPermisos; j++){

                QJsonValueRef rePerm = Permisos[j];
                if(! rePerm.isObject())
                continue;

                QJsonObject objPerm = rePerm.toObject();

                //Usuario
                QJsonValue usuarioValue = objPerm["usuario"];
                if(usuarioValue.isUndefined() || usuarioValue.isNull())
                continue;

                //Permiso
                QJsonValue permisoValue = objPerm["permiso"];
                if(permisoValue.isUndefined() || permisoValue.isNull())
                continue;

                PermissionInfo* TmpInfo = new PermissionInfo();
                TmpInfo->ARCH = nameValue.toString();
                TmpInfo->USR = usuarioValue.toString();
                TmpInfo->Type = permisoValue.toString();
                TmpInfo->TAG = permisoValue.toString();

                LsPermInfo->EndInsert(TmpInfo);
            }

            ArchiveInfo* ArInfo = new ArchiveInfo();

            ArInfo->Name = nameValue.toString();
            ArInfo->Type = typelValue.toString();
            ArInfo->Creator = creatorValue.toString();
            ArInfo->Creation_Date = creation_dateValue.toString();
            ArInfo->Modifier_Nickname = modifier_nicknameValue.toString();
            ArInfo->Modification_Date = modification_dateValue.toString();
            ArInfo->JSon_URL = json_urlValue.toString();

            //TAG
            ArInfo->TAG = nameValue.toString();

            Archive* ARCH = new Archive(ArInfo);

            LstHorizontal->EndInsert(ARCH);
            LstHorizontal->Last->TAG = nameValue.toString();
            LstHorizontal->Last->NICK = nameValue.toString();
            LstHorizontal->Last->Data->HrPos = A;
        }
    }

    //(^< ............ ............ ............ Carga de Usuarios
    void static Load_Vertical_Users(QByteArray JSon_File,GenList<User*>* LstVertical){

        QJsonDocument Doc = QJsonDocument::fromJson(JSon_File);
        if(!Doc.isArray()){
            QMessageBox::warning(nullptr, "JSON Productos", "Error en el archivo, el elemento raíz debe ser un arreglo");
            return;
        }

        QJsonArray Array = Doc.array();
        int MaxSize = Array.size();

        for(int i = 0; i < MaxSize; i++) {
            QJsonValueRef Ref = Array[i];
            if(! Ref.isObject())
                continue;

            QJsonObject Obj = Ref.toObject();

            //Codigo
            QJsonValue nameValue = Obj["nombre"];
            if(nameValue.isUndefined() || nameValue.isNull())
                continue;

            //Precio
            QJsonValue emailValue = Obj["correo"];
            if(emailValue.isUndefined() || emailValue.isNull())
                continue;

            //Nombre
            QJsonValue  nicknameValue = Obj["nickname"];
            if(nicknameValue.isUndefined() || nicknameValue.isNull())
                continue;

            //Descripcion
            QJsonValue keyValue = Obj["clave"];
            if(keyValue.isUndefined() || keyValue.isNull())
                continue;

            UserInfo* UsInfo = new UserInfo();

            UsInfo->Name = nameValue.toString();
            UsInfo->EMail = emailValue.toString();
            UsInfo->Nickname =nicknameValue.toString();
            UsInfo->Password = keyValue.toString();

            //TAG
            UsInfo->TAG = nameValue.toString();

            User* USR = new User(UsInfo);

            LstVertical->EndInsert(USR);
            LstVertical->Last->TAG = nameValue.toString();
            LstVertical->Last->NICK = nicknameValue.toString();
            LstVertical->Last->Data->VrPos = i;
        }
    }

    //(^< ............ ............ ............ Actualizacion de Usuarios
    //QString static User_Update(){

    //}

    //(^< ............ ............ ............ Actualizacion de Archivos
    //QString static User_Update(){

    //}

};

#endif // JSONREADER_H

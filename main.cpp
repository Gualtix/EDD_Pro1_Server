//C++
#include <iostream>

//Qt
#include <QApplication>
#include "QString"
#include "QDebug"

//ADT
#include "mainwindow.h"
#include "sparsematrix.h"
#include "user.h"
#include "archive.h"

using namespace std;

int main(int argc, char *argv[])

{

    //GenList<QString>* GL = new GenList<QString>();
        //SparseMatrix* Mtx = new SparseMatrix();

        //Mtx->Load_JSon_Vertical_Headers("/home/wrm/SERVER_PRO_1/SERVER_PRO_1/usuarios.json");
        //Mtx->Load_JSon_Horizontal_Headers("/home/wrm/SERVER_PRO_1/SERVER_PRO_1/archivos.json");

        //GeNode<User*>* Us = Mtx->LstVertical->GetNode_By_String("Gabriel Galicia");
        //GeNode<Archive*>* Ar2 = Mtx->LstHorizontal->GetNode_By_String("MarioBros");
        //GeNode<Archive*>* Ar3 = Mtx->LstHorizontal->GetNode_By_String("Tarea1");


        //Mtx->DrawMatrix();


        /*  "/home/wrm/SERVER_PRO_1/SERVER_PRO_1/usuarios.json" */
        /*  "/home/wrm/SERVER_PRO_1/SERVER_PRO_1/archivos.json" */

        /*

        Mtx->Hr_Insert(9,new Archive(new ArchiveInfo(250,13.5,"Julian")));
        Mtx->Hr_Insert(7,new Archive(new ArchiveInfo(250,13.5,"Marco")));
        Mtx->Hr_Insert(4,new Archive(new ArchiveInfo(250,13.5,"Alejandro")));
        Mtx->Hr_Insert(1,new Archive(new ArchiveInfo(250,13.5,"Josefina")));
        Mtx->Hr_Insert(10,new Archive(new ArchiveInfo(250,13.5,"Pamela")));

        Mtx->Vr_Insert(13,new User(new UserInfo(23,10.5,"Lenguajes")));
        Mtx->Vr_Insert(5,new User(new UserInfo(32,11.5,"Estructuras")));
        Mtx->Vr_Insert(8,new User(new UserInfo(32,11.5,"Investigacion")));
        Mtx->Vr_Insert(7,new User(new UserInfo(32,11.5,"Compiladores")));
        Mtx->Vr_Insert(6,new User(new UserInfo(32,11.5,"Redes")));

        int k = 10;
        int f = 20;

        Mtx->InsertNode(7,5,new Permission(new PermissionInfo(41,60.10,"Marc-Estr")));
        Mtx->InsertNode(9,5,new Permission(new PermissionInfo(41,60.10,"Juli-Estr")));


        Mtx->InsertNode(7,13,new Permission(new PermissionInfo(41,60.10,"Marc-Leng")));
        Mtx->InsertNode(9,13,new Permission(new PermissionInfo(41,60.10,"Juli-Leng")));

        //Mtx->InsertNode(10,8,new Permission(new PermissionInfo(41,60.10,"Pame-Inve")));

        Mtx->InsertNode(10,13,new Permission(new PermissionInfo(41,60.10,"Pame-Leng")));

        Mtx->InsertNode(9,7,new Permission(new PermissionInfo(41,60.10,"Juli-Comp")));

        Mtx->InsertNode(7,7,new Permission(new PermissionInfo(41,60.10,"Marc-Comp")));

        Mtx->InsertNode(1,5,new Permission(new PermissionInfo(41,60.10,"Jose-Estr")));

        Mtx->Update_to_NewNode(1,5,new Permission(new PermissionInfo(41,60.10,"Nomanches man xD ")));

        Mtx->Update_to_NewNode(1,7,new Permission(new PermissionInfo(41,60.10,"No mE Digas xD")));

        Mtx->Update_to_NewNode(1,7,new Permission(new PermissionInfo(41,60.10,"Qiopmfas xx")));

        Mtx->Update_to_NewNode(10,8,new Permission(new PermissionInfo(41,60.10,"Mi Vida Pamela")));

        //Mtx->InsertNode(10,7,new Permission(new PermissionInfo(41,60.10,"Pame-Compi")));

        //Mtx->DeleteNode(1,5);
        Mtx->DeleteNode(7,7);
        Mtx->DeleteNode(7,13);
        //Mtx->DeleteNode(9,5);
        Mtx->DeleteNode(9,7);
        Mtx->DeleteNode(10,13);
        Mtx->DeleteNode(7,5);
        //Mtx->DeleteNode(9,13);

        Mtx->DrawMatrix();

        */

        //int Yz;
        //Mtx->H_Insert(new Alumno(0,35.6,"Alejandro"));
        //Mtx->V_Insert(new Curso(0,10.5,"Aplicada 2"));

        //int Ps = 0;

       // QString msg = "NewUser#Walter#7487#Waltix@hotmail.com#Morales#";




    /*
    //(^< ............ User Load
    QString Input_JSon_URL = "US_DIR/usuarios.json";
    QFile MyFile(Input_JSon_URL);
    MyFile.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream out(&MyFile);
    QString JSon_Plain_String = out.readAll();

    MyFile.close();

    //(^< ............ Edit
    int Last_Char_Pos = JSon_Plain_String.size() - 1;
    JSon_Plain_String.remove(Last_Char_Pos-1,2);

    JSon_Plain_String.append(",\n");
    JSon_Plain_String.append("\t{\n");

    JSon_Plain_String.append("\t\t       \"nombre\":\"Walter Morales\"        ,\n");
    JSon_Plain_String.append("\t\t       \"correo\":\"waltix@gmail.com\"        ,\n");
    JSon_Plain_String.append("\t\t       \"nickname\":\"waltix\"        ,\n");
    JSon_Plain_String.append("\t\t       \"clave\":\"felicidad\"        \n");

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
    */


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

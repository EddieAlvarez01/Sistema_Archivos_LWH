#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <typeinfo>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <stack>
#include <queue>
#include "mbr.h"
#include "ebr.h"
#include "parser.h"
#include "scanner.h"
#include "command.h"
#include "mkdisk.h"
#include "fdisk.h"
#include "mount.h"
#include "rmdisk.h"
#include "unmount.h"
#include "rep.h"
#include "exec.h"
#include "mkfs.h"
#include "listmount.h"
#include "nodelist.h"
#include "plotter.h"

using namespace std;

extern int yyparse();
extern list<Command*> listCommand;
extern int linea; // Linea del token
extern int columna; // Columna de los tokens
extern int yylineno;
list<string> printExec;
ListMount list_ram;
Plotter plot;
char generateLetter = 'a';

int Total_Disk_Size(string unit, int size){
    if(unit == "k"){
        return size *1024;
    }
   return size *1024*1024;
}

int Random_Id(){
    srand(time(NULL));
    int num = 0 + rand() % (1000001);
    return num;
}

vector<string> Separate_Mk(string path){
    vector<string> ll;
    size_t pos1 = 0;
    size_t pos2 = 0;
    string pp = "";
    while(pos2 != path.npos){
        pos2 = path.find("/", pos1);
        if(pos2 != path.npos){
            if(pos2 > pos1){
                ll.push_back(path.substr(pos1, pos2-pos1));
            }
            pos1 = pos2+1;
        }
    }
    return ll;
}

void Create_Directory(string path){
    vector<string> ll = Separate_Mk(path);
    vector<string>::iterator it;
    string pp = "";
    for(it = ll.begin(); it != ll.end(); ++it){
        pp += "/" + (*it);
        mkdir(pp.c_str(), 0777);
    }
    cout << "Directorio " + pp + " creado exitosamente\n";
}

bool existDir(string dir){
    FILE *file;
    file = fopen(dir.c_str(), "rb");
    if(file != nullptr){
        fclose(file);
        return true;
    }else{
        return false;
    }
}

string Path_Raid(string path){
    size_t pos1 = 0;
    size_t pos2 = 0;
    string pp = "";
    while(pos2 != path.npos){
        pos2 = path.find("/", pos1);
        if(pos2 != path.npos){
            if(pos2 > pos1){
                pp += "/" + path.substr(pos1, pos2-pos1);
            }
            pos1 = pos2+1;
        }
    }
    string name = (path.substr(pos1, path.size() - pos1));
    size_t found = name.find(".");
    string raid = name.substr(0, found) + "ra_1.";
    raid += name.substr(found+1, name.size());
    pp += "/" + raid;
    return pp;
}

void Create_Disk_Wihout_fit(Mkdisk *mk){
    Mbr newDisk;
    newDisk.mbr_size = mk->size;
    time_t t = time(nullptr);
    tm *now = localtime(&t);
    string chain;
    chain = to_string(now->tm_mday) + "-" + to_string((now->tm_mon+1)) + "-" + to_string((now->tm_year + 1900)) + " " + to_string(now->tm_hour) + ":" + to_string(now->tm_min);
    strcpy(newDisk.dateTime, chain.c_str());
    newDisk.mbr_disk_aignature = Random_Id();
    string adId = "vd" + string(1, generateLetter);
    generateLetter++;
    strcpy(newDisk.id, adId.c_str());
    Create_Directory(mk->path);
    if(!existDir(mk->path)){
        FILE *file = fopen(mk->path.c_str(), "w");
        if(file != nullptr){
            int fin = (mk->size/1024);
            char buffer[1024] = {0};
            int j = 0;
            while(j != fin){
                fwrite(&buffer, 1024, 1, file);
                j++;
            }
            fclose(file);
            file = fopen(mk->path.c_str(), "rb+");
            fseek(file, 0, SEEK_SET);
            if(file != nullptr){
                fwrite(&newDisk, sizeof (Mbr), 1, file);
                cout << "\nDisco Creado Exitosamente\n" << endl;
            }else{
                cout << "Error al tratar de acceder al archivo " + mk->path << endl;
            }
            fclose(file);
        }else{
            cout << "Error al tratar de crear el archivo " + mk->path  + "\n"<< endl;
        }
    }else{
        cout << "\nError al crear el disco" << endl;
    }
}

bool Disk_Partition_Montage(Mbr mbr){
    for(int x=0; x<4; x++){
        if(mbr.particions[x].part_start != -1 && strcmp(mbr.particions[x].id, "") != 0){
            if(list_ram.isMount(mbr.particions[x].id)){
                return true;
            }
        }
    }
    return false;
}

string NameDisk(string path){
    size_t pos1 = 0;
    size_t pos2 = 0;
    string pp = "";
    while(pos2 != path.npos){
        pos2 = path.find("/", pos1);
        if(pos2 != path.npos){
            if(pos2 > pos1){
                pp += "/" + path.substr(pos1, pos2-pos1);
            }
            pos1 = pos2+1;
        }
    }
    return path.substr(pos1, path.size()-pos1);
}

void Delete_Confirmation_Msg(string name){
    cout << "\nDesea eliminar el disco: " + name + " (s/n)\n";
}

void Delete_Disk(Rmdisk *rm){
    if(existDir(rm->path)){
        bool isValid = false;
        FILE *file = fopen(rm->path.c_str(), "rb+");
        if(file != nullptr){
            Mbr mbr;
            fseek(file, 0, SEEK_SET);
            fread(&mbr, sizeof (Mbr), 1, file);
            if(!Disk_Partition_Montage(mbr)){
                fclose(file);
                do{
                Delete_Confirmation_Msg(NameDisk(rm->path));
                string option;
                cin >> option;
                cin.ignore();
                if(strcmp(option.c_str(), "s") == 0 || strcmp(option.c_str(), "S") == 0){
                    isValid = true;
                    if(remove(rm->path.c_str()) == 0){
                        cout << "Disco borrado exitosamente\n";
                    }else{
                        cout << "Error al remover el disco\n";
                    }
                }else if(strcmp(option.c_str(), "n") == 0 || strcmp(option.c_str(), "N") == 0){
                    isValid = true;
                }else{
                    cout << "Error opcion invalida\n";
                    isValid = false;
                }
                }while(!isValid);
            }else{
                cout << "Error: No se puede eliminar un dico con particiones montadas\n";
            }
        }else{
            cout << "Error: no se puede eliminar porque no se puedo abrir el archivo\n";
        }
    }else{
        cout << "\nEl archivo " + NameDisk(rm->path) + " no existe " << endl;
    }
}

void Msg_Disk(Mbr mbr, FILE *file, string nameD){
    cout << "\nDisco: " + nameD + "\n";
    cout << "Tamaño total: " + to_string(mbr.mbr_size) + " bytes\n";
    cout << "Fecha de Creacion: " + string(mbr.dateTime) + "\n";
    int pP = 0;
    int pE = 0;
    int pL = 0;
    for(int x=0; x<4; x++){
        if(mbr.particions[x].part_type == 80){
            pP++;
        }else if(mbr.particions[x].part_type == 69){
            pE++;
            Ebr ebr;
            fseek(file, mbr.particions[x].part_start, SEEK_SET);
            fread(&ebr, sizeof (Ebr), 1, file);
        }
    }
    cout << "Particiones primarias: " + to_string(pP) + "\n";
    cout << "Particiones extendidas: " + to_string(pE) + "\n";
    cout << "Particiones logicas: " + to_string(pL) + "\n";
}

bool Name_Equal_Partition(string name, Mbr mbr, FILE *ff){
    for(int x=0; x<4; x++){
        if(mbr.particions[x].part_type == 80){
            if(strcmp(name.c_str(), mbr.particions[x].part_name) == 0){
                return true;
            }
        }else if(mbr.particions[x].part_type == 76 || mbr.particions[x].part_type == 69){
            if(strcmp(mbr.particions[x].part_name, name.c_str()) == 0){
                return true;
            }else{
                Ebr ebbr;
                fseek(ff, mbr.particions[x].part_start, SEEK_SET);
                fread(&ebbr, sizeof (Ebr), 1, ff);
                if(strcmp(ebbr.part_name, name.c_str()) == 0){
                    return true;
                }
            }
        }
    }
    return false;
}

void Delete_Confirmation_Partition(string name){
    cout << "\nDesea eliminar la particion: " + name + " (s/n)\n";
}

int Position_Partition(Mbr mbr, string name){
    for(int x=0; x<4; x++){
        if(strcmp(mbr.particions[x].part_name, name.c_str()) == 0){
            return x;
        }
    }
    return 0;
}

void Delete_Partition(Fdisk *fd){
    if(existDir(fd->path)){
        FILE *file = fopen(fd->path.c_str(), "rb+");
        if(file != nullptr){
            Mbr mbr;
            fseek(file, 0, SEEK_SET);
            fread(&mbr, sizeof (Mbr), 1, file);
            Msg_Disk(mbr, file, NameDisk(fd->path));
            if(Name_Equal_Partition(fd->name, mbr, file)){
                bool isValid = false;
                do{
                    Delete_Confirmation_Partition(fd->name);
                    string option;
                    cin >> option;
                    cin.ignore();
                    if(strcmp(option.c_str(), "S") == 0 || strcmp(option.c_str(), "s") == 0){
                        isValid = true;
                        int index = Position_Partition(mbr, fd->name);
                        mbr.particions[index].part_status = 0;
                        mbr.particions[index].part_type = 0;
                        strcpy(mbr.particions[index].part_fit, "");
                        mbr.particions[index].part_start = -1;
                        mbr.particions[index].part_size = 0;
                        strcpy(mbr.particions[index].part_name, "");
                        fseek(file, 0, SEEK_SET);
                        fwrite(&mbr, sizeof (Mbr), 1, file);
                        cout << "Particion " + fd->name + " borrada correctamente\n";
                    }else if(strcmp(option.c_str(), "N") == 0 || strcmp(option.c_str(), "n") == 0){
                        isValid = true;
                    }else{
                        isValid = false;
                        cout << "\nOpcion Invalida\n";
                    }
                }while(!isValid);
            }else{
                cout << "No existe una particion con el nombre '" + fd->name + "'\n";
            }
            fclose(file);
        }else{
            cout << "Error al abrir el archivo\n";
        }
    }else{
        cout << "\nEl archivo " + NameDisk(fd->path) + " no existe " << endl;
    }
}

int Total_Disk_FD(string unit, int size){
    if(unit == "b"){
        return size;
    }else if(unit == "m"){
        return size *1024*1024;
    }
    return size *1024;
}

int Disk_Space(Mbr mbr){
    int ss = mbr.mbr_size;
    for(int x=0; x<4; x++){
        if(mbr.particions[x].part_start != -1){
            ss -= mbr.particions[x].part_size;
        }
    }
    return ss;
}

void Update_Start_B(int x, Mbr *mbr){
    int start = mbr->particions[x].part_start;
    int end = start + mbr->particions[x].part_size;
    for(int y = x+1; y<4; y++){
        if(mbr->particions[y].part_start != -1){
            if(end <= mbr->particions[y].part_start){
                break;
            }else{
                start = end;
                end = start + mbr->particions[y].part_size;
                mbr->particions[y].part_start = start;
            }
        }
    }
}

void addUnits(Fdisk *fd){
    if(existDir(fd->path)){
        FILE *file = fopen(fd->path.c_str(), "rb+");
        if(file != nullptr){
            Mbr mbr;
            fseek(file, 0, SEEK_SET);
            fread(&mbr, sizeof (Mbr), 1, file);
            Msg_Disk(mbr, file, NameDisk(fd->path));
            bool error = false;
            for(int x=0; x<4; x++){
                if(mbr.particions[x].part_type == 69){
                    if(strcmp(mbr.particions[x].part_name, fd->name.c_str()) == 0){
                        error = false;
                        int ss = Disk_Space(mbr);
                        if(fd->add < 0){
                            if((mbr.particions[x].part_size + fd->add) > 0){
                                mbr.particions[x].part_size += fd->add;
                                fseek(file, 0, SEEK_SET);
                                fwrite(&mbr, sizeof (Mbr), 1, file);
                                cout << "Añadido " + to_string(fd->add) + " bytes correctamente a la particion " + fd->name + "\n";
                            }else{
                                cout << "Error: al quitarle espacio a una particion no puede quedar negativa o igual a 0\n";
                            }
                        }else{
                            if((ss - fd->add) >= 0){
                                if(x<3){
                                    mbr.particions[x].part_size += fd->add;
                                    Update_Start_B(x, &mbr);
                                    fseek(file, 0, SEEK_SET);
                                    fwrite(&mbr, sizeof (Mbr), 1, file);
                                    cout << "Añadido " + to_string(fd->add) + " bytes correctamente a la particion " + fd->name + "\n";
                                    fseek(file, 0, SEEK_SET);
                                    fread(&mbr, sizeof(Mbr), 1, file);
                                }else{
                                    mbr.particions[x].part_size += fd->add;
                                    fseek(file, 0, SEEK_SET);
                                    fwrite(&mbr, sizeof (Mbr), 1, file);
                                    cout << "Añadido " + to_string(fd->add) + " bytes correctamente a la particion " + fd->name + "\n";
                                    fseek(file, 0, SEEK_SET);
                                    fread(&mbr, sizeof(Mbr), 1, file);
                                }
                            }else{
                                cout << "Error: no hay sufciente espacio en el disco para añadir\n";
                            }
                        }
                        break;
                    }else{
                        //Logicas
                    }
                }else if(strcmp(mbr.particions[x].part_name, fd->name.c_str()) == 0){
                    error = false;
                    int ss = Disk_Space(mbr);
                    if(fd->add < 0){
                        if((mbr.particions[x].part_size + fd->add) > 0){
                            mbr.particions[x].part_size += fd->add;
                            fseek(file, 0, SEEK_SET);
                            fwrite(&mbr, sizeof (Mbr), 1, file);
                            cout << "Añadido " + to_string(fd->add) + " bytes correctamente a la particion " + fd->name + "\n";
                        }else{
                            cout << "Error: al quitarle espacio a una particion no puede quedar negativa o igual a 0\n";
                        }
                    }else{
                        if((ss - fd->add) >= 0){
                            if(x<3){
                                mbr.particions[x].part_size += fd->add;
                                Update_Start_B(x, &mbr);
                                fseek(file, 0, SEEK_SET);
                                fwrite(&mbr, sizeof (Mbr), 1, file);
                                fflush(file);
                                cout << "Añadido " + to_string(fd->add) + " bytes correctamente a la particion " + fd->name + "\n";
                            }else{
                                mbr.particions[x].part_size += fd->add;
                                cout << "Añadido " + to_string(fd->add) + " bytes correctamente a la particion " + fd->name + "\n";
                            }
                        }else{
                            cout << "Error: no hay sufciente espacio en el disco para añadir\n";
                        }
                    }
                    break;
                }else{
                    error = true;
                }
            }
            if(error){
                cout << "Error: no existe la particion: " + fd->name + "\n";
            }
            fclose(file);
        }else{
            cout << "Error al abrir el archivo\n";
        }
    }else{
        cout << "\nEl archivo " + NameDisk(fd->path) + " no existe " << endl;
    }
}

bool Partition_Space(Mbr mbr){
    for(int x=0; x<4; x++){
        if(strcmp(mbr.particions[x].part_name, "") == 0){
            return true;
        }
    }
    return false;
}

bool Partiton_Disk_Space(Mbr mbr, int sizea){
    int pp = mbr.mbr_size;
    for(int x=0; x<4; x++){
        if(mbr.particions[x].part_start != -1){
            pp -= mbr.particions[x].part_size;
        }
    }
    if((pp - sizea) >= 0){
        return true;
    }
    return false;
}

bool Exist_Extended(Mbr mbr){
    for(int x=0; x<4; x++){
        if(mbr.particions[x].part_type == 69){
            return true;
        }
    }
    return false;
}

void Create_Partition_Extended(Fdisk *fd){
    if(existDir(fd->path)){
        FILE *file = fopen(fd->path.c_str(), "rb+");
        if(file != nullptr){
            Mbr mbr;
            fseek(file, 0, SEEK_SET);
            fread(&mbr, sizeof (Mbr), 1, file);
            Msg_Disk(mbr, file, NameDisk(fd->path));
            if(Partition_Space(mbr) && Partiton_Disk_Space(mbr, fd->size)){
                if(!Exist_Extended(mbr)){
                    if(!Name_Equal_Partition(fd->name, mbr, file)){
                        if(fd->size <= mbr.mbr_size){
                            int start = sizeof (Mbr);
                            int end = start + fd->size;
                            int parT = 0;
                            for(int x=0; x<4; x++){
                                if(mbr.particions[x].part_start != -1){
                                        start = mbr.particions[x].part_start + mbr.particions[x].part_size;
                                        end = start + fd->size;
                                        parT = x+1;
                                }else{
                                    break;
                                }
                            }
                            if(end <= mbr.mbr_size){
                                mbr.particions[parT].part_start = start;
                                mbr.particions[parT].part_status = 1;
                                strcpy(mbr.particions[parT].part_name, fd->name.c_str());
                                mbr.particions[parT].part_size = fd->size;
                                strcpy(mbr.particions[parT].part_fit, fd->fit.c_str());
                                mbr.particions[parT].part_type == 69;
                                Ebr ebr;
                                fseek(file, mbr.particions[parT].part_start, SEEK_SET);
                                fwrite(&ebr, sizeof (Ebr), 1, file);
                                fseek(file, 0, SEEK_SET);
                                fwrite(&mbr, sizeof (Mbr), 1, file);
                                cout << "Particion extendida '" + fd->name + "' creada exitosamente\n";
                                fseek(file, 0, SEEK_SET);
                                fread(&mbr, sizeof(Mbr), 1, file);
                                Msg_Disk(mbr, file, NameDisk(fd->path));
                            }else{
                                cout << "Error: ya no hay espacio suficiente para la particion '" + fd->name + "'\n";
                            }
                        }else{
                            cout << "Error: el tamaño de la particion es mas grande que el disco\n";
                        }
                    }else{
                        cout << "Error: el nombre '" + fd->name + "' ya esta siendo utilizado en otra particion\n";
                    }
                }else{
                    cout << "Error: ya existe una particion extendida en este disco\n";
                }
            }else{
                 cout << "Error: no hay espacio en el disco para mas particiones\n";
            }
            fclose(file);
        }else{
            cout << "Error: al abrir el archivo\n" << endl;
        }
    }else{
        cout << "\nEl archivo " + NameDisk(fd->path) + " no existe " << endl;
    }
}

void Create_Partition_Primary(Fdisk *fd){
    if(existDir(fd->path)){
        FILE *file = fopen(fd->path.c_str(), "rb+");
        if(file != nullptr){
            Mbr mbr;
            fseek(file, 0, SEEK_SET);
            fread(&mbr, sizeof (Mbr), 1, file);
            Msg_Disk(mbr, file, NameDisk(fd->path));
            if(Partition_Space(mbr) && Partiton_Disk_Space(mbr, fd->size)){
                if(!Name_Equal_Partition(fd->name, mbr, file)){
                    if(fd->size <= mbr.mbr_size){
                        int start = sizeof (Mbr);
                        int end = start + fd->size;
                        int parT = 0;
                        for(int x=0; x<4; x++){
                            if(mbr.particions[x].part_start != -1){
                                    start = mbr.particions[x].part_start + mbr.particions[x].part_size;
                                    end = start + fd->size;
                                    parT = x+1;
                            }else{
                                break;
                            }
                        }
                        if(end <= mbr.mbr_size){
                            mbr.particions[parT].part_start = start;
                            mbr.particions[parT].part_status = 1;
                            strcpy(mbr.particions[parT].part_name, fd->name.c_str());
                            mbr.particions[parT].part_size = fd->size;
                            strcpy(mbr.particions[parT].part_fit, fd->fit.c_str());
                            mbr.particions[parT].part_type == 80;
                            cout << "Particion primaria '" + fd->name + "' creada exitosamente\n";
                            fseek(file, 0, SEEK_SET);
                            fwrite(&mbr, sizeof (Mbr), 1, file);
                            fseek(file, 0, SEEK_SET);
                            fread(&mbr, sizeof(Mbr), 1, file);
                            Msg_Disk(mbr, file, NameDisk(fd->path));
                        }else{
                            cout << "Error: ya no hay espacio suficiente para la particion '" + fd->name + "'\n";
                        }
                    }else{
                        cout << "Error: el tamaño de la particion es mas grande que el disco\n";
                    }
                }else{
                    cout << "Error: el nombre '" + fd->name + "' ya esta siendo utilizado en otra particion\n";
                }
            }else{
                cout << "Error: no hay espacio en el disco para mas particiones\n";
            }
            fclose(file);
        }else{
            cout << "Error: al abrir el archivo\n" << endl;
        }
    }else{
        cout << "\nEl archivo " + NameDisk(fd->path) + " no existe " << endl;
    }
}

void Mount_Partition(Mount *mn){
    if(existDir(mn->path)){
        FILE *file = fopen(mn->path.c_str(), "rb+");
        if(file != nullptr){
            Mbr mbr;
            fseek(file, 0, SEEK_SET);
            fread(&mbr, sizeof (Mbr), 1, file);
            Msg_Disk(mbr, file, NameDisk(mn->path));
            if(Name_Equal_Partition(mn->name, mbr, file)){
                int pp = Position_Partition(mbr, mn->name);
                if(!list_ram.isMount(mbr.particions[pp].id)){
                    string idd = mbr.id + to_string(pp+1);
                    strcpy(mbr.particions[pp].id, idd.c_str());
                    NodeList *node = new NodeList(mbr.particions[pp]);
                    node->disk = mn->path;
                    time_t t = time(nullptr);
                    tm *now = localtime(&t);
                    node->date = to_string(now->tm_mday) + "-" + to_string(now->tm_mon + 1) + "-" + to_string(now->tm_year + 1900);
                     list_ram.insert(node);
                    fseek(file, 0, SEEK_SET);
                    fwrite(&mbr, sizeof (Mbr), 1, file);
                    cout << "Particion " + mn->name + " montada correctamente\n";
                    cout << "\nParticiones montadas:\n";
                }else{
                    cout << "Error: la particion " + mn->name + " ya esta montada\n";
                }
            }else{
                cout << "Error: la particion '" + mn->name + "' no exite\n";
            }
            fclose(file);
        }else{
            cout << "Error al abrir el archivo\n";
        }
    }else{
        cout << "\nEl archivo " + NameDisk(mn->path) + " no existe " << endl;
    }
}

string Path_To_Report(string path){
    std::string pp;
    size_t found = path.find(".");
    pp = path.substr(0, found);
    return pp;
}

bool hasExtension(string name){
    string ext = name.substr(name.length() - 4, 4);
    if(ext == ".dsk"){
        return true;
    }
    return false;
}


int main()
{
    do{
        if(printExec.empty()){
            cout << "\nInserte comando\n";
            string command;
            getline(cin, command);
            YY_BUFFER_STATE buffer = yy_scan_string(command.c_str());
        }else{
            string msg = printExec.front() + "\n";
            printExec.pop_front();
            cout << msg;
            YY_BUFFER_STATE buffer = yy_scan_string(msg.c_str());
        }
    linea = 1;
    columna = 0;
    yylineno = 0;
    listCommand.clear();
    if(yyparse() == 0){
        list<Command*> :: iterator it;
        for(it = listCommand.begin(); it != listCommand.end(); ++it){
            if(Mkdisk *mk = dynamic_cast<Mkdisk*>((*it))){
                if(mk->size > 0){
                    if(mk->size % 8 == 0){
                        if(mk->path != ""){
                            if(mk->name != ""){
                                if(hasExtension(mk->name)){
                                    mk->path += mk->name;
                                    mk->size = Total_Disk_Size(mk->unit, mk->size);
                                    Create_Disk_Wihout_fit(mk);
                                }else{
                                    cout << "Error: el nombre no contiene la extension '.dsk'\n";
                                }
                            }else{
                                cout << "Error: el 'name' es obligatorio\n";
                            }
                        }else{
                            cout << "Error: el 'path' es obligatorio" << endl;
                        }
                    }else{
                        cout << "Error: el tamaño debe ser multiplo de 8\n";
                    }
                }else{
                    cout << "Error: el tamaño es obligatorio" << endl;
                }
            }else if(Rmdisk *rm = dynamic_cast<Rmdisk*>((*it))){
                if(rm->path != ""){
                    Delete_Disk(rm);
                }else{
                    cout << "Error: el 'path' es obligatorio\n";
                }
            }else if(Fdisk *fd = dynamic_cast<Fdisk*>((*it))){
                if(fd->path != ""){
                    if(fd->name != ""){
                        if(fd->toDelete != ""){
                            Delete_Partition(fd);
                            fd->path = Path_Raid(fd->path);
                            Delete_Partition(fd);
                        }else if(fd->isAdd){
                            fd->add = Total_Disk_FD(fd->unit, fd->add);
                            addUnits(fd);
                            fd->path = Path_Raid(fd->path);
                            addUnits(fd);
                        }else{
                            if(fd->size != -1){
                                fd->size = Total_Disk_FD(fd->unit, fd->size);
                                if(fd->fit == ""){
                                    fd->fit = "wf";
                                }
                                if(fd->type != "" && fd->type != "p"){
                                    if(fd->type == "e"){
                                        Create_Partition_Extended(fd);
                                        fd->path = Path_Raid(fd->path);
                                        Create_Partition_Extended(fd);
                                    }else if(fd->type == "l"){

                                    }
                                }else{
                                    Create_Partition_Primary(fd);
                                    fd->path = Path_Raid(fd->path);
                                    Create_Partition_Primary(fd);
                                }
                            }else{
                                cout << "Error: el parametro 'size' es obligatorio\n";                            }
                        }
                    }else{
                        cout << "Error: el parametro 'name' es obligatorio\n";
                    }
                }else{
                    cout << "Error: el 'path' es obligatorio" << endl;
                }
            }else if(Mount *mn = dynamic_cast<Mount*>((*it))){
                if(mn->name != ""){
                    if(mn->path != ""){
                        Mount_Partition(mn);
                        mn->path = Path_Raid(mn->path);
                        Mount_Partition(mn);
                        list_ram.List_Mount();
                    }else{
                        cout << "Error: el 'path' es obligatorio\n";
                    }
                }else{
                    cout << "Error: el 'name' es obligatorio\n";
                }
            }else if(Unmount *unm = dynamic_cast<Unmount*>((*it))){
                if(unm->id != ""){

                }else{
                    cout << "Error: el 'id' es obligatorio\n";
                }
            }else if(Exec *exc = dynamic_cast<Exec*>((*it))){
                if(exc->path != ""){
                    string line;
                    ifstream file;
                    file.open(exc->path, ios::in);
                    if(!file.fail()){
                        while(!file.eof()){
                            getline(file, line);
                            printExec.push_back(line);
                        }
                        file.close();
                    }else{
                        cout << "No se puedo leer el script\n";
                    }
                }else{
                    cout << "Error: el 'path es obligatorio\n";
                }
            }else if(Rep *rp = dynamic_cast<Rep*>((*it))){
                if(rp->name != ""){
                    if(rp->path != ""){
                        if(rp->id != ""){
                            if(strcmp(rp->name.c_str(), "mbr") == 0){
                                string oPath = list_ram.To_Report(rp->id);
                                if(oPath != ""){
                                    Create_Directory(rp->path);
                                    FILE *file = fopen(oPath.c_str(), "rb+");
                                    if(file != nullptr){
                                        Mbr mbr;
                                        fseek(file, 0, SEEK_SET);
                                        fread(&mbr, sizeof (Mbr), 1, file);
                                        fclose(file);
                                        plot.Plot_Mbr(mbr, NameDisk(oPath), Path_To_Report(rp->path));
                                    }else{
                                        cout << "Error al abrir el archivo\n";
                                    }
                                }else{
                                    cout << "No existe el id '" + rp->id + "' montada\n";
                                }
                            }else{
                                 string oPath = list_ram.To_Report(rp->id);
                                 if(oPath != ""){
                                    Create_Directory(rp->path);
                                    FILE *file = fopen(oPath.c_str(), "rb+");
                                    if(file != nullptr){
                                        Mbr mbr;
                                        fseek(file, 0, SEEK_SET);
                                        fread(&mbr, sizeof (Mbr), 1, file);
                                        fclose(file);
                                        plot.Plot_Disk(mbr, Path_To_Report(rp->path), Disk_Space(mbr));
                                    }else{
                                        cout << "Error al abrir el archivo\n";
                                    }
                                 }else{
                                     cout << "No existe el id '" + rp->id + "' montada\n";
                                 }
                            }
                        }else{
                            cout << "Error: el 'id' es obligatorio\n";
                        }
                    }else{
                        cout << "Error: el 'path' es obligatorio\n";
                    }
                }else{
                    cout << "Error: el 'name' es obligatorio\n";
                }
            }/*else if(Mkfs *mkfs = dynamic_cast<Mkfs*>((*it))){
                if(mkfs->id != ""){
                    Format_Partition(mkfs);
                }else{
                    cout << "Error: el 'id' es obligatorio\n";
                }
            }else if(Login *login = dynamic_cast<Login*>((*it))){
                if(login->usr != ""){
                    if(login->pwd != ""){
                        if(login->id != ""){
                            if(!ussr.isSession){
                                Session(login);
                            }else{
                                cout << "Ya hay una sesion iniciada, ejecute logout\n";
                            }
                        }else{
                            cout << "Error: el 'id' es obligatorio\n";
                        }
                    }else{
                        cout << "La contrasena es obligatoria\n";
                    }
                }else{
                    cout << "El nombre de usuario es obligatorio\n";
                }
            }else if(Logout *logout = dynamic_cast<Logout*>((*it))){
                if(ussr.isSession){
                    ussr.id = "";
                    ussr.user = "";
                    ussr.group = "";
                    ussr.idGroup = "";
                    ussr.isSession = false;
                    ussr.partition = nullptr;
                    cout << "Session cerrada correctamente\n";
                }else{
                    cout << "Error: no hay ninguna sesion iniciada, porfavor inici sesion para poder usar este comando\n";
                }
            }else if(Mkgrp *mkgr = dynamic_cast<Mkgrp*>((*it))){
                if(ussr.isSession){
                    if(strcmp(ussr.group.c_str(), "root") == 0){
                        if(mkgr->name != ""){
                            AddGroup(mkgr);
                        }else{
                            cout << "El name es obligatorio\n";
                        }
                    }else{
                        cout << "Error: permisos insuficientes\n";
                    }
                }else{
                    cout << "Error: no hay sesion iniciada para usar este comando\n";
                }
            }else if(Rmgrp *rmgrp = dynamic_cast<Rmgrp*>((*it))){
                if(ussr.isSession){
                    if(strcmp(ussr.group.c_str(), "root") == 0){
                        if(rmgrp->name != ""){
                            RemoveGroup(rmgrp);
                        }else{
                            cout << "El name es obligatorio\n";
                        }
                    }else{
                        cout << "Error: permisos insuficientes\n";
                    }
                }else{
                    cout << "Error: no hay ninguna sesion iniciada, porfavor inici sesion para poder usar este comando\n";
                }
            }else if(Mkusr *mkusr = dynamic_cast<Mkusr*>((*it))){
                if(ussr.isSession){
                    if(strcmp(ussr.group.c_str(), "root") == 0){
                        if(mkusr->usr != ""){
                            if(mkusr->pwd != ""){
                                if(mkusr->grp != ""){
                                    CreateNewUser(mkusr);
                                }else{
                                    cout << "El grp es obligatorio\n";
                                }
                            }else{
                                cout << "EL password es obligatorio\n";
                            }
                        }else{
                            cout << "El usuario es obligatorio\n";
                        }
                    }else{
                        cout << "Error: permisos insuficientes\n";
                    }
                }else{
                    cout << "Error: no hay ninguna sesion iniciada, porfavor inici sesion para poder usar este comando\n";
                }
            }else if(Rmusr *rmusr = dynamic_cast<Rmusr*>((*it))){
                if(ussr.isSession){
                    if(strcmp(ussr.group.c_str(), "root") == 0){
                        if(rmusr->usr != ""){
                            RemoveUser(rmusr);
                        }else{
                           cout << "El usuario es obligatorio\n";
                        }
                    }else{
                        cout << "Error: permisos insuficientes\n";
                    }
                }else{
                   cout << "Error: no hay ninguna sesion iniciada, porfavor inici sesion para poder usar este comando\n";
                }
            }else if(Mkfile *mkfile = dynamic_cast<Mkfile*>((*it))){
                if(ussr.isSession){
                    if(mkfile->path != ""){
                        if(mkfile->cont != ""){
                            if(existDir(mkfile->cont)){
                                stack<string> evaluatePath = PathbyInodes(mkfile->path);
                                NewFile(mkfile, evaluatePath);
                            }else{
                                cout << "Error: el archivo de cont no existe\n";
                            }
                        }else{
                            stack<string> evaluatePath = PathbyInodes(mkfile->path);
                            NewFile(mkfile, evaluatePath);
                        }
                    }else{
                        cout << "Error: el path es obligatorio\n";
                    }
                }else{
                    cout << "Error: no hay ninguna sesion iniciada, porfavor inici sesion para poder usar este comando\n";
                }
            }else if(Mkdir *mkdir = dynamic_cast<Mkdir*>((*it))){
                if(ussr.isSession){
                    if(mkdir->path != ""){
                        NewDir(mkdir);
                    }else{
                        cout << "Error: el path es obligatorio\n";
                    }
                }else{
                    cout << "Error: no hay ninguna sesion iniciada, porfavor inici sesion para poder usar este comando\n";
                }
            }*/
        }
    }else{
        cout << "Incorrecto" << endl;
    }
    }while(true);
    return 0;
}

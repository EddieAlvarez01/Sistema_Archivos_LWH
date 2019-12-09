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
#include <math.h>
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
#include "superboot.h"
#include "virtualdirectorytree.h"
#include "directorydetail.h"
#include "inode.h"
#include "datablock.h"
#include "log.h"
#include "returnedofbitmap.h"

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
int countLogic = 1; //Contador para los id de las monturas de las particiones logicas.

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

int Tell_Logic(Ebr ebr, FILE *file, int pL){
    if(ebr.part_next != 0){
        Ebr ebr2;
        fseek(file, ebr.part_next, SEEK_SET);
        fread(&ebr2, sizeof(Ebr), 1, file);
        pL++;
        pL = Tell_Logic(ebr2, file, pL);
    }
    return pL;
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
            if(ebr.isLogic == 49){
                pL++;
                if(ebr.part_next != 0){
                    pL = Tell_Logic(ebr, file, pL);
                }
            }
        }
    }
    cout << "Particiones primarias: " + to_string(pP) + "\n";
    cout << "Particiones extendidas: " + to_string(pE) + "\n";
    cout << "Particiones logicas: " + to_string(pL) + "\n";
}

bool Equal_Logic(string name, Ebr bbr, FILE *file, bool rs){
    if(bbr.part_next != 0){
        Ebr ebr2;
        fseek(file, bbr.part_next, SEEK_SET);
        fread(&ebr2, sizeof(Ebr), 1, file);
        if(strcmp(ebr2.part_name, name.c_str()) == 0){
            rs = true;
            return rs;
        }else{
            rs = Equal_Logic(name, ebr2, file, rs);
        }
    }
    return rs;
}

bool Name_Equal_Partition(string name, Mbr mbr, FILE *ff){
    for(int x=0; x<4; x++){
        if(mbr.particions[x].part_type == 80){
            if(strcmp(name.c_str(), mbr.particions[x].part_name) == 0){
                return true;
            }
        }else if(mbr.particions[x].part_type == 69){
            if(strcmp(mbr.particions[x].part_name, name.c_str()) == 0){
                return true;
            }else{
                Ebr ebbr;
                fseek(ff, mbr.particions[x].part_start, SEEK_SET);
                fread(&ebbr, sizeof (Ebr), 1, ff);
                if(ebbr.isLogic == 49){
                    if(strcmp(ebbr.part_name, name.c_str()) == 0){
                        return true;
                    }else{
                        bool rs = false;
                        if(Equal_Logic(name, ebbr, ff, rs)){
                            return true;
                        }
                    }
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
    return -1;
}

void Resize_Ex(Ebr ebr, Ebr ebr2, FILE *file){
    if(ebr2.part_next != 0){

    }
}

void Delete_R_Logic(Ebr ebr, FILE *file, string name){
    if(ebr.part_next != 0){
        Ebr ebr2;
        fseek(file, ebr.part_next, SEEK_SET);
        fread(&ebr2, sizeof(Ebr), 1, file);
        if(strcmp(ebr2.part_name, name.c_str()) == 0){
            if(ebr2.part_next != 0){
                Ebr ebr3;
                fseek(file, ebr2.part_next, SEEK_SET);
                fread(&ebr3, sizeof(Ebr), 1, file);
                ebr3.part_start = ebr2.part_start;
                //ebr3.
            }
        }
    }
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
                        if(index != -1){
                            mbr.particions[index].part_status = 0;
                            mbr.particions[index].part_type = 0;
                            strcpy(mbr.particions[index].part_fit, "");
                            mbr.particions[index].part_start = -1;
                            mbr.particions[index].part_size = 0;
                            strcpy(mbr.particions[index].part_name, "");
                            fseek(file, 0, SEEK_SET);
                            fwrite(&mbr, sizeof (Mbr), 1, file);
                        }else{
                            for(int x=0; x<4; x++){
                                if(mbr.particions[x].part_type == 69){
                                    Ebr ebr;
                                    fseek(file, mbr.particions[x].part_start, SEEK_SET);
                                    fread(&ebr, sizeof(Ebr), 1, file);
                                    if(strcmp(ebr.part_name, fd->name.c_str()) == 0){
                                        ebr.isLogic = 48;
                                        strcpy(ebr.part_fit, "");
                                        ebr.part_status = 48;
                                        ebr.part_size = -1;
                                        strcpy(ebr.part_name, "");
                                    }else{

                                    }
                                    break;
                                }
                            }
                        }
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

int EbrSpace(Ebr ebr, int diskS, FILE *file){
    diskS -= sizeof(Ebr);
    diskS -= ebr.part_size;
    if(ebr.part_next != 0){
        Ebr ebr2;
        fseek(file, ebr.part_next, SEEK_SET);
        fread(&ebr2, sizeof(Ebr), 1, file);
        return EbrSpace(ebr2, diskS, file);
    }
    return diskS;
}

bool Partition_Extended_Space(FILE *file, Mbr mbr, int size){
    int u = 0;
    for(int x=0; x<4; x++){
        if(mbr.particions[x].part_type == 69){
            u = x;
            break;
        }
    }
    int diskS = mbr.particions[u].part_size;
    Ebr ebr;
    fseek(file, mbr.particions[u].part_start, SEEK_SET);
    fread(&ebr, sizeof(Ebr), 1, file);
    diskS -= sizeof(Ebr);
    if(ebr.isLogic != 48){
        diskS -= ebr.part_size;
        if(ebr.part_next != 0){
            Ebr ebr2;
            fseek(file, ebr.part_next, SEEK_SET);
            fread(&ebr2, sizeof(Ebr), 1, file);
            diskS = EbrSpace(ebr2, diskS, file);
        }
        if((diskS - size) >= 0){
            return true;
        }else{
            return false;
        }
    }
    return true;
}

void Recalculate_Space_Logic(Ebr ebr, FILE *file, int add){
    if(ebr.part_next != 0){
        int start = ebr.part_start;
        int next = ebr.part_next;
        Ebr ebr2;
        fseek(file, next, SEEK_SET);
        fread(&ebr2, sizeof(Ebr), 1, file);
        ebr.part_size += add;
        ebr.part_next = start + ebr.part_size;
        ebr2.part_start = ebr.part_next + sizeof(Ebr);
        if(ebr2.part_next == 0){
            fseek(file, ebr.part_next, SEEK_SET);
            fwrite(&ebr2, sizeof(Ebr), 1, file);
        }else{
            Recalculate_Space_Logic(ebr2, file, add);
        }
        fseek(file, (start - sizeof(Ebr)), SEEK_SET);
        fwrite(&ebr, sizeof(Ebr), 1, file);
    }else{
        ebr.part_size += add;
        fseek(file, (ebr.part_start - sizeof(Ebr)), SEEK_SET);
        fwrite(&ebr, sizeof(Ebr), 1, file);
    }
}

Ebr Search_Ebr(Ebr ebr, FILE *file, string name){
    if(strcmp(ebr.part_name, name.c_str()) == 0){
        return ebr;
    }else{
        if(ebr.part_next != 0){
            Ebr ebr2;
            fseek(file, ebr.part_next, SEEK_SET);
            fread(&ebr2, sizeof(Ebr), 1, file);
            ebr = Search_Ebr(ebr2, file, name);
        }
    }
    return ebr;
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
                        //añadir tamaño a logicas
                        Ebr ebr;
                        fseek(file, mbr.particions[x].part_start, SEEK_SET);
                        fread(&ebr, sizeof(Ebr), 1, file);
                        if(fd->add < 0){
                            if(strcmp(ebr.part_name, fd->name.c_str()) == 0){
                                error = false;
                                if((ebr.part_size + fd->add) > 0){
                                    Recalculate_Space_Logic(ebr, file, fd->add);
                                    cout << "Añadido correctamente " + to_string(fd->add) + " bytes a la particion '" + fd->name + "' \n";
                                }else{
                                    cout << "Error: al quitarle espacio a una particion no puede quedar negativa o igual a 0\n";
                                }
                            }else{
                                if(ebr.isLogic != 48){
                                    Ebr ebr2;
                                    fseek(file, ebr.part_next, SEEK_SET);
                                    fread(&ebr2, sizeof(Ebr), 1, file);
                                    Ebr tmpE = Search_Ebr(ebr2, file, fd->name);
                                    error = false;
                                    if((tmpE.part_size + fd->add) > 0){
                                        Recalculate_Space_Logic(tmpE, file, fd->add);
                                        cout << "Añadido correctamente " + to_string(fd->add) + " bytes a la particion '" + fd->name + "' \n";
                                    }else{
                                        cout << "Error: al quitarle espacio a una particion no puede quedar negativa o igual a 0\n";
                                    }
                                }
                            }
                        }else{
                            if(Partition_Extended_Space(file, mbr, fd->add)){
                                if(strcmp(ebr.part_name, fd->name.c_str()) == 0){
                                    error = false;
                                    Recalculate_Space_Logic(ebr, file, fd->add);
                                }else{
                                    if(ebr.isLogic != 48){
                                        error = false;
                                        Ebr ebr2;
                                        fseek(file, ebr.part_next, SEEK_SET);
                                        fread(&ebr2, sizeof(Ebr), 1, file);
                                        Recalculate_Space_Logic(Search_Ebr(ebr2, file, fd->name), file, fd->add);
                                    }
                                }
                                cout << "Añadido correctamente " + to_string(fd->add) + " bytes a la particion '" + fd->name + "' \n";
                            }else{
                                cout << "Error: la cantidad a añadir sobrepasa el tamano de la particion externa\n";
                            }
                        }
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
                                mbr.particions[parT].part_type = 69;
                                Ebr ebr;
                                ebr.part_start = sizeof(Ebr) + mbr.particions[parT].part_start;
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
                            mbr.particions[parT].part_status = 49;
                            strcpy(mbr.particions[parT].part_name, fd->name.c_str());
                            mbr.particions[parT].part_size = fd->size;
                            strcpy(mbr.particions[parT].part_fit, fd->fit.c_str());
                            mbr.particions[parT].part_type = 80;
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

void Linked_Ebr(Ebr ebr, FILE *file, Mbr mbr, Fdisk *fd){
    if(ebr.part_next == 0){
        Ebr ebr2;
        ebr.part_next = ebr.part_start + ebr.part_size;
        ebr2.part_status = 49;
        if(fd->fit != ""){
            strcpy(ebr2.part_fit, fd->fit.c_str());
        }else{
            strcpy(ebr2.part_fit, "wf");
        }
        ebr2.part_start = ebr.part_next + sizeof(Ebr);
        ebr2.part_size = fd->size;
        ebr2.part_next = 0;
        strcpy(ebr2.part_name, fd->name.c_str());
        fseek(file, (ebr.part_start - sizeof(Ebr)), SEEK_SET);
        fwrite(&ebr, sizeof(Ebr), 1, file);
        fseek(file, ebr.part_next, SEEK_SET);
        fwrite(&ebr2, sizeof(Ebr), 1, file);
        cout << "Particion logica '" + fd->name + "' creada exitosamente\n";
        fseek(file, 0, SEEK_SET);
        fread(&mbr, sizeof(Mbr), 1, file);
        Msg_Disk(mbr, file, NameDisk(fd->path));
    }else{
        Ebr ebr2;
        fseek(file, ebr.part_next, SEEK_SET);
        fread(&ebr2, sizeof(Ebr), 1, file);
        Linked_Ebr(ebr2, file, mbr, fd);
    }
}

void Create_Partition_Logic(Fdisk *fd){
    if(existDir(fd->path)){
        FILE *file = fopen(fd->path.c_str(), "rb+");
        if(file != nullptr){
            Mbr mbr;
            fseek(file, 0, SEEK_SET);
            fread(&mbr, sizeof (Mbr), 1, file);
            if(Exist_Extended(mbr)){
                if(Partition_Extended_Space(file, mbr, fd->size)){
                    if(!Name_Equal_Partition(fd->name, mbr, file)){
                        Msg_Disk(mbr, file, NameDisk(fd->path));
                        int y;
                        for(int x=0; x<4; x++){
                            if(mbr.particions[x].part_type == 69){
                                y = x;
                                break;
                            }
                        }
                        Ebr ebr;
                        fseek(file, mbr.particions[y].part_start, SEEK_SET);
                        fread(&ebr, sizeof(Ebr), 1, file);
                            if(ebr.isLogic != 48){
                                if(ebr.part_next != 0){
                                    Linked_Ebr(ebr, file, mbr, fd);
                                }else{
                                    ebr.part_next = ebr.part_start + ebr.part_size;
                                    Ebr ebr2;
                                    ebr2.part_status = 49;
                                    if(fd->fit != ""){
                                        strcpy(ebr2.part_fit, fd->fit.c_str());
                                    }else{
                                        strcpy(ebr2.part_fit, "wf");
                                    }
                                    ebr2.part_start = ebr.part_next + sizeof(Ebr);
                                    ebr2.part_size = fd->size;
                                    ebr2.part_next = 0;
                                    strcpy(ebr2.part_name, fd->name.c_str());
                                    fseek(file, mbr.particions[y].part_start, SEEK_SET);
                                    fwrite(&ebr, sizeof(Ebr), 1, file);
                                    fseek(file, ebr.part_next, SEEK_SET);
                                    fwrite(&ebr2, sizeof(Ebr), 1, file);
                                    cout << "Particion logica '" + fd->name + "' creada exitosamente\n";
                                    fseek(file, 0, SEEK_SET);
                                    fread(&mbr, sizeof(Mbr), 1, file);
                                    Msg_Disk(mbr, file, NameDisk(fd->path));
                                }
                            }else{
                                ebr.part_status = 49;
                                if(fd->fit != ""){
                                    strcpy(ebr.part_fit, fd->fit.c_str());
                                }else{
                                    strcpy(ebr.part_fit, "wf");
                                }
                                ebr.part_size = fd->size;
                                ebr.isLogic = 49;
                                strcpy(ebr.part_name, fd->name.c_str());
                                fseek(file, mbr.particions[y].part_start, SEEK_SET);
                                fwrite(&ebr, sizeof(Ebr), 1, file);
                                cout << "Particion logica '" + fd->name + "' creada exitosamente\n";
                                fseek(file, 0, SEEK_SET);
                                fread(&mbr, sizeof(Mbr), 1, file);
                                Msg_Disk(mbr, file, NameDisk(fd->path));
                            }
                    }else{
                        cout << "Error: el nombre '" + fd->name + "' ya existe en una particion\n";
                    }
                 }else{
                    cout << "Error: no hay espacio en la particion extendida\n";
                }
            }else{
                cout << "Error: no se puede crear logicas sin una particion extendida\n";
            }
            fclose(file);
        }else{
            cout << "Error: al abrir el archivo\n";
        }
    }else{
        cout << "\nEl archivo " + NameDisk(fd->path) + " no existe \n";
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
                if(pp != -1){
                    if(!list_ram.isMountByName(mbr.particions[pp].part_name)){
                        string idd = mbr.id + to_string(pp+1);
                        strcpy(mbr.particions[pp].id, idd.c_str());
                        NodeList *node = new NodeList(mbr.particions[pp]);
                        node->disk = mn->path;
                        time_t t = time(nullptr);
                        tm *now = localtime(&t);
                        node->date = to_string(now->tm_mday) + "-" + to_string(now->tm_mon + 1) + "-" + to_string(now->tm_year + 1900);
                         list_ram.insert(node);
                        cout << "Particion " + mn->name + " montada correctamente\n";
                        cout << "\nParticiones montadas:\n";
                    }else{
                        cout << "Error: la particion " + mn->name + " ya esta montada\n";
                    }
                }else{
                    for(int x=0; x<4; x++){
                        if(mbr.particions[x].part_type == 69){                // Se encuentra la extendida
                            Ebr ebr;
                            fseek(file, mbr.particions[x].part_start, SEEK_SET);
                            fread(&ebr, sizeof(Ebr), 1, file);
                            Ebr ebr2 = Search_Ebr(ebr, file, mn->name);     // Se encuentra la partión logica
                            if(!list_ram.isMountByName(ebr2.part_name)){
                                string idd = mbr.id + to_string(4 + countLogic++);
                                //Llenar propiedades
                                strcpy(ebr2.id, idd.c_str());
                                NodeList *node = new NodeList(ebr2);
                                node->disk = mn->path;
                                time_t t = time(nullptr);
                                tm *now = localtime(&t);
                                node->date = to_string(now->tm_mday) + "-" + to_string(now->tm_mon + 1) + "-" + to_string(now->tm_year + 1900);
                                list_ram.insert(node);
                            }else{
                                 cout << "Error: la particion " + mn->name + " ya esta montada\n";
                            }
                            break;
                        }
                    }
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

int Calculate_Structures(int partitionSize){
    int dividend = partitionSize - (2*(int)sizeof (SuperBoot));
    int divider = 27 + (int)sizeof (VirtualDirectoryTree) + (int)sizeof (DirectoryDetail) + (5 * (int)sizeof (Inode) + (20 * (int)sizeof(DataBlock)) + (int)sizeof(Log));
    double n = dividend / divider;
    return (int)floor(n);
}

/*int ReturnedByteJournaling(FILE *file, int initByte, int endByte){
    Journaling jo;
    for(int i=initByte; i<=endByte; i += (int)sizeof (Journaling)){
        fseek(file, i, SEEK_SET);
        fread(&jo, sizeof (Journaling), 1, file);
        if(strcmp(jo.op, "mkdir") != 0){
            return i;
        }
    }
    return 0;
}*/

ReturnedOfBitmap ReturnByteBitmap(FILE *file, int initByte, int endByte){
    char bit;
    ReturnedOfBitmap returnBy;
    int count = 0;
    while(initByte <= endByte){
        fseek(file, initByte, SEEK_SET);
        fread(&bit, 1, 1, file);
        int byte = bit;
        if(byte == 0){
            returnBy.position = count;
            returnBy.byte = initByte;
            return returnBy;
        }
        initByte++;
        count++;
    }
    return returnBy;
}

/*Metodo de escritura en los bloques*/
string Write_DataBlock(char contentBlock[25], string text){
    int spaceFree = strlen(contentBlock);
    while(spaceFree < 25){
        char character = text[0];
        contentBlock[spaceFree] = character;
        text.erase(0, 1);
        spaceFree++;
        if(text == ""){
           break;
        }
    }
    return text;
}

/*Metodo de asignacion de bloques a un inodo*/
void Recursive_CreateFile(FILE *file, string text, SuperBoot sb, Inode in, int posInode){
    for(int i=0; i<4; i++){
        if(in.i_array_bloques[i] == -1){
            ReturnedOfBitmap byteBmBlock = ReturnByteBitmap(file, sb.sb_ap_bitmap_bloques, sb.sb_ap_bloques);
            if(byteBmBlock.position != -1){
                char a = 49;
                fseek(file, byteBmBlock.byte, SEEK_SET);
                fwrite(&a, 1, 1, file);
                DataBlock dB;
                text = Write_DataBlock(dB.db_data, text);
                in.i_array_bloques[i] = byteBmBlock.position;
                in.i_count_bloques_asignados += 1;
                fseek(file, sb.sb_ap_bloques + (byteBmBlock.position * (int)sizeof(DataBlock)), SEEK_SET);
                fwrite(&dB, sizeof(DataBlock), 1, file);
                if(text == ""){
                    break;
                }
                in.i_size_archivo += 25;
            }else{
                cout << "No hay espacio en los bloques\n";
            }
        }
    }
    if(text != ""){
        if(in.i_ap_indirecto == -1){
            ReturnedOfBitmap byteBmInode = ReturnByteBitmap(file, sb.sb_ap_bitmap_tabla_inodo, sb.sb_ap_tabla_inodo);
            if(byteBmInode.position != -1){
                char a = 49;
                fseek(file, byteBmInode.byte, SEEK_SET);
                fwrite(&a, 1, 1, file);
                in.i_ap_indirecto = byteBmInode.position;
                Inode newIn;
                newIn.i_count_inodo = byteBmInode.position + 1;
                newIn.i_size_archivo = 100;
                newIn.i_count_bloques_asignados = 0;
                newIn.i_id_proper = in.i_id_proper;
                newIn.i_perm = in.i_perm;
                Recursive_CreateFile(file, text, sb, newIn, byteBmInode.position);
            }else{
                cout << "No hay espacio en inodos\n";
            }
        }
    }
    fseek(file, sb.sb_ap_tabla_inodo + (posInode * (int)sizeof(Inode)), SEEK_SET);
    fwrite(&in, sizeof(Inode), 1, file);
}

void Format_Partition(Mkfs *mkfs){
    if(list_ram.isMount(mkfs->id)){
        list_ram.FormatPartition(mkfs->id);
        NodeList *node = list_ram.SearchNode(mkfs->id);
        int partSize = 0;
        FILE *file = fopen(node->disk.c_str(), "rb+");
        if(file != nullptr){
            Mbr mbr;
            fseek(file, 0, SEEK_SET);
            fread(&mbr, sizeof (Mbr), 1, file);
            if(node->type == 0){
                partSize = node->data.part_size;
            }else{
                partSize = node->data2.part_size;
            }
            int calc = Calculate_Structures(partSize);

            /*Se inicializa el Superboot*/

            SuperBoot sb;
             int readSb = 0;
             int dataStart = 0;
            if(node->type == 0){
               strcpy(sb.sb_nombre_hd, node->data.id);
               readSb = node->data.part_start + (int)sizeof (SuperBoot);
               dataStart = node->data.part_start;
            }else{
                strcpy(sb.sb_nombre_hd, node->data2.id);
                readSb = node->data2.part_start + (int)sizeof (SuperBoot);
                dataStart = node->data2.part_start;
            }
            sb.sb_arbol_virtual_count = calc;
            sb.sb_detalle_directorio_count = calc;
            sb.sb_inodos_count = 5 * calc;
            sb.sb_bloques_count = 20 * calc;
            sb.sb_arbol_virtual_free = sb.sb_arbol_virtual_count;
            sb.sb_detalle_directorio_free = sb.sb_detalle_directorio_count;
            sb.sb_inodos_free = sb.sb_inodos_count;
            sb.sb_bloques_free = sb.sb_bloques_count;
            time_t t = time(nullptr);
            tm *now = localtime(&t);
            string dateC = to_string(now->tm_mday) + "/" + to_string((now->tm_mon+1)) + "/" + to_string((now->tm_year + 1900)) + " " + to_string(now->tm_hour) + ":" + to_string(now->tm_min);
            strcpy(sb.sb_date_creacion, dateC.c_str());
            strcpy(sb.sb_date_ultimo_montaje, node->date.c_str());
            sb.sb_montajes_count = 0;
            sb.sb_ap_bitmap_arbol_directorio = readSb;
            sb.sb_ap_arbol_directorio = sb.sb_ap_bitmap_arbol_directorio + calc;
            sb.sb_ap_bitmap_detalle_directorio = sb.sb_ap_arbol_directorio + (calc * (int)sizeof(VirtualDirectoryTree));
            sb.sb_ap_detalle_directorio = sb.sb_ap_bitmap_detalle_directorio + calc;
            sb.sb_ap_bitmap_tabla_inodo = sb.sb_ap_detalle_directorio + (calc * (int)sizeof(DirectoryDetail));
            sb.sb_ap_tabla_inodo = sb.sb_ap_bitmap_tabla_inodo + (5 * calc);
            sb.sb_ap_bitmap_bloques = sb.sb_ap_tabla_inodo + (5 * calc * (int)sizeof(Inode));
            sb.sb_ap_bloques = sb.sb_ap_bitmap_bloques + (20 * calc);
            sb.sb_ap_log = sb.sb_ap_bloques + (20 * calc * (int)sizeof(DataBlock));
            sb.sb_size_struct_arbol_directorio = sizeof(VirtualDirectoryTree);
            sb.sb_size_struct_detalle_directorio = sizeof(DirectoryDetail);
            sb.sb_size_struct_inodo = sizeof(Inode);
            sb.sb_size_struct_bloque = sizeof(DataBlock);
            sb.sb_first_free_bit_arbol_directorio = sb.sb_ap_bitmap_arbol_directorio;
            sb.sb_first_free_bit_detalle_directorio = sb.sb_ap_bitmap_detalle_directorio;
            sb.sb_first_free_bit_tabla_inodo = sb.sb_ap_bitmap_tabla_inodo;
            sb.sb_first_free_bit_bloques = sb.sb_ap_bitmap_bloques;
            sb.sb_magic_num = 201700326;
            fseek(file, dataStart, SEEK_SET);
            fwrite(&sb, sizeof (SuperBoot), 1, file);
            fseek(file, sb.sb_ap_log + (calc * (int)sizeof(Log)), SEEK_SET);
            fwrite(&sb, sizeof(SuperBoot), 1, file);
            /*Journaling jo;
            strcpy(jo.op, "mkdir");
            strcpy(jo.type, "Carpeta");
            strcpy(jo.name, "/");
            strcpy(jo.content, "-");
            time_t t = time(nullptr);
            tm *now = localtime(&t);
            string chain;
            chain = to_string(now->tm_mday) + "-" + to_string((now->tm_mon+1)) + "-" + to_string((now->tm_year + 1900)) + " " + to_string(now->tm_hour) + ":" + to_string(now->tm_min);
            strcpy(jo.date, chain.c_str());
            int byte = ReturnedByteJournaling(file, readSb, readJour);
            if(byte != 0){
                fseek(file, byte, SEEK_SET);
                fwrite(&jo, sizeof (Journaling), 1, file);
            }else{
                cout << "No hay espacio en el journaling para la raiz\n";
            }*/
            char a = 49;
            ReturnedOfBitmap byteBmVirtual = ReturnByteBitmap(file, sb.sb_ap_bitmap_arbol_directorio, sb.sb_ap_arbol_directorio);
            ReturnedOfBitmap byteBmDetail = ReturnByteBitmap(file, sb.sb_ap_bitmap_detalle_directorio, sb.sb_ap_detalle_directorio);
            ReturnedOfBitmap byteBmInode = ReturnByteBitmap(file, sb.sb_ap_bitmap_tabla_inodo, sb.sb_ap_tabla_inodo);
            fseek(file, byteBmInode.byte, SEEK_SET);
            fwrite(&a, 1, 1, file);
            Inode usersInode;
            usersInode.i_count_inodo = byteBmInode.position + 1;
            usersInode.i_count_bloques_asignados = 0;
            usersInode.i_id_proper = 1;
            usersInode.i_size_archivo = 0;
            usersInode.i_perm = 764;
            string text = "1,G,root\n1,U,root,root,201700326\n";
            Recursive_CreateFile(file, text, sb, usersInode, byteBmInode.position);
            DirectoryDetail rootDirec;
            strcpy(rootDirec.dd_array_files[0].dd_file_nombre, "users.txt");
            strcpy(rootDirec.dd_array_files[0].dd_file_date_creacion, sb.sb_date_creacion);
            strcpy(rootDirec.dd_array_files[0].dd_file_date_modificacion, sb.sb_date_creacion);
            rootDirec.dd_array_files[0].dd_file_app_inodo = byteBmInode.position;
            VirtualDirectoryTree root;
            strcpy(root.avd_fecha_creacion, sb.sb_date_creacion);
            strcpy(root.avd_nombre_directorio, "/");
            root.avd_proper = 1;
            root.i_perm = 764;
            root.avd_ap_detalle_directorio = byteBmDetail.position;
            fseek(file, byteBmVirtual.byte, SEEK_SET);
            fwrite(&a, 1, 1, file);
            fseek(file, byteBmDetail.byte, SEEK_SET);
            fwrite(&a, 1, 1, file);
            fseek(file, sb.sb_ap_arbol_directorio + (byteBmVirtual.position * (int)sizeof(VirtualDirectoryTree)), SEEK_SET);
            fwrite(&root, sizeof(VirtualDirectoryTree), 1, file);
            fseek(file, sb.sb_ap_detalle_directorio + (byteBmDetail.position * (int)sizeof(DirectoryDetail)), SEEK_SET);
            fwrite(&rootDirec, sizeof(DirectoryDetail), 1, file);
        }else{
            cout << "No se puede abrir el archivo de la particion\n";
        }
        fclose(file);
        cout << "Particion '" + mkfs->id + "' formateada exitosamente\n";
    }else{
        cout << "Error: la particion con el id '" + mkfs->id + "' no esta montada\n";
    }
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
                        }else if(fd->isAdd){
                            fd->add = Total_Disk_FD(fd->unit, fd->add);
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
                                    }else if(fd->type == "l"){
                                        Create_Partition_Logic(fd);
                                    }
                                }else{
                                    Create_Partition_Primary(fd);
                                }
                            }else{
                                cout << "Error: el parametro 'size' es obligatorio\n";
                            }
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
            }else if(Mkfs *mkfs = dynamic_cast<Mkfs*>((*it))){
                if(mkfs->id != ""){
                    if(mkfs->isAdd){
                        NodeList *node = list_ram.SearchNode(mkfs->id);
                        if(node != nullptr){
                            if(node->type == 0){
                                Fdisk *fd = new Fdisk();
                                fd->path = node->disk;
                                fd->name = node->data.part_name;
                                fd->add = mkfs->add;
                                addUnits(fd);
                            }else{
                                Fdisk *fd = new Fdisk();
                                fd->path = node->disk;
                                fd->name = node->data2.part_name;
                                fd->add = mkfs->add;
                                addUnits(fd);
                            }
                        }
                    }
                    Format_Partition(mkfs);
                }else{
                    cout << "Error: el 'id' es obligatorio\n";
                }
            }/*else if(Login *login = dynamic_cast<Login*>((*it))){
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

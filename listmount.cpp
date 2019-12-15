#include "listmount.h"

ListMount::ListMount()
{
    first = nullptr;
}

void ListMount::insert(NodeList *node){
    if(first != nullptr){
        NodeList *tmp = first;
        while (tmp != nullptr) {
            if(tmp->next == nullptr){
                tmp->next = node;
                break;
            }
            tmp = tmp->next;
        }
    }else{
        first = node;
    }
}

void ListMount::unMount(std::string idDisk){
    if(first != nullptr){
        NodeList *tmp = first;
        NodeList *tmp2 = nullptr;
        while (tmp != nullptr) {
            if(strcmp(tmp->data.id, idDisk.c_str()) == 0){
                if(tmp == first){
                    first = tmp->next;
                }else if(tmp->next == nullptr){
                    tmp2->next = nullptr;
                }else{
                    tmp2->next = tmp->next;
                }
            }
            tmp2 = tmp;
            tmp = tmp->next;
        }
        std::cout << "La particion con el id " + idDisk + " ha sido desmonatda exitosamente\n";
    }
}

std::string ListMount::To_Report(std::string idDisk){
    if(first != nullptr){
        NodeList *tmp = first;
        while(tmp != nullptr){
            if(tmp->type == 0){
                if(strcmp(tmp->data.id, idDisk.c_str()) == 0){
                    return tmp->disk;
                }
            }else{
                if(strcmp(tmp->data2.id, idDisk.c_str()) == 0){
                    return tmp->disk;
                }
            }
            tmp = tmp->next;
        }
    }
    return "";
}

bool ListMount::isMount(std::string id){
    if(first != nullptr){
        NodeList *tmp = first;
        while(tmp != nullptr){
            if(tmp->type == 0){
                if(strcmp(tmp->data.id, id.c_str()) == 0){
                    return true;
                }
            }else{
                if(strcmp(tmp->data2.id, id.c_str()) == 0){
                    return true;
                }
            }
            tmp = tmp->next;
        }
    }
    return false;
}

bool ListMount::isMountByName(std::string name){
    if(first != nullptr){
        NodeList *tmp = first;
        while(tmp != nullptr){
            if(tmp->type == 0){
                if(strcmp(tmp->data.part_name, name.c_str()) == 0){
                    return true;
                }
            }else{
                if(strcmp(tmp->data2.part_name, name.c_str()) == 0){
                    return true;
                }
            }
            tmp = tmp->next;
        }
    }
    return false;
}

void ListMount::List_Mount(){
    if(first != nullptr){
        NodeList *tmp = first;
        while(tmp != nullptr){
            if(tmp->type == 0){
                std::cout << std::string("\nParticion ") + tmp->data.id + std::string(":\n");
                std::cout << std::string("Nombre de la particion: ") + tmp->data.part_name + std::string("\n");
                std::cout << std::string("Ajuste: ") + tmp->data.part_fit + std::string("\n");
                std::cout << std::string("Tamaño de la particion: ") + std::to_string(tmp->data.part_size) + "\n";
                std::cout << std::string("Tipo de particion: Primaria\n");
                std::cout << "Inicio de la particion: " + std::to_string(tmp->data.part_start) + "\n";
            }else{
                std::cout << std::string("\nParticion ") + tmp->data2.id + std::string(":\n");
                std::cout << std::string("Nombre de la particion: ") + tmp->data2.part_name + std::string("\n");
                std::cout << std::string("Ajuste: ") + tmp->data2.part_fit + std::string("\n");
                std::cout << std::string("Tamaño de la particion: ") + std::to_string(tmp->data2.part_size) + "\n";
                std::cout << std::string("Tipo de particion: Logica\n");
                std::cout << "Inicio de la particion: " + std::to_string(tmp->data2.part_start) + "\n";
            }
            tmp = tmp->next;
        }
    }
}

void ListMount::FormatPartition(std::string id){
    NodeList *tmp = first;
    while(tmp != nullptr){
        if(tmp->type == 0){
            if(strcmp(tmp->data.id, id.c_str()) == 0){
                tmp->format = 1;
                return;
            }
        }else{
            if(strcmp(tmp->data2.id, id.c_str()) == 0){
                tmp->format = 1;
                return;
            }
        }
        tmp = tmp->next;
    }
}

NodeList* ListMount::SearchNode(std::string id){
    if(first != nullptr){
        NodeList *tmp = first;
        while(tmp != nullptr){
            if(tmp->type == 0){
                if(strcmp(tmp->data.id, id.c_str()) == 0){
                    return tmp;
                }
            }else{
                if(strcmp(tmp->data2.id, id.c_str()) == 0){
                    return tmp;
                }
            }
            tmp = tmp->next;
        }
    }
    return nullptr;
}

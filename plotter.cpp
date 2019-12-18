#include "plotter.h"

Plotter::Plotter()
{

}

void Plotter::Plot_Mbr(FILE *filetoRead, Mbr mbr, std::string nameDisk, std::string path){
    std::string body = "";
    std::string ebrNode = "";
    body += "<TR>\n" +
            std::string("<TD BGCOLOR=\"lightblue\">Nombre</TD>\n") +
            "<TD BGCOLOR=\"lightblue\">Valor</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>mbr_tamaño</TD>\n") +
            "<TD>" + std::to_string(mbr.mbr_size) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>mbr_fecha_creacion</TD>\n") +
            "<TD>" + mbr.dateTime + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>mbr_disk_signature</TD>\n") +
            "<TD>" + std::to_string(mbr.mbr_disk_aignature) + "</TD>\n" +
            std::string("</TR>\n");
    for(int x=0; x<4; x++){
        if(mbr.particions[x].part_start != -1){
            body += "<TR>\n" +
            std::string("<TD>part_status_") + std::to_string(x+1) + "</TD>\n" +
            "<TD>" + mbr.particions[x].part_status + "</TD>\n" +
            std::string("</TR>\n");
            body += "<TR>\n" +
                    std::string("<TD>part_type_") + std::to_string(x+1) + "</TD>\n" +
                    "<TD>" + mbr.particions[x].part_type + "</TD>\n" +
                    std::string("</TR>\n");
            body += "<TR>\n" +
                    std::string("<TD>part_fit_") + std::to_string(x+1) + "</TD>\n" +
                    "<TD>" + mbr.particions[x].part_fit + "</TD>\n" +
                    std::string("</TR>\n");
            body += "<TR>\n" +
                    std::string("<TD>part_start_") + std::to_string(x+1) + "</TD>\n" +
                    "<TD>" + std::to_string(mbr.particions[x].part_start) + "</TD>\n" +
                    std::string("</TR>\n");
            body += "<TR>\n" +
                    std::string("<TD>part_size_") + std::to_string(x+1) + "</TD>\n" +
                    "<TD>" + std::to_string(mbr.particions[x].part_size) + "</TD>\n" +
                    std::string("</TR>\n");
            body += "<TR>\n" +
                    std::string("<TD>part_name_") + std::to_string(x+1) + "</TD>\n" +
                    "<TD>" + mbr.particions[x].part_name + "</TD>\n" +
                    std::string("</TR>\n");
            if(mbr.particions[x].part_type == 69){
                Ebr ebr;
                fseek(filetoRead, mbr.particions[x].part_start, SEEK_SET);
                fread(&ebr, sizeof(Ebr), 1, filetoRead);
                if(ebr.isLogic == 49){
                   ebrNode = Ebr_Recursive(filetoRead, ebr, "", 66, 1);
                }
            }
        }
    }
    std::string input = "";
    if(ebrNode == ""){
        input = "digraph example {\n" +
                            std::string("node [shape=plaintext]\n") +
                            "rankdir=TB\n" +
                            std::string("A [label=<\n") +
                            "<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\">\n" +
                            body +
                            "</TABLE>\n" +
                            ">];\n" +
                            "}";
    }else{
        input = "digraph example {\n" +
                            std::string("node [shape=plaintext]\n") +
                            "rankdir=TB\n" +
                            std::string("A [label=<\n") +
                            "<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\">\n" +
                            body +
                            "</TABLE>\n" +
                            ">];\n" +
                            ebrNode +
                            "}";
    }
    std::ofstream file;
    std::string pathTxt = path + ".txt";
    std::string pathJpg = path + ".pdf";
    file.open(pathTxt);
    if(file.fail()){
        std::cout << "Error al abrir el txt\n";
        return;
    }
    file << input << std::endl;
    file.close();
    std::string pathUnion = "dot " + pathTxt + " -o " + pathJpg + " -Tpdf";
    system(pathUnion.c_str());
}

std::string Plotter::Ebr_Recursive(FILE *file, Ebr logic, std::string textBody, char nodeName, int countEbr){
    std::string bodyTxt = "";
    bodyTxt += "<TR>\n" +
            std::string("<TD BGCOLOR=\"lightblue\">Nombre</TD>\n") +
            "<TD BGCOLOR=\"lightblue\">Valor</TD>\n" +
            std::string("</TR>\n");
    bodyTxt += "<TR>\n" +
            std::string("<TD>part_status_") + std::to_string(countEbr) + "</TD>\n" +
            "<TD>" + logic.part_status + "</TD>\n" +
            std::string("</TR>\n");
    bodyTxt += "<TR>\n" +
            std::string("<TD>part_fit_") + std::to_string(countEbr) + "</TD>\n" +
            "<TD>" + logic.part_fit + "</TD>\n" +
            std::string("</TR>\n");
    bodyTxt += "<TR>\n" +
            std::string("<TD>part_start_") + std::to_string(countEbr) + "</TD>\n" +
            "<TD>" + std::to_string(logic.part_start) + "</TD>\n" +
            std::string("</TR>\n");
    bodyTxt += "<TR>\n" +
            std::string("<TD>part_size_") + std::to_string(countEbr) + "</TD>\n" +
            "<TD>" + std::to_string(logic.part_size) + "</TD>\n" +
            std::string("</TR>\n");
    bodyTxt += "<TR>\n" +
            std::string("<TD>part_next_") + std::to_string(countEbr) + "</TD>\n" +
            "<TD>" + std::to_string(logic.part_next) + "</TD>\n" +
            std::string("</TR>\n");
    bodyTxt += "<TR>\n" +
            std::string("<TD>part_name_") + std::to_string(countEbr) + "</TD>\n" +
            "<TD>" + logic.part_name + "</TD>\n" +
            std::string("</TR>\n");
    textBody += std::to_string(nodeName++) + " [label=<\n" +
                "<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\">\n" +
                bodyTxt +
                "</TABLE>\n" +
                ">];\n";
    if(logic.part_next != 0){
        Ebr ebr;
        fseek(file, logic.part_next, SEEK_SET);
        fread(&ebr, sizeof(Ebr), 1, file);
        textBody = Ebr_Recursive(file, ebr, textBody, nodeName, ++countEbr);
    }
    return textBody;
}

void Plotter::Plot_Disk(FILE *ff, Mbr mbr, std::string path, int space){
    std::string body;
    int yy = 0;
    body += "<TD>MBR</TD>\n";
    for(int x=0; x<4; x++){
        if(mbr.particions[x].part_start == -1){
            yy++;
        }
    }
    for(int x=0; x<4; x++){
        body += "<TD>";
        if(mbr.particions[x].part_start != -1){
            if(mbr.particions[x].part_type == 80){
                body += "Primaria<br/>" + std::to_string(mbr.particions[x].part_size * 100 / mbr.mbr_size) + "% del disco";
            }else if(mbr.particions[x].part_type == 69){
                Ebr ebr;
                fseek(ff, mbr.particions[x].part_start, SEEK_SET);
                fread(&ebr, sizeof(Ebr), 1, ff);
                std::string tableLogic = "";
                std::string ebrLogic = "";
                ebrLogic += "<TD>EBR</TD>\n";
                if(ebr.isLogic == 49){
                    ebrLogic += "<TD>Logica<br/>" + std::to_string(ebr.part_size * 100 / mbr.mbr_size) + "% del disco</TD>\n";
                    int freeSpaceLogic = mbr.particions[x].part_size - ebr.part_size;
                    if(ebr.part_next != 0){
                        ebrLogic = Ebr_REcursive_Disk(ff, ebr, ebrLogic, mbr.mbr_size, freeSpaceLogic);
                    }else{
                        ebrLogic += "<TD>Libre<br/>" + std::to_string(freeSpaceLogic * 100 / mbr.mbr_size) + "% del disco</TD>\n";
                    }
                }else{
                    ebrLogic += "<TD>Libre<br/>" + std::to_string(mbr.particions[x].part_size * 100 / mbr.mbr_size) + "% del disco</TD>\n";
                }
                tableLogic = std::string("<TABLE>\n") +
                              "<TR><TD>Extendida</TD></TR>" +
                              "<TR>" + ebrLogic + "</TR>\n" +
                              "</TABLE>";
                body += tableLogic;
            }
        }else{
            body += "Libre<br/>" + std::to_string((space/yy) * 100 / mbr.mbr_size) + "% del disco";
        }
        body += "</TD>\n";
    }
    std::string input = "digraph test {\n" +
                        std::string("graph [ratio=fill];\n") +
                        "node [label=\"\\N\", fontsize=15, shape=plaintext]" +
                        std::string("graph [bb=\"0, 0, 352, 154\"];\n") +
                        "arset [label=<\n" +
                        std::string("<TABLE ALIGN=\"LEFT\">\n") +
                        "<TR>\n" +
                        body +
                        "</TR>\n" +
                        std::string("</TABLE>\n") +
                        ">, ];\n" +
                        "}";

    std::ofstream file;
    std::string pathTxt = path + ".txt";
    std::string pathJpg = path + ".pdf";
    file.open(pathTxt);
    if(file.fail()){
        std::cout << "Error al abrir el txt\n";
        return;
    }
    file << input << std::endl;
    file.close();
    std::string pathUnion = "dot " + pathTxt + " -o " + pathJpg + " -Tpdf";
    system(pathUnion.c_str());
}

std::string Plotter::Ebr_REcursive_Disk(FILE *file, Ebr logic, std::string txtBody, int totalSize, int freeExtended){
    Ebr ebr;
    fseek(file, logic.part_next, SEEK_SET);
    fread(&ebr, sizeof(Ebr), 1, file);
    txtBody += "<TD>EBR</TD>\n";
    txtBody += "<TD>Logica<br/>" + std::to_string(ebr.part_size * 100 / totalSize) + "% del disco</TD>\n";
    freeExtended -= ebr.part_size;
    if(ebr.part_next != 0){
        txtBody = Ebr_REcursive_Disk(file, ebr, txtBody, totalSize, freeExtended);
    }else{
        txtBody += "<TD>Libre<br/>" + std::to_string(freeExtended * 100 / totalSize) + "% del disco</TD>\n";
    }
    return txtBody;
}

void Plotter::Plot_BmAvd(FILE *file, int startBm, int endBm, std::string path){
    std::string pathRR = path + ".txt";
    std::ofstream fs(pathRR);
    if(fs.fail()){
        std::cout << "Error al abrir el txt\n";
        return;
    }
    int count = 1;
    char pivot;
    while(startBm < endBm){
        fseek(file, startBm, SEEK_SET);
        fread(&pivot, 1, 1, file);
        if(count == 20){
            if(pivot == 49){
                fs << "1\n";
            }else{
                fs << "0\n";
            }
            count = 0;
        }else{
            if(pivot == 49){
                fs << "1|";
            }else{
                fs << "0|";
            }
        }
        startBm++;
        count++;
    }
    fs.close();
}

void Plotter::Plot_Log(FILE *file, int startLog, int endLog, std::string path){
    std::string pathR = path + ".txt";
    std::ofstream fs(pathR);
    if(fs.fail()){
        std::cout << "Error al abrir el txt\n";
        return;
    }
    Log log;
    while (startLog <= endLog) {
        fseek(file, startLog, SEEK_SET);
        fread(&log, sizeof(Log), 1, file);
        if(log.log_tipo_operacion != 0){
            if(log.log_tipo_operacion == 1){
                fs << "Tipo Operación: mkdir\n";
                fs << "Tipo: Directorio\n";
                fs << "Nombre: " + std::string(log.log_nombre) + "\n";
                fs << "Fecha: " + std::string(log.log_fecha) + "\n\n\n";
            }else{
                fs << "Tipo Operación: mkfile\n";
                fs << "Tipo: Archivo\n";
                fs << "Nombre: " + std::string(log.log_nombre) + "\n";
                fs << "Contenido: " + std::string(log.log_contenido) + "\n";
                fs << "Fecha: " + std::string(log.log_fecha) + "\n\n\n";
            }
        }
        startLog += sizeof(Log);
    }
    fs.close();
}

void Plotter::Plot_Directory(FILE *file, SuperBoot sb, std::string path){
    VirtualDirectoryTree root;
    fseek(file, sb.sb_ap_arbol_directorio, SEEK_SET);
    fread(&root, sizeof(VirtualDirectoryTree), 1, file);
    std::string txtBody = "";
    std::string nodePointers = "";
    txtBody = Directory_Tour(file, sb, root, txtBody, 0);
    nodePointers = Pointer_Travel(file, sb, root, nodePointers, 0);
    std::string toR = "digraph structs {\n" +
                      std::string("node [shape=record];\n") +
                      txtBody +
                      nodePointers +
                      "}";
    std::ofstream file2;
    std::string pathTxt = path + ".txt";
    std::string pathJpg = path + ".pdf";
    file2.open(pathTxt);
    if(file2.fail()){
        std::cout << "Error al abrir el txt\n";
        return;
    }
    file2 << toR << std::endl;
    file2.close();
    std::string pathUnion = "dot " + pathTxt + " -o " + pathJpg + " -Tpdf";
    system(pathUnion.c_str());
}

std::string Plotter::Directory_Tour(FILE *file, SuperBoot sb, VirtualDirectoryTree root, std::string txt, int posAvd){
    txt += "DA" + std::to_string(posAvd) + " [label=\"{<t0>" + root.avd_nombre_directorio + "|{";
    for(int x=0; x<6; x++){
        txt += "<p" + std::to_string(x) + ">" + std::to_string(root.avd_ap_array_subdirectorios[x]) + "|";
    }
    txt += "<p6>" + std::to_string(root.avd_ap_detalle_directorio) + "|";
    txt += "<p7>" + std::to_string(root.avd_ap_arbol_virtual_directorio) + "}}\"];\n";
    for(int x=0; x<6; x++){
        if(root.avd_ap_array_subdirectorios[x] != -1){
            VirtualDirectoryTree avd;
            fseek(file, sb.sb_ap_arbol_directorio + (root.avd_ap_array_subdirectorios[x] * (int)sizeof(VirtualDirectoryTree)), SEEK_SET);
            fread(&avd, sizeof(VirtualDirectoryTree), 1, file);
            txt = Directory_Tour(file, sb, avd, txt, root.avd_ap_array_subdirectorios[x]);
        }
    }
    if(root.avd_ap_arbol_virtual_directorio != -1){
        VirtualDirectoryTree avd;
        fseek(file, sb.sb_ap_arbol_directorio + (root.avd_ap_arbol_virtual_directorio * (int)sizeof(VirtualDirectoryTree)), SEEK_SET);
        fread(&avd, sizeof(VirtualDirectoryTree), 1, file);
        txt = Directory_Tour(file, sb, avd, txt, root.avd_ap_arbol_virtual_directorio);
    }
    return txt;
}

std::string Plotter::Pointer_Travel(FILE *file, SuperBoot sb, VirtualDirectoryTree root, std::string txt, int posAvd){
    for(int x=0; x<6; x++){
        if(root.avd_ap_array_subdirectorios[x] != -1){
            txt += "DA" + std::to_string(posAvd) + ":p" + std::to_string(x) + "->DA" + std::to_string(root.avd_ap_array_subdirectorios[x]) + ":t0\n";
        }
    }
    if(root.avd_ap_arbol_virtual_directorio != -1){
        txt += "DA" + std::to_string(posAvd) + ":p7->DA" + std::to_string(root.avd_ap_arbol_virtual_directorio) + ":t0\n";
    }
    for(int x=0; x<6; x++){
        if(root.avd_ap_array_subdirectorios[x] != -1){
            VirtualDirectoryTree avd;
            fseek(file, sb.sb_ap_arbol_directorio + (root.avd_ap_array_subdirectorios[x] * (int)sizeof(VirtualDirectoryTree)), SEEK_SET);
            fread(&avd, sizeof(VirtualDirectoryTree), 1, file);
            txt = Pointer_Travel(file, sb, avd, txt, root.avd_ap_array_subdirectorios[x]);
        }
    }
    if(root.avd_ap_arbol_virtual_directorio != -1){
        VirtualDirectoryTree avd;
        fseek(file, sb.sb_ap_arbol_directorio + (root.avd_ap_arbol_virtual_directorio * (int)sizeof(VirtualDirectoryTree)), SEEK_SET);
        fread(&avd, sizeof(VirtualDirectoryTree), 1, file);
        txt = Pointer_Travel(file, sb, avd, txt, root.avd_ap_arbol_virtual_directorio);
    }
    return txt;
}

VirtualDirectoryTree Plotter::SearchAvd(FILE *file, SuperBoot sb, VirtualDirectoryTree root, std::string folder, std::queue<std::string> route, VirtualDirectoryTree searchNode){
    if(strcmp(root.avd_nombre_directorio, folder.c_str()) == 0){
        if(route.empty()){
            return root;
        }else{
            folder = route.front();
            route.pop();
        }
    }
    for(int x=0; x<6; x++){
        if(root.avd_ap_array_subdirectorios[x] != -1){
            VirtualDirectoryTree avd;
            fseek(file, sb.sb_ap_arbol_directorio + (root.avd_ap_array_subdirectorios[x] * (int)sizeof(VirtualDirectoryTree)), SEEK_SET);
            fread(&avd, sizeof(VirtualDirectoryTree), 1, file);
            searchNode = SearchAvd(file, sb, avd, folder, route, searchNode);
            if(strcmp(searchNode.avd_nombre_directorio, "") != 0){
                return searchNode;
            }
        }
    }
    if(root.avd_ap_arbol_virtual_directorio != -1){
        VirtualDirectoryTree avd;
        fseek(file, sb.sb_ap_arbol_directorio + (root.avd_ap_arbol_virtual_directorio * (int)sizeof(VirtualDirectoryTree)), SEEK_SET);
        fread(&avd, sizeof(VirtualDirectoryTree), 1, file);
        searchNode = SearchAvd(file, sb, avd, folder, route, searchNode);
        if(strcmp(searchNode.avd_nombre_directorio, "") != 0){
            return searchNode;
        }
    }
    return searchNode;
}

void Plotter::Print_Files(FILE *file, SuperBoot sb, DirectoryDetail dd, int count){
    for(int x=0; x<5; x++){
        if(dd.dd_array_files[x].dd_file_app_inodo != -1){
            std::cout << std::to_string(++count) + ". " + dd.dd_array_files[x].dd_file_nombre + "\n";
        }
    }
    if(dd.dd_ap_detalle_directorio != -1){
        DirectoryDetail dd2;
        fseek(file, sb.sb_ap_detalle_directorio + (dd.dd_ap_detalle_directorio * (int)sizeof(DirectoryDetail)), SEEK_SET);
        fread(&dd2, sizeof(DirectoryDetail), 1, file);
        Print_Files(file, sb, dd2, count);
    }
}

ContentDetail Plotter::searchContent(FILE *file, SuperBoot sb, DirectoryDetail dd, int count, int selection, ContentDetail cD){
    for(int x=0; x<5; x++){
        if(count == selection){
            return dd.dd_array_files[x];
        }
        count++;
    }
    if(dd.dd_ap_detalle_directorio != -1){
        DirectoryDetail dd2;
        fseek(file, sb.sb_ap_detalle_directorio + (dd.dd_ap_detalle_directorio * (int)sizeof(DirectoryDetail)), SEEK_SET);
        fread(&dd2, sizeof(DirectoryDetail), 1, file);
        return searchContent(file, sb, dd2, count, selection, cD);
    }
    return cD;
}

void Plotter::Plot_Tree_File(FILE *file, SuperBoot sb, std::string folder, std::queue<std::string> route, std::string path){
    VirtualDirectoryTree root;
    fseek(file, sb.sb_ap_arbol_directorio, SEEK_SET);
    fread(&root, sizeof(VirtualDirectoryTree), 1, file);
    VirtualDirectoryTree searchNode;
    searchNode = SearchAvd(file, sb, root, folder, route, searchNode);
    DirectoryDetail dd;
    fseek(file, sb.sb_ap_detalle_directorio + (searchNode.avd_ap_detalle_directorio * (int)sizeof(DirectoryDetail)), SEEK_SET);
    fread(&dd, sizeof(DirectoryDetail), 1, file);
    int count = 0;
    std::cout << "Elija el archivo a graficar\n";
    Print_Files(file, sb, dd, count);
    std::string option;
    getline(std::cin, option);
    int op = std::stoi(option);
    ContentDetail cD2;
    ContentDetail cD = searchContent(file, sb, dd, 0, op - 1, cD2);
    if(strcmp(cD.dd_file_nombre, "") != 0){
        Inode in;
        fseek(file, sb.sb_ap_tabla_inodo + (cD.dd_file_app_inodo * (int)sizeof(Inode)), SEEK_SET);
        fread(&in, sizeof(Inode), 1, file);
        std::string txtBody = "";
        std::string txtRelationship = "";
        txtBody = Txt_Inode(file, sb, in, txtBody, cD.dd_file_app_inodo);
        txtBody = Txt_Block(file, sb, in, txtBody);
        txtRelationship = Node_Relationsip_Inodes(file, sb, in, cD.dd_file_app_inodo, txtRelationship);
        std::string toR = std::string("digraph structs {\n") +
                          "node [shape=record];\n" +
                          "DD" + " [label=\"{<t0>DD|{" + cD.dd_file_nombre + "|<p0>" + std::to_string(cD.dd_file_app_inodo) + "}}\"];\n" +
                           txtBody +
                           txtRelationship +
                           "DD:p0->I" + std::to_string(cD.dd_file_app_inodo) + ":t0\n" +
                           "}";
        std::ofstream file2;
        std::string pathTxt = path + ".txt";
        std::string pathJpg = path + ".pdf";
        file2.open(pathTxt);
        if(file2.fail()){
            std::cout << "Error al abrir el txt\n";
            return;
        }
        file2 << toR << std::endl;
        file2.close();
        std::string pathUnion = "dot " + pathTxt + " -o " + pathJpg + " -Tpdf";
        system(pathUnion.c_str());
    }else{
        std::cout << "Error no hay ningun archivo en la opcion seleccionada\n";
    }
}

std::string Plotter::Txt_Inode(FILE *file, SuperBoot sb, Inode in, std::string txt, int posIn){
    txt += "I" + std::to_string(posIn) + " [label=\"{<t0>" + std::to_string(posIn) + "|";
    for(int x=0; x<4; x++){
            txt += "{<p" + std::to_string(x) + ">" + std::to_string(in.i_array_bloques[x]) + "}|";
    }
    txt += "{<p4>" + std::to_string(in.i_ap_indirecto) + "}}\"];\n";
    if(in.i_ap_indirecto != -1){
        Inode in2;
        fseek(file, sb.sb_ap_tabla_inodo + (in.i_ap_indirecto * (int)sizeof(Inode)), SEEK_SET);
        fread(&in2, sizeof(Inode), 1, file);
        txt = Txt_Inode(file, sb, in2, txt, in.i_ap_indirecto);
    }
    return txt;
}

std::string Plotter::Txt_Block(FILE *file, SuperBoot sb, Inode in, std::string txt){
    for(int x=0; x<4; x++){
        if(in.i_array_bloques[x] != -1){
            DataBlock db;
            fseek(file, sb.sb_ap_bloques + (in.i_array_bloques[x] * (int)sizeof(DataBlock)), SEEK_SET);
            fread(&db, sizeof(DataBlock), 1, file);
            txt += "B" + std::to_string(in.i_array_bloques[x]) + " [label=\"{<t0>" + std::to_string(in.i_array_bloques[x]) + "|" + RetirveTextBlock(db) + "}\"];\n";
        }
    }
    if(in.i_ap_indirecto != -1){
        Inode in2;
        fseek(file, sb.sb_ap_tabla_inodo + (in.i_ap_indirecto * (int)sizeof(Inode)), SEEK_SET);
        fread(&in2, sizeof(Inode), 1, file);
        txt = Txt_Block(file, sb, in2, txt);
    }
    return txt;
}

std::string Plotter::Node_Relationsip_Inodes(FILE *file, SuperBoot sb, Inode in, int posInodo, std::string txt){
    for(int x=0; x<4; x++){
        if(in.i_array_bloques[x] != -1){
            txt += "I" + std::to_string(posInodo) + ":p" + std::to_string(x) + "->B" + std::to_string(in.i_array_bloques[x]) + ":t0\n";
        }
    }
    if(in.i_ap_indirecto != -1){
        txt += "I" + std::to_string(posInodo) + ":p5->I" + std::to_string(in.i_ap_indirecto) + ":t0\n";
        Inode in2;
        fseek(file, sb.sb_ap_tabla_inodo + (in.i_ap_indirecto * (int)sizeof(Inode)), SEEK_SET);
        fread(&in2, sizeof(Inode), 1, file);
        txt = Node_Relationsip_Inodes(file, sb, in2, in.i_ap_indirecto, txt);
    }
    return txt;
}

std::string Plotter::RetirveTextBlock(DataBlock db){
    std::string txt = "";
    for(int x=0; x<25; x++){
        if(db.db_data[x] != 0){
            txt += db.db_data[x];
        }
    }
    return txt;
}

void Plotter::Plot_Sb(SuperBoot sb, FILE *file, std::string path){
    std::string body = "";
    body += "<TR>\n" +
            std::string("<TD BGCOLOR=\"lightblue\">Nombre</TD>\n") +
            "<TD BGCOLOR=\"lightblue\">Valor</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_nombre_hd</TD>\n") +
            "<TD>" + sb.sb_nombre_hd + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_arbol_virtual_count</TD>\n") +
            "<TD>" + std::to_string(sb.sb_arbol_virtual_count) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_detalle_directorio_count</TD>\n") +
            "<TD>" + std::to_string(sb.sb_detalle_directorio_count) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_inodos_count</TD>\n") +
            "<TD>" + std::to_string(sb.sb_inodos_count) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_bloques_count</TD>\n") +
            "<TD>" + std::to_string(sb.sb_bloques_count) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_arbol_virtual_free</TD>\n") +
            "<TD>" + std::to_string(sb.sb_arbol_virtual_free) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_detalle_directorio_free</TD>\n") +
            "<TD>" + std::to_string(sb.sb_detalle_directorio_free) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_inodos_free</TD>\n") +
            "<TD>" + std::to_string(sb.sb_inodos_free) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_bloques_free</TD>\n") +
            "<TD>" + std::to_string(sb.sb_bloques_free) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_date_creacion</TD>\n") +
            "<TD>" + sb.sb_date_creacion + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_date_ultimo_montaje</TD>\n") +
            "<TD>" + sb.sb_date_ultimo_montaje + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_montajes_count</TD>\n") +
            "<TD>" + std::to_string(sb.sb_montajes_count) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_ap_bitmap_arbol_directorio</TD>\n") +
            "<TD>" + std::to_string(sb.sb_ap_bitmap_arbol_directorio) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_ap_arbol_directorio</TD>\n") +
            "<TD>" + std::to_string(sb.sb_ap_arbol_directorio) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_ap_bitmap_detalle_directorio</TD>\n") +
            "<TD>" + std::to_string(sb.sb_ap_bitmap_detalle_directorio) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_ap_detalle_directorio</TD>\n") +
            "<TD>" + std::to_string(sb.sb_ap_detalle_directorio) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_ap_bitmap_tabla_inodo</TD>\n") +
            "<TD>" + std::to_string(sb.sb_ap_bitmap_tabla_inodo) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_ap_tabla_inodo</TD>\n") +
            "<TD>" + std::to_string(sb.sb_ap_tabla_inodo) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_ap_bitmap_bloques</TD>\n") +
            "<TD>" + std::to_string(sb.sb_ap_bitmap_bloques) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_ap_bloques</TD>\n") +
            "<TD>" + std::to_string(sb.sb_ap_bloques) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_ap_log</TD>\n") +
            "<TD>" + std::to_string(sb.sb_ap_log) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_size_struct_arbol_directorio</TD>\n") +
            "<TD>" + std::to_string(sb.sb_size_struct_arbol_directorio) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_size_struct_detalle_directorio</TD>\n") +
            "<TD>" + std::to_string(sb.sb_size_struct_detalle_directorio) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_size_struct_inodo</TD>\n") +
            "<TD>" + std::to_string(sb.sb_size_struct_inodo) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_size_struct_bloque</TD>\n") +
            "<TD>" + std::to_string(sb.sb_size_struct_bloque) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_first_free_bit_arbol_directorio</TD>\n") +
            "<TD>" + std::to_string(FreeBitmap(file, sb.sb_ap_bitmap_arbol_directorio, sb.sb_ap_arbol_directorio)) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_first_free_bit_detalle_directorio</TD>\n") +
            "<TD>" + std::to_string(FreeBitmap(file, sb.sb_ap_bitmap_detalle_directorio, sb.sb_ap_detalle_directorio)) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_first_free_bit_tabla_inodo</TD>\n") +
            "<TD>" + std::to_string(FreeBitmap(file, sb.sb_ap_bitmap_tabla_inodo, sb.sb_ap_tabla_inodo)) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_first_free_bit_bloques</TD>\n") +
            "<TD>" + std::to_string(FreeBitmap(file, sb.sb_ap_bitmap_bloques, sb.sb_ap_bloques)) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>sb_magic_num</TD>\n") +
            "<TD>" + std::to_string(sb.sb_magic_num) + "</TD>\n" +
            std::string("</TR>\n");
    std::string input = "";
    input = "digraph example {\n" +
                        std::string("node [shape=plaintext]\n") +
                        "rankdir=TB\n" +
                        std::string("A [label=<\n") +
                        "<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\">\n" +
                        body +
                        "</TABLE>\n" +
                        ">];\n" +
                        "}";
    std::ofstream file2;
    std::string pathTxt = path + ".txt";
    std::string pathJpg = path + ".pdf";
    file2.open(pathTxt);
    if(file2.fail()){
        std::cout << "Error al abrir el txt\n";
        return;
    }
    file2 << input << std::endl;
    file2.close();
    std::string pathUnion = "dot " + pathTxt + " -o " + pathJpg + " -Tpdf";
    system(pathUnion.c_str());
}

int Plotter::FreeBitmap(FILE *file, int startBm, int endBm){
    char a;
    while(startBm <= endBm){
        fseek(file, startBm, SEEK_SET);
        fread(&a, 1, 1, file);
        if(a == 0){
            return startBm;
        }
        startBm++;
    }
    return 0;
}

void Plotter::Plot_Tree_Complete(FILE *file, SuperBoot sb, std::string path){
    VirtualDirectoryTree root;
    fseek(file, sb.sb_ap_arbol_directorio, SEEK_SET);
    fread(&root, sizeof(VirtualDirectoryTree), 1, file);
}

std::string Plotter::NodeAvdComplete(FILE *file, SuperBoot sb, std::string txt, VirtualDirectoryTree root, int posAvd){
    txt += "DA" + std::to_string(posAvd) + " [label=\"{<t0>" + root.avd_nombre_directorio + "|{";
    for(int x=0; x<6; x++){
        txt += "<p" + std::to_string(x) + ">" + std::to_string(root.avd_ap_array_subdirectorios[x]) + "|";
    }
    txt += "<p6>" + std::to_string(root.avd_ap_detalle_directorio) + "|";
    txt += "<p7>" + std::to_string(root.avd_ap_arbol_virtual_directorio) + "}}\"];\n";
    for(int x=0; x<6; x++){
        if(root.avd_ap_array_subdirectorios[x] != -1){
            VirtualDirectoryTree avd;
            fseek(file, sb.sb_ap_arbol_directorio + (root.avd_ap_array_subdirectorios[x] * (int)sizeof(VirtualDirectoryTree)), SEEK_SET);
            fread(&avd, sizeof(VirtualDirectoryTree), 1, file);
            txt = Directory_Tour(file, sb, avd, txt, root.avd_ap_array_subdirectorios[x]);
        }
    }
    if(root.avd_ap_arbol_virtual_directorio != -1){
        VirtualDirectoryTree avd;
        fseek(file, sb.sb_ap_arbol_directorio + (root.avd_ap_arbol_virtual_directorio * (int)sizeof(VirtualDirectoryTree)), SEEK_SET);
        fread(&avd, sizeof(VirtualDirectoryTree), 1, file);
        txt = Directory_Tour(file, sb, avd, txt, root.avd_ap_arbol_virtual_directorio);
    }

}

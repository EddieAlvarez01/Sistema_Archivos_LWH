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
    std::string pathJpg = path + ".png";
    file.open(pathTxt);
    if(file.fail()){
        std::cout << "Error al abrir el txt\n";
        return;
    }
    file << input << std::endl;
    file.close();
    std::string pathUnion = "dot " + pathTxt + " -o " + pathJpg + " -Tpng";
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
    std::string pathJpg = path + ".png";
    file.open(pathTxt);
    if(file.fail()){
        std::cout << "Error al abrir el txt\n";
        return;
    }
    file << input << std::endl;
    file.close();
    std::string pathUnion = "dot " + pathTxt + " -o " + pathJpg + " -Tpng";
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
